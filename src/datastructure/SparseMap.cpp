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

#include <datastructure/SparseMap.h>
#include "xpcf/core/helpers.h"

namespace SolAR {
namespace datastructure {

const SRef<PointCloud<FeatureCloudPoint>>& SparseMap::getConstPointCloud() const
{
	return m_pointCloud;
}

std::unique_lock<std::mutex> SparseMap::getPointCloud(SRef<PointCloud<FeatureCloudPoint>>& pointCloud)
{
	pointCloud = m_pointCloud;
	return m_pointCloud->acquireLock();
}

void SparseMap::setPointCloud(const SRef<PointCloud<FeatureCloudPoint>> pointCloud)
{
	m_pointCloud = pointCloud;
}

const SRef<KeyframeCollection>& SparseMap::getConstKeyframeCollection() const
{
	return m_keyframeCollection;
}

std::unique_lock<std::mutex> SparseMap::getKeyframeCollection(SRef<KeyframeCollection>& keyframeCollection)
{
	keyframeCollection = m_keyframeCollection;
	return m_keyframeCollection->acquireLock();
}

void SparseMap::setKeyframeCollection(const SRef<KeyframeCollection> keyframeCollection)
{
	m_keyframeCollection = keyframeCollection;
}

const SRef<CovisibilityGraph>& SparseMap::getConstCovisibilityGraph() const
{
	return m_covisibilityGraph;
}

std::unique_lock<std::mutex> SparseMap::getCovisibilityGraph(SRef<CovisibilityGraph>& covisibilityGraph)
{
	covisibilityGraph = m_covisibilityGraph;
	return m_covisibilityGraph->acquireLock();
}

void SparseMap::setCovisibilityGraph(const SRef<CovisibilityGraph> covisibilityGraph)
{
	m_covisibilityGraph = covisibilityGraph;
}

const SRef<KeyframeRetrieval>& SparseMap::getConstKeyframeRetrieval() const
{
	return m_keyframeRetrieval;
}

std::unique_lock<std::mutex> SparseMap::getKeyframeRetrieval(SRef<KeyframeRetrieval>& keyframeRetrieval)
{
	keyframeRetrieval = m_keyframeRetrieval;
	return m_keyframeRetrieval->acquireLock();
}

void SparseMap::setKeyframeRetrieval(const SRef<KeyframeRetrieval> keyframeRetrieval)
{
	m_keyframeRetrieval = keyframeRetrieval;
}

template<typename Archive>
void Identification::serialize(ATTRIBUTE(maybe_unused) Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
	ar & boost::serialization::base_object<Map>(*this);
	ar & m_pointCloud;
	ar & m_keyframeCollection;
	ar & m_covisibilityGraph;
	ar & m_keyframeRetrieval;
}

IMPLEMENTSERIALIZE(SparseMap);

}
}
