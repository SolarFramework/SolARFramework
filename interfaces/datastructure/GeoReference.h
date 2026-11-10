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

#ifndef SOLAR_GEOREFERENCE_H
#define SOLAR_GEOREFERENCE_H

#include <core/SerializationDefinitions.h>
#include <core/SolARFrameworkDefinitions.h>
#include <datastructure/MathDefinitions.h>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace SolAR {
namespace datastructure {

/**
 * @struct GeoPosition
 * @brief <B>A position on the WGS-84 ellipsoid.</B>
 */
struct GeoPosition {
    double lat = 0.0;   ///< latitude in degrees, in [-90, 90]
    double lon = 0.0;   ///< longitude in degrees, in [-180, 180]
    double h = 0.0;     ///< height in metres above the WGS-84 ellipsoid

    /**
     * @brief Boost serialization of the position
     * @param[in,out] ar the archive to save to or load from
     * @param[in] version the version of the archive (unused)
     */
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int /* version */) { ar & lat; ar & lon; ar & h; }
};

/**
 * @struct GeoPose
 * @brief <B>A geopose (OGC GeoPose "Basic-Quaternion"): a WGS-84 position plus an orientation
 * expressed relative to the local East-North-Up frame at that position.</B>
 */
struct GeoPose {
    GeoPosition position;                                               ///< WGS-84 position
    Maths::Quaterniond quaternion = Maths::Quaterniond::Identity();     ///< orientation relative to the local East-North-Up frame
};

/**
 * @enum GeoReferenceMethod
 * @brief <B>How the georeference was obtained.</B>
 */
enum class GeoReferenceMethod : std::uint8_t {
    GNSS_FIT,           ///< fitted from GNSS readings ("gnss_fit")
    MARKER_MEASURED,    ///< from markers with surveyed positions ("marker_measured")
    DEVICE_ALIGNMENT,   ///< from the capture device's own geo alignment ("device_alignment")
    FROM_MAP            ///< inherited from another georeferenced map ("from_map")
};

/**
 * @brief GeoReferenceMethod to string
 * @param[in] method the GeoReferenceMethod to convert
 * @return the schema string: "gnss_fit", "marker_measured", "device_alignment" or "from_map"
 * @throws std::invalid_argument if the value is not a valid GeoReferenceMethod
 */
std::string toString(GeoReferenceMethod method);

/**
 * @brief String to GeoReferenceMethod
 * @param[in] method the schema string to parse, e.g. "gnss_fit"
 * @return the parsed value, or std::nullopt if the string is not a known value
 */
std::optional<GeoReferenceMethod> parseGeoReferenceMethod(const std::string& method);

/**
 * @enum HeightSource
 * @brief <B>Where the height value came from.</B>
 */
enum class HeightSource : std::uint8_t {
    GNSS,               ///< "gnss"
    MAPS,               ///< "maps"
    BUILDING_PLANS,     ///< "building_plans"
    UNKNOWN             ///< "unknown"
};

/**
 * @brief HeightSource to string
 * @param[in] source the HeightSource to convert
 * @return the schema string: "gnss", "maps", "building_plans" or "unknown"
 * @throws std::invalid_argument if the value is not a valid HeightSource
 */
std::string toString(HeightSource source);

/**
 * @brief String to HeightSource
 * @param[in] source the schema string to parse, e.g. "maps"
 * @return the parsed value, or std::nullopt if the string is not a known value
 */
std::optional<HeightSource> parseHeightSource(const std::string& source);

/**
 * @enum GeoidModel
 * @brief <B>Geoid model used to convert a non-ellipsoidal altitude into an ellipsoidal height.</B>
 */
enum class GeoidModel : std::uint8_t {
    RAF20,              ///< "RAF20"
    EGM2008,            ///< "EGM2008"
    EGM96,              ///< "EGM96"
    DEVICE_UNSPECIFIED  ///< "device_unspecified"
};

/**
 * @brief GeoidModel to string
 * @param[in] model the GeoidModel to convert
 * @return the schema string: "RAF20", "EGM2008", "EGM96" or "device_unspecified"
 * @throws std::invalid_argument if the value is not a valid GeoidModel
 */
