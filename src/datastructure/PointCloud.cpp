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

#include "datastructure/PointCloud.h"
#include "xpcf/core/helpers.h"
#include "core/Log.h"

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

FrameworkReturnCode SparsePointCloud::addPoint(const SRef<CloudPoint> point)
{
	point->setId(m_id);
	m_pointCloud[m_id] = point;
	m_id++;
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode SparsePointCloud::addPoints(const std::vector<SRef<CloudPoint>>& points)
{
	for (auto &it : points) {
		it->setId(m_id);
		m_pointCloud[m_id] = it;
		m_id++;
	}
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode SparsePointCloud::addPoint(const CloudPoint & point)
{
	SRef<CloudPoint> point_ptr = xpcf::utils::make_shared<CloudPoint>(point);
	point_ptr->setId(m_id);
	m_pointCloud[m_id] = point_ptr;
	m_id++;
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode SparsePointCloud::addPoints(const std::vector<CloudPoint>& points)
{
	for (auto &it : points) {
		SRef<CloudPoint> point_ptr = xpcf::utils::make_shared<CloudPoint>(it);
		point_ptr->setId(m_id);
		m_pointCloud[m_id] = point_ptr;
		m_id++;
	}
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode SparsePointCloud::getPoint(const uint32_t id, SRef<CloudPoint>& point) const
{
	std::map< uint32_t, SRef<CloudPoint>>::const_iterator pointIt = m_pointCloud.find(id);
	if (pointIt != m_pointCloud.end()) {
		point = pointIt->second;
		return FrameworkReturnCode::_SUCCESS;
	}
	else {
		LOG_DEBUG("Cannot find cloud point with id {} to get", id);
		return FrameworkReturnCode::_ERROR_;
	}
}

FrameworkReturnCode SparsePointCloud::getPoints(const std::vector<uint32_t>& ids, std::vector<SRef<CloudPoint>>& points) const
{
	for (auto &it : ids) {
		std::map< uint32_t, SRef<CloudPoint>>::const_iterator pointIt = m_pointCloud.find(it);
		if (pointIt == m_pointCloud.end()) {
			LOG_DEBUG("Cannot find cloud point with id {} to get", it);
			return FrameworkReturnCode::_ERROR_;
		}
		points.push_back(pointIt->second);
	}
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode SparsePointCloud::getAllPoints(std::vector<SRef<CloudPoint>>& points) const
{
	for (auto pointIt = m_pointCloud.begin(); pointIt != m_pointCloud.end(); pointIt++)
		points.push_back(pointIt->second);
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode SparsePointCloud::suppressPoint(const uint32_t id)
{
	std::map< uint32_t, SRef<CloudPoint>>::iterator pointIt = m_pointCloud.find(id);
	if (pointIt != m_pointCloud.end()) {
		m_pointCloud.erase(pointIt);
		return FrameworkReturnCode::_SUCCESS;
	}
	else {
		LOG_DEBUG("Cannot find cloud point with id {} to suppress", id);
		return FrameworkReturnCode::_ERROR_;
	}
}

FrameworkReturnCode SparsePointCloud::suppressPoints(const std::vector<uint32_t>& ids)
{
	for (auto &it : ids) {
		std::map< uint32_t, SRef<CloudPoint>>::iterator pointIt = m_pointCloud.find(it);
		if (pointIt == m_pointCloud.end()) {
			LOG_DEBUG("Cannot find cloud point with id {} to suppress", it);
			return FrameworkReturnCode::_ERROR_;
		}
		m_pointCloud.erase(pointIt);
	}
	return FrameworkReturnCode::_SUCCESS;
}

DescriptorType SparsePointCloud::getDescriptorType() const
{
	return m_descriptorType;
}

FrameworkReturnCode SparsePointCloud::setDescriptorType(const DescriptorType & type)
{
	m_descriptorType = type;
	return FrameworkReturnCode::_SUCCESS;
}

bool SparsePointCloud::isExistPoint(const uint32_t id) const
{
	if (m_pointCloud.find(id) != m_pointCloud.end())
		return true;
	else
		return false;
}

int SparsePointCloud::getNbPoints() const
{
	return static_cast<int>(m_pointCloud.size());
}

template <typename Archive>
void SparsePointCloud::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version)
{
	ar & m_id;
	ar & m_descriptorType;
	ar & m_pointCloud;
}

IMPLEMENTSERIALIZE(SparsePointCloud);

} // end of namespace datastructure
} // end of namespace SolAR
