/**
 * @copyright Copyright (c) 2026 B-com http://www.b-com.com/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <datastructure/GeoReference.h>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <ctime>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string_view>

namespace SolAR {
namespace datastructure {

namespace {

// WGS-84 ellipsoid
constexpr double WGS84_A = 6378137.0;                    // semi-major axis (m)
constexpr double WGS84_F = 1.0 / 298.257223563;          // flattening
constexpr double WGS84_E2 = WGS84_F * (2.0 - WGS84_F);   // first eccentricity squared

constexpr std::string_view ROTATION_CONVENTION = "map_to_enu";
constexpr std::string_view HEIGHT_TYPE = "ellipsoidal_wgs84";

std::string nowIso8601Utc()
{
    const std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm utc{};
    gmtime_r(&now, &utc);
    char buffer[sizeof("YYYY-MM-DDTHH:MM:SSZ")];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", &utc);
    return buffer;
}

bool isIso8601Utc(const std::string& value)
{
    static const std::regex pattern(R"(^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(\.\d+)?Z$)");
    return std::regex_match(value, pattern);
}

nlohmann::json optionalToJson(const std::optional<double>& value)
{
    return value ? nlohmann::json(*value) : nlohmann::json(nullptr);
}

std::optional<double> optionalFromJson(const nlohmann::json& object, const char* key)
{
    if (!object.contains(key) || object.at(key).is_null()) {
        return std::nullopt;
    }
    return object.at(key).get<double>();
}

std::string optionalToString(const std::optional<double>& value)
{
    return value ? std::to_string(*value) : std::string("unknown");
}

// Boost serialization of an optional value, as a presence flag followed by the value (0 if absent).
// When loading, "ar &" overwrites both locals with the stored ones and the optional is rebuilt from them
template <typename Archive>
void serializeOptional(Archive &ar, std::optional<double>& value)
{
    bool hasValue = value.has_value();
    double data = value.value_or(0.0);
    ar & hasValue;
    ar & data;
    if (typename Archive::is_loading()) {
        value = hasValue ? std::optional<double>(data) : std::nullopt;
    }
}

// Upper-case copy of a string, so that parsing also accepts the lower-case values written by earlier versions
std::string toUpper(std::string value)
{
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) { return static_cast<char>(std::toupper(ch)); });
    return value;
}

} // anonymous namespace

std::string toString(GeoReferenceMethod method)
{
    switch (method) {
        case GeoReferenceMethod::GNSS_FIT:
            return "GNSS_FIT";
        case GeoReferenceMethod::MARKER_MEASURED:
            return "MARKER_MEASURED";
        case GeoReferenceMethod::DEVICE_ALIGNMENT:
            return "DEVICE_ALIGNMENT";
        case GeoReferenceMethod::FROM_MAP:
            return "FROM_MAP";
        case GeoReferenceMethod::UNSET:
            return "UNSET";
    }
    throw std::invalid_argument("Unknown georeference method");
}

std::optional<GeoReferenceMethod> parseGeoReferenceMethod(const std::string& methodText)
{
    const std::string method = toUpper(methodText);
    if (method == "GNSS_FIT") {
        return GeoReferenceMethod::GNSS_FIT;
    }
    if (method == "MARKER_MEASURED") {
        return GeoReferenceMethod::MARKER_MEASURED;
    }
    if (method == "DEVICE_ALIGNMENT") {
        return GeoReferenceMethod::DEVICE_ALIGNMENT;
    }
    if (method == "FROM_MAP") {
        return GeoReferenceMethod::FROM_MAP;
    }
    return std::nullopt;
}

std::string toString(HeightSource source)
{
    switch (source) {
        case HeightSource::GNSS:
            return "GNSS";
        case HeightSource::MAPS:
            return "MAPS";
        case HeightSource::BUILDING_PLANS:
            return "BUILDING_PLANS";
        case HeightSource::UNKNOWN:
            return "UNKNOWN";
    }
    throw std::invalid_argument("Unknown height source");
}

std::optional<HeightSource> parseHeightSource(const std::string& sourceText)
{
    const std::string source = toUpper(sourceText);
    if (source == "GNSS") {
        return HeightSource::GNSS;
    }
    if (source == "MAPS") {
        return HeightSource::MAPS;
    }
    if (source == "BUILDING_PLANS") {
        return HeightSource::BUILDING_PLANS;
    }
    if (source == "UNKNOWN") {
        return HeightSource::UNKNOWN;
    }
    return std::nullopt;
}

std::string toString(GeoidModel model)
{
    switch (model) {
        case GeoidModel::RAF20:
            return "RAF20";
        case GeoidModel::EGM2008:
            return "EGM2008";
        case GeoidModel::EGM96:
            return "EGM96";
        case GeoidModel::DEVICE_BUILTIN:
            return "DEVICE_BUILTIN";
    }
    throw std::invalid_argument("Unknown geoid model");
}

std::optional<GeoidModel> parseGeoidModel(const std::string& modelText)
{
    const std::string model = toUpper(modelText);
    if (model == "RAF20") {
        return GeoidModel::RAF20;
    }
    if (model == "EGM2008") {
        return GeoidModel::EGM2008;
    }
    if (model == "EGM96") {
        return GeoidModel::EGM96;
    }
    if (model == "DEVICE_BUILTIN") {
        return GeoidModel::DEVICE_BUILTIN;
    }
    return std::nullopt;
}

Vector3d geodeticToEcef(const GeoPosition& position)
{
    const double lat = position.lat * SOLAR_DEG2RAD;
    const double lon = position.lon * SOLAR_DEG2RAD;
    const double sinLat = std::sin(lat);
    const double cosLat = std::cos(lat);
    const double n = WGS84_A / std::sqrt(1.0 - WGS84_E2 * sinLat * sinLat);
    return Vector3d((n + position.h) * cosLat * std::cos(lon),
                    (n + position.h) * cosLat * std::sin(lon),
                    (n * (1.0 - WGS84_E2) + position.h) * sinLat);
}

GeoPosition ecefToGeodetic(const Vector3d& ecef)
{
    const double x = ecef.x(), y = ecef.y(), z = ecef.z();
    const double p = std::sqrt(x * x + y * y);
    double lat = std::atan2(z, p * (1.0 - WGS84_E2));
    double n = WGS84_A;
    // Fixed-point iteration, well-behaved at the poles; converges to sub-millimetre in a few steps
    for (int i = 0; i < 10; ++i) {
        const double sinLat = std::sin(lat);
        n = WGS84_A / std::sqrt(1.0 - WGS84_E2 * sinLat * sinLat);
        const double newLat = std::atan2(z + WGS84_E2 * n * sinLat, p);
        const bool converged = std::abs(newLat - lat) < 1e-12;
        lat = newLat;
        if (converged) {
            break;
        }
    }
    const double sinLat = std::sin(lat);
    n = WGS84_A / std::sqrt(1.0 - WGS84_E2 * sinLat * sinLat);
    GeoPosition result;
    result.lat = lat * SOLAR_RAD2DEG;
    result.lon = std::atan2(y, x) * SOLAR_RAD2DEG;
    result.h = p * std::cos(lat) + (z + WGS84_E2 * n * sinLat) * sinLat - n;
    return result;
}

Maths::Matrix3d enuToEcefRotation(double lat_deg, double lon_deg)
{
    const double lat = lat_deg * SOLAR_DEG2RAD;
    const double lon = lon_deg * SOLAR_DEG2RAD;
    const double sLat = std::sin(lat), cLat = std::cos(lat);
    const double sLon = std::sin(lon), cLon = std::cos(lon);
    Maths::Matrix3d r;
    r << -sLon, -sLat * cLon, cLat * cLon,
          cLon, -sLat * sLon, cLat * sLon,
          0.0,   cLat,        sLat;
    return r;
}

GeoReference::GeoReference() : m_createdTime(nowIso8601Utc())
{
}

void GeoReference::setOriginGeoPose(const GeoPose& originGeoPose)
{
    m_originGeoPose = originGeoPose;
    // Normalize to absorb rounding errors (e.g. from float computations); a zero or non-finite
    // quaternion is kept as is so that isValid() reports it
    const double norm = m_originGeoPose.quaternion.norm();
    if (std::isfinite(norm) && norm > 0.0) {
        m_originGeoPose.quaternion.normalize();
    }
}

void GeoReference::setMethod(GeoReferenceMethod method, const std::string& sourceMapId)
{
    m_method = method;
    m_sourceMapId = sourceMapId;
}

bool GeoReference::isValid(std::string& error) const
{
    const GeoPosition& pos = m_originGeoPose.position;
    const Maths::Quaterniond& q = m_originGeoPose.quaternion;

    if (m_version != SCHEMA_VERSION) {
        error = "unsupported georef version " + std::to_string(m_version);
        return false;
    }
    if (!std::isfinite(pos.lat) || pos.lat < -90.0 || pos.lat > 90.0) {
        error = "latitude must be in [-90, 90] degrees";
        return false;
    }
    if (!std::isfinite(pos.lon) || pos.lon < -180.0 || pos.lon > 180.0) {
        error = "longitude must be in [-180, 180] degrees";
        return false;
    }
    if (!std::isfinite(pos.h)) {
        error = "height must be a finite number";
        return false;
    }
    if (!q.coeffs().allFinite() || std::abs(q.norm() - 1.0) > QUATERNION_NORM_TOLERANCE) {
        error = "origin quaternion must be a unit quaternion";
        return false;
    }
    if (m_method == GeoReferenceMethod::UNSET) {
        error = "method must be set";
        return false;
    }
    if (m_method == GeoReferenceMethod::FROM_MAP && m_sourceMapId.empty()) {
        error = "source_map_id is required when method is from_map";
        return false;
    }
    if (m_method != GeoReferenceMethod::FROM_MAP && !m_sourceMapId.empty()) {
        error = "source_map_id is only allowed when method is from_map";
        return false;
    }
    for (const auto& value : {m_accuracy.horizontal_m, m_accuracy.vertical_m, m_accuracy.heading_deg}) {
        if (value && (!std::isfinite(*value) || *value < 0.0)) {
            error = "accuracy values must be >= 0 or unknown";
            return false;
        }
    }
    const HeightSource heightSource = m_heightReference.source;
    if ((heightSource == HeightSource::MAPS || heightSource == HeightSource::BUILDING_PLANS)
        && !m_heightReference.conversion) {
        error = "height conversion is required when the height source is " + SolAR::datastructure::toString(heightSource);
        return false;
    }
    if (m_heightReference.conversion) {
        const HeightConversion& conv = *m_heightReference.conversion;
        if (conv.sourceDatum.empty()) {
            error = "height conversion source_datum must not be empty";
            return false;
        }
        if (!std::isfinite(conv.undulation_m) || !std::isfinite(conv.sourceValue_m)) {
            error = "height conversion values must be finite numbers";
            return false;
        }
        const double expected = conv.sourceValue_m + conv.undulation_m;
        if (std::abs(expected - pos.h) > HEIGHT_CONVERSION_TOLERANCE_M) {
            std::ostringstream oss;
            oss << "height h (" << pos.h << ") does not match source_value_m + undulation_m (" << expected << ")";
            error = oss.str();
            return false;
        }
    }
    if (!isIso8601Utc(m_createdTime)) {
        error = "created must be an ISO 8601 UTC time ending in 'Z'";
        return false;
    }
    error.clear();
    return true;
}

GeoPosition GeoReference::mapPointToGeodetic(const Vector3d& mapPoint) const
{
    const GeoPosition& origin = m_originGeoPose.position;
    const Vector3d enu = m_originGeoPose.quaternion.normalized() * mapPoint;
    return ecefToGeodetic(geodeticToEcef(origin) + enuToEcefRotation(origin.lat, origin.lon) * enu);
}

Vector3d GeoReference::geodeticToMapPoint(const GeoPosition& position) const
{
    const GeoPosition& origin = m_originGeoPose.position;
    const Vector3d enu = enuToEcefRotation(origin.lat, origin.lon).transpose()
                         * (geodeticToEcef(position) - geodeticToEcef(origin));
    return m_originGeoPose.quaternion.normalized().conjugate() * enu;
}

GeoPose GeoReference::mapPoseToGeoPose(const Transform3Df& mapPose) const
{
    const GeoPosition& origin = m_originGeoPose.position;
    GeoPose result;
    result.position = mapPointToGeodetic(mapPose.translation().cast<double>());
    // pose frame -> map -> ENU at origin -> ECEF -> ENU at the pose position
    const Maths::Matrix3d poseToMap = mapPose.linear().cast<double>();
    const Maths::Matrix3d poseToEnu = enuToEcefRotation(result.position.lat, result.position.lon).transpose()
                                      * enuToEcefRotation(origin.lat, origin.lon)
                                      * m_originGeoPose.quaternion.normalized().toRotationMatrix()
                                      * poseToMap;
    result.quaternion = Maths::Quaterniond(poseToEnu).normalized();
    return result;
}

Transform3Df GeoReference::geoPoseToMapPose(const GeoPose& geoPose) const
{
    const GeoPosition& origin = m_originGeoPose.position;
    // ENU at the pose position -> ECEF -> ENU at origin -> map (inverse of mapPoseToGeoPose)
    const Maths::Matrix3d poseToMap = m_originGeoPose.quaternion.normalized().toRotationMatrix().transpose()
                                      * enuToEcefRotation(origin.lat, origin.lon).transpose()
                                      * enuToEcefRotation(geoPose.position.lat, geoPose.position.lon)
                                      * geoPose.quaternion.normalized().toRotationMatrix();
    Transform3Df result = Transform3Df::Identity();
    result.linear() = poseToMap.cast<float>();
    result.translation() = geodeticToMapPoint(geoPose.position).cast<float>();
    return result;
}

nlohmann::json GeoReference::toJson() const
{
    const GeoPosition& pos = m_originGeoPose.position;
    const Maths::Quaterniond& q = m_originGeoPose.quaternion;

    nlohmann::json json;
    json["version"] = m_version;
    json["origin_geopose"] = {
        {"position", {{"lat", pos.lat}, {"lon", pos.lon}, {"h", pos.h}}},
        {"quaternion", {{"x", q.x()}, {"y", q.y()}, {"z", q.z()}, {"w", q.w()}}}
    };
    json["rotation"] = ROTATION_CONVENTION;
    json["method"] = SolAR::datastructure::toString(m_method);
    if (m_method == GeoReferenceMethod::FROM_MAP) {
        json["source_map_id"] = m_sourceMapId;
    }
    json["accuracy"] = {
        {"horizontal_m", optionalToJson(m_accuracy.horizontal_m)},
        {"vertical_m", optionalToJson(m_accuracy.vertical_m)},
        {"heading_deg", optionalToJson(m_accuracy.heading_deg)}
    };
    nlohmann::json heightRef = {
        {"h_type", HEIGHT_TYPE},
        {"source", SolAR::datastructure::toString(m_heightReference.source)},
        {"conversion", nullptr}
    };
    if (m_heightReference.conversion) {
        const HeightConversion& conv = *m_heightReference.conversion;
        heightRef["conversion"] = {
            {"source_datum", conv.sourceDatum},
            {"geoid_model", SolAR::datastructure::toString(conv.geoidModel)},
            {"undulation_m", conv.undulation_m},
            {"source_value_m", conv.sourceValue_m}
        };
    }
    json["height_ref"] = heightRef;
    json["created"] = m_createdTime;
    return json;
}

std::optional<GeoReference> GeoReference::fromJson(const nlohmann::json& json, std::string& error)
{
    GeoReference result;
    try {
        result.m_version = json.at("version").get<std::uint32_t>();
        if (result.m_version != SCHEMA_VERSION) {
            error = "unsupported georef version " + std::to_string(result.m_version);
            return std::nullopt;
        }

        const nlohmann::json& geopose = json.at("origin_geopose");
        const nlohmann::json& position = geopose.at("position");
        result.m_originGeoPose.position.lat = position.at("lat").get<double>();
        result.m_originGeoPose.position.lon = position.at("lon").get<double>();
        result.m_originGeoPose.position.h = position.at("h").get<double>();
        const nlohmann::json& quaternion = geopose.at("quaternion");
        result.m_originGeoPose.quaternion = Maths::Quaterniond(quaternion.at("w").get<double>(),
                                                               quaternion.at("x").get<double>(),
                                                               quaternion.at("y").get<double>(),
                                                               quaternion.at("z").get<double>());

        const std::string rotation = json.at("rotation").get<std::string>();
        if (rotation != ROTATION_CONVENTION) {
            error = "rotation must be \"" + std::string(ROTATION_CONVENTION) + "\", got \"" + rotation + "\"";
            return std::nullopt;
        }

        const std::string method = json.at("method").get<std::string>();
        const std::optional<GeoReferenceMethod> parsedMethod = parseGeoReferenceMethod(method);
        if (!parsedMethod) {
            error = "unknown method \"" + method + "\"";
            return std::nullopt;
        }
        result.m_method = *parsedMethod;
        if (json.contains("source_map_id") && !json.at("source_map_id").is_null()) {
            result.m_sourceMapId = json.at("source_map_id").get<std::string>();
        }

        const nlohmann::json& accuracy = json.at("accuracy");
        result.m_accuracy.horizontal_m = optionalFromJson(accuracy, "horizontal_m");
        result.m_accuracy.vertical_m = optionalFromJson(accuracy, "vertical_m");
        result.m_accuracy.heading_deg = optionalFromJson(accuracy, "heading_deg");

        const nlohmann::json& heightRef = json.at("height_ref");
        const std::string heightType = heightRef.at("h_type").get<std::string>();
        if (heightType != HEIGHT_TYPE) {
            error = "h_type must be \"" + std::string(HEIGHT_TYPE) + "\", got \"" + heightType + "\"";
            return std::nullopt;
        }
        const std::string source = heightRef.at("source").get<std::string>();
        const std::optional<HeightSource> parsedSource = parseHeightSource(source);
        if (!parsedSource) {
            error = "unknown height source \"" + source + "\"";
            return std::nullopt;
        }
        result.m_heightReference.source = *parsedSource;
        if (heightRef.contains("conversion") && !heightRef.at("conversion").is_null()) {
            const nlohmann::json& conversion = heightRef.at("conversion");
            HeightConversion conv;
            conv.sourceDatum = conversion.at("source_datum").get<std::string>();
            const std::string geoidModel = conversion.at("geoid_model").get<std::string>();
            const std::optional<GeoidModel> parsedGeoidModel = parseGeoidModel(geoidModel);
            if (!parsedGeoidModel) {
                error = "unknown geoid model \"" + geoidModel + "\"";
                return std::nullopt;
            }
            conv.geoidModel = *parsedGeoidModel;
            conv.undulation_m = conversion.at("undulation_m").get<double>();
            conv.sourceValue_m = conversion.at("source_value_m").get<double>();
            result.m_heightReference.conversion = conv;
        }

        result.m_createdTime = json.at("created").get<std::string>();
    }
    catch (const nlohmann::json::exception& e) {
        error = std::string("invalid georef JSON: ") + e.what();
        return std::nullopt;
    }

    if (!result.isValid(error)) {
        error = "invalid georef: " + error;
        return std::nullopt;
    }
    return result;
}

std::string GeoReference::toString() const
{
    const GeoPosition& pos = m_originGeoPose.position;
    const Maths::Quaterniond& q = m_originGeoPose.quaternion;
    std::ostringstream oss;
    oss.precision(10);
    oss << "Georeference (version " << m_version << "):\n"
        << "- origin: lat " << pos.lat << ", lon " << pos.lon << ", h " << pos.h << " m (ellipsoidal WGS-84)\n"
        << "- map_to_enu quaternion: x " << q.x() << ", y " << q.y() << ", z " << q.z() << ", w " << q.w() << "\n"
        << "- method: " << SolAR::datastructure::toString(m_method);
    if (m_method == GeoReferenceMethod::FROM_MAP) {
        oss << " (source map " << m_sourceMapId << ")";
    }
    oss << "\n- accuracy: horizontal " << optionalToString(m_accuracy.horizontal_m) << " m"
        << ", vertical " << optionalToString(m_accuracy.vertical_m) << " m"
        << ", heading " << optionalToString(m_accuracy.heading_deg) << " deg\n"
        << "- height source: " << SolAR::datastructure::toString(m_heightReference.source) << "\n";
    if (m_heightReference.conversion) {
        const HeightConversion& conv = *m_heightReference.conversion;
        oss << "- height conversion: " << conv.sourceValue_m << " m (" << conv.sourceDatum << ") + "
            << conv.undulation_m << " m (" << SolAR::datastructure::toString(conv.geoidModel) << ")\n";
    }
    oss << "- created: " << m_createdTime << "\n";
    return oss.str();
}

template <typename Archive>
void GeoReference::serialize(Archive &ar, const unsigned int /* version */)
{
    ar & m_version;
    ar & m_originGeoPose;
    ar & m_method;
    ar & m_sourceMapId;
    serializeOptional(ar, m_accuracy.horizontal_m);
    serializeOptional(ar, m_accuracy.vertical_m);
    serializeOptional(ar, m_accuracy.heading_deg);
    ar & m_heightReference;
    ar & m_createdTime;
}

IMPLEMENTSERIALIZE(GeoReference);

}
}