std::string toString(GeoidModel model);

/**
 * @brief String to GeoidModel
 * @param[in] model the schema string to parse, e.g. "RAF20"
 * @return the parsed value, or std::nullopt if the string is not a known value
 */
std::optional<GeoidModel> parseGeoidModel(const std::string& model);

/**
 * @struct GeoAccuracy
 * @brief <B>Accuracy of the georeference; an unset value means unknown.</B>
 */
struct GeoAccuracy {
    std::optional<double> horizontal_m;     ///< horizontal accuracy in metres, >= 0
    std::optional<double> vertical_m;       ///< vertical accuracy in metres, >= 0
    std::optional<double> heading_deg;      ///< heading accuracy in degrees, >= 0
};

/**
 * @struct HeightConversion
 * @brief <B>Conversion of an original altitude into an ellipsoidal height: h = sourceValue_m + undulation_m.</B>
 */
struct HeightConversion {
    std::string sourceDatum;                                ///< e.g. "NGF-IGN69", "msl", or another national datum name
    GeoidModel geoidModel = GeoidModel::DEVICE_UNSPECIFIED; ///< geoid model giving the undulation
    double undulation_m = 0.0;                              ///< geoid undulation N in metres
    double sourceValue_m = 0.0;                             ///< original altitude in metres
};

/**
 * @struct HeightReference
 * @brief <B>Reference of the height. The height type is always ellipsoidal WGS-84.</B>
 */
struct HeightReference {
    HeightSource source = HeightSource::UNKNOWN;    ///< where the height value came from
    std::optional<HeightConversion> conversion;     ///< how the height was converted; required for MAPS and BUILDING_PLANS, optional otherwise
};

/**
 * @class GeoReference
 * @brief <B>Ties a map coordinate system to the Earth (WGS-84).</B>
 *
 * The map origin is located at the origin geopose position, and the origin geopose quaternion
 * rotates map-frame vectors into the local East-North-Up frame at that position ("map_to_enu").
 * The map is assumed to be metric (1 map unit = 1 metre).
 *
 * The JSON form (toJson / fromJson) follows the "georef" schema, version 1.
 */
class SOLARFRAMEWORK_API GeoReference {
public:
    /// @brief Current version of the georef schema
    static constexpr std::uint32_t SCHEMA_VERSION = 1;

    /// @brief Maximum allowed deviation of the origin quaternion norm from 1
    static constexpr double QUATERNION_NORM_TOLERANCE = 1e-6;
    
    /// @brief Maximum allowed difference in metres between h and sourceValue_m + undulation_m
    static constexpr double HEIGHT_CONVERSION_TOLERANCE_M = 0.001;

    /**
     * @brief GeoReference constructor. The creation time is set to now
     */
    GeoReference();

    /**
     * @brief GeoReference default destructor
     */
    ~GeoReference() = default;

    /**
     * @brief Get the version of the georef schema
     * @return the schema version
     */
    std::uint32_t getVersion() const { return m_version; }

    /**
     * @brief Get the geopose of the map origin
     * @return the origin geopose
     */
    const GeoPose& getOriginGeoPose() const { return m_originGeoPose; }

    /**
     * @brief Set the geopose of the map origin
     * @param[in] originGeoPose the origin position and the map_to_enu rotation
     */
    void setOriginGeoPose(const GeoPose& originGeoPose) { m_originGeoPose = originGeoPose; }

    /**
     * @brief Get the method used to obtain the georeference
     * @return the method
     */
    GeoReferenceMethod getMethod() const { return m_method; }

    /**
     * @brief Set the method used to obtain the georeference
     * @param[in] method the method
     * @param[in] sourceMapId the identifier of the source map: required for FROM_MAP, must be empty otherwise
     */
    void setMethod(GeoReferenceMethod method, const std::string& sourceMapId = "");

    /**
     * @brief Get the identifier of the map the georeference was inherited from
     * @return the source map identifier, empty unless the method is FROM_MAP
     */
    const std::string& getSourceMapId() const { return m_sourceMapId; }

    /**
     * @brief Get the accuracy of the georeference
     * @return the accuracy
     */
    const GeoAccuracy& getAccuracy() const { return m_accuracy; }

