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
#ifndef POINTCLOUD_H
#define EPOINTCLOUD_H

#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/CloudPoint.h"
#include "datastructure/FeatureCloudPoint.h"
#include "datastructure/Lockable.h"
#include "core/Messages.h"
#include "xpcf/core/refs.h"
#include <map>

// Definition of PointCloud Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
* @class PointCloud
* @brief <B>A 3D cloud composed of multiple cloud points.</B>
* This class provides a point cloud.
*/
template <class T>
class  SOLARFRAMEWORK_API PointCloud : public Lockable {
public:

	///
	/// @brief PointCloud constructor.
	///
	PointCloud() = default;
	PointCloud(const PointCloud& other) = default;
	PointCloud& operator=(const PointCloud& other) = default;

	///
	/// @brief ~PointCloud
	///
	~PointCloud() = default;

	/// @brief This method allow to add a 3D point to the point cloud
	/// @param[in] point the 3D point to add to the persistent point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode addPoint(const SRef<T> point);

	/// @brief This method allow to add a vector of 3D points to the point cloud
	/// @param[in] a vector of the 3D points to add to the persistent point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode addPoints(const std::vector<SRef<T>>& points);

	/// @brief This method allow to add a 3D point to the point cloud
	/// @param[in] point the 3D point to add to the persistent point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode addPoint(const T &point);

	/// @brief This method allow to add a vector of 3D points to the point cloud
	/// @param[in] a vector of the 3D points to add to the persistent point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode addPoints(const std::vector<T> &points);

	/// @brief This method allows to get a 3D point stored in the point cloud by its id
	/// @param[in] id of the point to get
	/// @param[out] a 3D point stored in the point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode getPoint(const uint32_t id, SRef<T>& point) const;

	/// @brief This method allows to get a set of 3D points stored in the point cloud by their ids
	/// @param[in] a vector of ids of the points to get
	/// @param[out] a vector of 3D points stored in the point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode getPoints(const std::vector<uint32_t> &ids, std::vector<SRef<T>>& points) const;

	/// @brief This method allows to get all 3D points stored in the point cloud
	/// @param[out] the set of 3D point stored in the point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode getAllPoints(std::vector<SRef<T>>& points) const;

	/// @brief This method allow to suppress a point stored in the point cloud by its id
	/// @param[in] id of the point to suppress
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode suppressPoint(const uint32_t id);

	/// @brief This method allow to suppress a vector of points stored in the point cloud by their ids
	/// @param[in] ids the vector of ids of the point to suppress
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
	FrameworkReturnCode suppressPoints(const std::vector<uint32_t> & ids);

	/// @brief This method allows to know if a point is already stored in the component
	/// @param[in] Id of this point
	/// @return true if exist, else false
	bool isExistPoint(const uint32_t id) const;

	/// @brief This method allows to get the number of points stored in the point cloud
	/// @return The number of points
	int getNbPoints() const;

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & m_id;
		ar & m_pointCloud;
	}

	std::map<uint32_t, SRef<T>>	m_pointCloud;
	uint32_t					m_id;
};

template<class T>
inline FrameworkReturnCode PointCloud<T>::addPoint(const SRef<T> point)
{
	point->setId(m_id);
	m_pointCloud[m_id] = point;
	m_id++;
	return FrameworkReturnCode::_SUCCESS;
}

template<class T>
inline FrameworkReturnCode PointCloud<T>::addPoints(const std::vector<SRef<T>>& points)
{
	for (auto &it : points) {
		it->setId(m_id);
		m_pointCloud[m_id] = it;
		m_id++;
	}
	return FrameworkReturnCode::_SUCCESS;
}

template<class T>
inline FrameworkReturnCode PointCloud<T>::addPoint(const T & point)
{
	SRef<T> point_ptr = xpcf::utils::make_shared<T>(point);
	point_ptr->setId(m_id);
	m_pointCloud[m_id] = point_ptr;
	m_id++;
	return FrameworkReturnCode::_SUCCESS;
}

template<class T>
inline FrameworkReturnCode PointCloud<T>::addPoints(const std::vector<T>& points)
{
	for (auto &it : points) {
		SRef<T> point_ptr = xpcf::utils::make_shared<T>(it);
		point_ptr->setId(m_id);
		m_pointCloud[m_id] = point_ptr;
		m_id++;
	}
	return FrameworkReturnCode::_SUCCESS;
}

template<class T>
inline FrameworkReturnCode PointCloud<T>::getPoint(const uint32_t id, SRef<T>& point) const
{
	auto pointIt = m_pointCloud.find(id);
	if (pointIt != m_pointCloud.end()) {
		point = pointIt->second;
		return FrameworkReturnCode::_SUCCESS;
	}
	else {
		LOG_DEBUG("Cannot find cloud point with id {} to get", id);
		return FrameworkReturnCode::_ERROR_;
	}
}

template<class T>
inline FrameworkReturnCode PointCloud<T>::getPoints(const std::vector<uint32_t>& ids, std::vector<SRef<T>>& points) const
{
	for (auto &it : ids) {
		auto pointIt = m_pointCloud.find(it);
		if (pointIt == m_pointCloud.end()) {
			LOG_DEBUG("Cannot find cloud point with id {} to get", it);
			return FrameworkReturnCode::_ERROR_;
		}
		points.push_back(pointIt->second);
	}
	return FrameworkReturnCode::_SUCCESS;
}

template<class T>
inline FrameworkReturnCode PointCloud<T>::getAllPoints(std::vector<SRef<T>>& points) const
{
	for (auto pointIt : m_pointCloud)
		points.push_back(pointIt->second);
	return FrameworkReturnCode::_SUCCESS;
}

template<class T>
inline FrameworkReturnCode PointCloud<T>::suppressPoint(const uint32_t id)
{
	auto pointIt = m_pointCloud.find(id);
	if (pointIt != m_pointCloud.end()) {
		m_pointCloud.erase(pointIt);
		return FrameworkReturnCode::_SUCCESS;
	}
	else {
		LOG_DEBUG("Cannot find cloud point with id {} to suppress", id);
		return FrameworkReturnCode::_ERROR_;
	}
}

template<class T>
inline FrameworkReturnCode PointCloud<T>::suppressPoints(const std::vector<uint32_t>& ids)
{
	for (auto &it : ids) {
		auto pointIt = m_pointCloud.find(it);
		if (pointIt == m_pointCloud.end()) {
			LOG_DEBUG("Cannot find cloud point with id {} to suppress", it);
		}
		m_pointCloud.erase(pointIt);
	}
	return FrameworkReturnCode::_SUCCESS;
}

template<class T>
inline bool PointCloud<T>::isExistPoint(const uint32_t id) const
{
	if (m_pointCloud.find(id) != m_pointCloud.end())
		return true;
	else
		return false;
}

template<class T>
inline int PointCloud<T>::getNbPoints() const
{
	return static_cast<int>(m_pointCloud.size());
}

}
}  // end of namespace SolAR

#endif // POINTCLOUD_H
