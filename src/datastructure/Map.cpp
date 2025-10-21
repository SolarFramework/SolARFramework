/**
 * @copyright Copyright (c) 2017 B-com http://www.b-com.com/
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

#include <datastructure/Map.h>
#include "xpcf/component/ComponentFactory.h"
#include <xpcf/core/helpers.h>

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::Map);

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

const SRef<Identification>& Map::getConstIdentification() const
{
	return m_identification;
}

std::unique_lock<std::mutex> Map::getIdentification(SRef<Identification>& identification)
{
	identification = m_identification;
	return m_identification->acquireLock();
}

void Map::setIdentification(const SRef<Identification> identification)
{
	m_identification = identification;
}

const SRef<CoordinateSystem>& Map::getConstCoordinateSystem() const
{
	return m_coordinateSystem;
}

std::unique_lock<std::mutex> Map::getCoordinateSystem(SRef<CoordinateSystem>& coordinateSystem)
{
	coordinateSystem = m_coordinateSystem;
	return m_coordinateSystem->acquireLock();
}

void Map::setCoordinateSystem(const SRef<CoordinateSystem> coordinateSystem)
{
	m_coordinateSystem = coordinateSystem;
}

const SRef<PointCloud>& Map::getConstPointCloud() const
{
	return m_pointCloud;
}

std::unique_lock<std::mutex> Map::getPointCloud(SRef<PointCloud>& pointCloud)
{
	pointCloud = m_pointCloud;
	return m_pointCloud->acquireLock();
}

void Map::setPointCloud(const SRef<PointCloud> pointCloud)
{
	m_mapSupportedTypes = m_mapSupportedTypes | MapType::_PointCloud;
	m_pointCloud = pointCloud;
}

const SRef<KeyframeCollection>& Map::getConstKeyframeCollection() const
{
	return m_keyframeCollection;
}

std::unique_lock<std::mutex> Map::getKeyframeCollection(SRef<KeyframeCollection>& keyframeCollection)
{
	keyframeCollection = m_keyframeCollection;
	return m_keyframeCollection->acquireLock();
}

void Map::setKeyframeCollection(const SRef<KeyframeCollection> keyframeCollection)
{
    m_mapSupportedTypes = m_mapSupportedTypes | MapType::_Keyframe;

    // Check if keyframe images must be embedded
    if (m_embedKeyframeImages) {
        m_keyframeCollection = keyframeCollection;
    }
    else {
        // Remove keyframe images
        m_keyframeCollection = xpcf::utils::make_shared<KeyframeCollection>();
        m_keyframeCollection->setDescriptorType(keyframeCollection->getDescriptorType());
        std::vector<SRef<Keyframe>> keyframesWithoutImages;
        keyframeCollection->getAllKeyframesWithoutImages(keyframesWithoutImages);
        for (const auto& kf: keyframesWithoutImages) {
            m_keyframeCollection->addKeyframe(kf, false);
        }
    }
}

const SRef<CovisibilityGraph> Map::getConstCovisibilityGraph() const
{
	return m_covisibilityGraph;
}

std::unique_lock<std::mutex> Map::getCovisibilityGraph(SRef<CovisibilityGraph>& covisibilityGraph)
{
	covisibilityGraph = m_covisibilityGraph;
	return m_covisibilityGraph->acquireLock();
}

void Map::setCovisibilityGraph(const SRef<CovisibilityGraph> covisibilityGraph)
{
	m_mapSupportedTypes = m_mapSupportedTypes | MapType::_CovisibilityGraph;
	m_covisibilityGraph = covisibilityGraph;
}

const SRef<KeyframeRetrieval>& Map::getConstKeyframeRetrieval() const
{
	return m_keyframeRetrieval;
}

std::unique_lock<std::mutex> Map::getKeyframeRetrieval(SRef<KeyframeRetrieval>& keyframeRetrieval)
{
	keyframeRetrieval = m_keyframeRetrieval;
	return m_keyframeRetrieval->acquireLock();
}

void Map::setKeyframeRetrieval(const SRef<KeyframeRetrieval> keyframeRetrieval)
{
	m_mapSupportedTypes = m_mapSupportedTypes | MapType::_KFRetriever;
	m_keyframeRetrieval = keyframeRetrieval;
}

const SRef<CameraParametersCollection>& Map::getConstCameraParametersCollection() const
{
    return m_cameraParametersCollection;
}

std::unique_lock<std::mutex> Map::getCameraParametersCollection(SRef<CameraParametersCollection>& cameraParametersCollection)
{
    cameraParametersCollection = m_cameraParametersCollection;
    return m_cameraParametersCollection->acquireLock();
}

void Map::setCameraParametersCollection(const SRef<CameraParametersCollection> cameraParametersCollection)
{
    m_mapSupportedTypes = m_mapSupportedTypes | MapType::_CameraParameters;
    m_cameraParametersCollection = cameraParametersCollection;
}

TrackableType Map::getType() const
{
    return TrackableType::MAP;
}

void Map::setVersion(const std::string & version)
{
    m_version = version;
}

void Map::setDescriptorType(const datastructure::DescriptorType & descriptorType)
{
    m_descriptorType = descriptorType;
}

void Map::setGlobalDescriptorType(const datastructure::GlobalDescriptorType & globalDescriptorType)
{
    m_globalDescriptorType = globalDescriptorType;
}

bool Map::getInformation(std::string & version,
                         datastructure::DescriptorType & descriptorType,
                         datastructure::GlobalDescriptorType & globalDescriptorType) const
{
    if (m_version.empty()) {
        return false;
    }
    version = m_version;
    descriptorType = m_descriptorType;
    globalDescriptorType= m_globalDescriptorType;
    return true;
}

void Map::embedKeyframeImages()
{
    m_embedKeyframeImages = true;
}

bool Map::hasKeyframeImages() const
{
    return m_embedKeyframeImages;
}

SRef<Map> Map::copyWithoutKeyframeImages() const
{
    SRef<Map> mapWithoutKeyframeImages = xpcf::utils::make_shared<Map>();

    mapWithoutKeyframeImages->setTransform3D(m_transform3D);

    SRef<Identification> copyIdentification = mapWithoutKeyframeImages->getConstIdentification();
    copyIdentification->setUUID(m_identification->getUUID());
    copyIdentification->setName(m_identification->getName());
    copyIdentification->setAuthor(m_identification->getAuthor());
    copyIdentification->setCreatedTime(m_identification->getCreatedTime());
    copyIdentification->setLastUpdateTime(m_identification->getLastUpdateTime());
    copyIdentification->setBBox3D(m_identification->getBBox3D());

    SRef<CoordinateSystem> copyCoordinateSystem = mapWithoutKeyframeImages->getConstCoordinateSystem();
    copyCoordinateSystem->setAbsolutePosition(m_coordinateSystem->getAbsolutePosition());
    copyCoordinateSystem->setAbsoluteRotation(m_coordinateSystem->getAbsoluteRotation());
    copyCoordinateSystem->setParentId(m_coordinateSystem->getParentId());
    copyCoordinateSystem->setParentTransform(m_coordinateSystem->getParentTransform());

    SRef<PointCloud> copyPointCloud = mapWithoutKeyframeImages->getConstPointCloud();
    copyPointCloud->setDescriptorType(m_pointCloud->getDescriptorType());
    std::vector<SRef<CloudPoint>> srefPoints;
    m_pointCloud->getAllPoints(srefPoints);
    std::vector<CloudPoint> points;
    for (const auto & pt: srefPoints) {
        points.push_back(*pt);
    }
    copyPointCloud->addPoints(points, false);

    SRef<KeyframeCollection> copyKeyframeCollection = mapWithoutKeyframeImages->getConstKeyframeCollection();
    SRef<KeyframeRetrieval> copyKeyframeRetrieval = mapWithoutKeyframeImages->getConstKeyframeRetrieval();
    copyKeyframeCollection->setDescriptorType(m_keyframeCollection->getDescriptorType());
    std::vector<SRef<Keyframe>> keyframesWithoutImages;
    m_keyframeCollection->getAllKeyframesWithoutImages(keyframesWithoutImages);
    for (const auto & kf: keyframesWithoutImages) {
        copyKeyframeCollection->addKeyframe(kf, false);
        uint32_t kfID = kf->getId();
        BoWFeature bowDesc;
        m_keyframeRetrieval->getBoWFeature(kfID, bowDesc);
        BoWLevelFeature bowLevelDesc;
        m_keyframeRetrieval->getBoWLevelFeature(kfID, bowLevelDesc);
        copyKeyframeRetrieval->addDescriptor(kfID, bowDesc, bowLevelDesc);
    }

    SRef<CovisibilityGraph> copyCovisibilityGraph = mapWithoutKeyframeImages->getConstCovisibilityGraph();
    std::set<uint32_t> nodesID;
    m_covisibilityGraph->getAllNodes(nodesID);
    for (const auto & nID: nodesID) {
        std::vector<uint32_t> neighbors;
        m_covisibilityGraph->getNeighbors(nID, 0, neighbors);
        for (const auto & nb: neighbors) {
            float weight;
            m_covisibilityGraph->getEdge(nID, nb, weight);
            copyCovisibilityGraph->increaseEdge(nID, nb, weight);
        }
    }

    SRef<CameraParametersCollection> copyCameraParametersCollection = mapWithoutKeyframeImages->getConstCameraParametersCollection();
    std::vector<SRef<CameraParameters>> cameraParameters;
    m_cameraParametersCollection->getAllCameraParameters(cameraParameters);
    for (const auto & camParam: cameraParameters) {
        CameraParameters copyCamParam;
        copyCamParam.name = camParam->name;
        copyCamParam.id = camParam->id;
        copyCamParam.type = camParam->type;
        copyCamParam.resolution = camParam->resolution;
        copyCamParam.intrinsic = camParam->intrinsic;
        copyCamParam.distortion = camParam->distortion;
        copyCamParam.extrinsics = camParam->extrinsics;
        copyCameraParametersCollection->addCameraParameters(copyCamParam, false);
    }

    mapWithoutKeyframeImages->setVersion(m_version);
    mapWithoutKeyframeImages->setDescriptorType(m_descriptorType);
    mapWithoutKeyframeImages->setGlobalDescriptorType(m_globalDescriptorType);
    if (m_embedKeyframeImages) {
        mapWithoutKeyframeImages->embedKeyframeImages();
    }

    return mapWithoutKeyframeImages;
}

bool Map::isMapCompatible(datastructure::DescriptorType descriptorType,
                          datastructure::GlobalDescriptorType globalDescriptorType) const
{
    LOG_DEBUG("Get map information");
    std::string mapVersion;
    datastructure::DescriptorType mapDescriptorType;
    datastructure::GlobalDescriptorType mapGlobalDescriptorType;
    if (!getInformation(mapVersion, mapDescriptorType, mapGlobalDescriptorType)) {
        LOG_ERROR("Cannot get map information");
        return false;
    }

    LOG_DEBUG("Test map compatibility");
    if (mapVersion != SolAR::VERSION) {
        LOG_WARNING("The version of the map ({}) is not compatible with the framework version ({})", mapVersion, SolAR::VERSION);
        return false;
    }
    if (mapDescriptorType != descriptorType) {
        LOG_WARNING("The descriptor type used for the map ({}) is not compatible with the service configuration ({})", toString(mapDescriptorType), toString(descriptorType));
        return false;
    }
    if (mapGlobalDescriptorType != globalDescriptorType) {
        LOG_WARNING("The global descriptor type used for the map ({}) is not compatible with the service configuration ({})", toString(mapGlobalDescriptorType), toString(globalDescriptorType));
        return false;
    }

    return true;
}


template<typename Archive>
void Map::serialize(Archive &ar, const unsigned int /* version */) {
	ar & m_mapSupportedTypes;
	ar & m_identification;
	ar & m_coordinateSystem;
	ar & m_pointCloud;
	ar & m_keyframeCollection;
	ar & m_covisibilityGraph;
	ar & m_keyframeRetrieval;
    ar & m_cameraParametersCollection;
	ar & m_transform3D;
    ar & m_version;
    ar & m_descriptorType;
    ar & m_globalDescriptorType;
    ar & m_embedKeyframeImages;
}

IMPLEMENTSERIALIZE(Map);

}
}