    /**
     * @brief Set the accuracy of the georeference
     * @param[in] accuracy the accuracy, with unset values for unknown ones
     */
    void setAccuracy(const GeoAccuracy& accuracy) { m_accuracy = accuracy; }

    /**
     * @brief Get the reference of the origin height
     * @return the height reference
     */
    const HeightReference& getHeightReference() const { return m_heightReference; }

    /**
     * @brief Set the reference of the origin height
     * @param[in] heightReference the height reference
     */
    void setHeightReference(const HeightReference& heightReference) { m_heightReference = heightReference; }

    /**
     * @brief Get the creation time of the georeference
     * @return the creation time, ISO 8601 in UTC ending in "Z"
     */
    const std::string& getCreatedTime() const { return m_createdTime; }

    /**
     * @brief Set the creation time of the georeference
     * @param[in] createdTime the creation time, ISO 8601 in UTC ending in "Z" (e.g. "2026-11-10T14:30:00Z")
     */
    void setCreatedTime(const std::string& createdTime) { m_createdTime = createdTime; }

    /**
     * @brief Check the georeference against the schema rules
     * @param[out] error description of the first violated rule, empty if valid
     * @return true if valid
     */
    bool isValid(std::string& error) const;

    /**
     * @brief Convert a point from the map frame to WGS-84
     * @param[in] mapPoint the point in the map frame, in metres
     * @return the WGS-84 position of the point
     */
    GeoPosition mapPointToGeodetic(const Vector3d& mapPoint) const;

    /**
     * @brief Convert a WGS-84 position to a point in the map frame
     * @param[in] position the WGS-84 position
     * @return the point in the map frame, in metres
     */
    Vector3d geodeticToMapPoint(const GeoPosition& position) const;

    /**
     * @brief Convert a pose in the map frame (e.g. a camera pose) to a geopose
     * @param[in] mapPose the pose in the map frame (pose frame to map frame)
     * @return the geopose, whose orientation is relative to the local East-North-Up frame at the pose position
     */
    GeoPose mapPoseToGeoPose(const Transform3Df& mapPose) const;

    /**
     * @brief Serialize to the "georef" JSON object
     * @return the JSON object
     */
    nlohmann::json toJson() const;

    /**
     * @brief Parse a "georef" JSON object and validate it
     * @param[in] json the JSON object
     * @return the georeference
     * @throws std::invalid_argument if the object does not follow the schema
     */
    static GeoReference fromJson(const nlohmann::json& json);

    /**
     * @brief Get a human-readable description of the georeference
     * @return the description
     */
    std::string toString() const;

private:
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    std::uint32_t       m_version = SCHEMA_VERSION;
    GeoPose             m_originGeoPose;
    GeoReferenceMethod  m_method = GeoReferenceMethod::GNSS_FIT;
    std::string         m_sourceMapId;      // only set when m_method is FROM_MAP
    GeoAccuracy         m_accuracy;
    HeightReference     m_heightReference;
    std::string         m_createdTime;
};

/**
 * @brief Convert a WGS-84 geodetic position to Earth-Centred Earth-Fixed coordinates
 * @param[in] position the WGS-84 position
 * @return the ECEF coordinates, in metres
 */
Vector3d geodeticToEcef(const GeoPosition& position);

/**
 * @brief Convert Earth-Centred Earth-Fixed coordinates to a WGS-84 geodetic position
 * @param[in] ecef the ECEF coordinates, in metres
 * @return the WGS-84 position
 */
GeoPosition ecefToGeodetic(const Vector3d& ecef);

/**
 * @brief Get the rotation from the local East-North-Up frame to Earth-Centred Earth-Fixed
 * @param[in] lat_deg latitude in degrees
 * @param[in] lon_deg longitude in degrees
 * @return the rotation, whose columns are the East, North and Up axes expressed in ECEF
 */
Maths::Matrix3d enuToEcefRotation(double lat_deg, double lon_deg);

DECLARESERIALIZE(GeoReference);

}
}  // end of namespace SolAR

#endif // SOLAR_GEOREFERENCE_H
