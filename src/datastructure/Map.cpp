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
#include "xpcf/core/helpers.h"

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

Map::Map()
{	
	m_identification = xpcf::utils::make_shared<Identification>();
	m_coordinateSystem = xpcf::utils::make_shared<CoordinateSystem>();
	m_pointCloud = xpcf::utils::make_shared<PointCloud>();
	m_keyframeCollection = xpcf::utils::make_shared<KeyframeCollection>();
    m_cameraParametersCollection = xpcf::utils::make_shared<CameraParametersCollection>();
	m_covisibilityGraph = xpcf::utils::make_shared<CovisibilityGraph>();
	m_keyframeRetrieval = xpcf::utils::make_shared<KeyframeRetrieval>();
}

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
	m_keyframeCollection = keyframeCollection;
}

const SRef<CovisibilityGraph>& Map::getConstCovisibilityGraph() const
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
    m_mapSupportedTypes = m_mapSupportedTypes | MapType::_CameraParemeters;
    m_cameraParametersCollection = cameraParametersCollection;
}

TrackableType Map::getType() const
{
    return TrackableType::MAP;
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
}

IMPLEMENTSERIALIZE(Map);

}
}
