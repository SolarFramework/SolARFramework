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
#define POINTCLOUD_H

#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/CloudPoint.h"
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
class  SOLARFRAMEWORK_API PointCloud : public Lockable {
public:

	///
	/// @brief PointCloud constructor.
	///
	PointCloud() { m_id = 0; };
    PointCloud(const PointCloud& other): m_pointCloud(other.m_pointCloud), m_descriptorType(other.m_descriptorType), m_id(other.m_id) {};
    PointCloud& operator=(const PointCloud& /* other */) { return *this; };

	///
	/// @brief ~PointCloud
	///
	~PointCloud() = default;

	/// @brief This method allow to add a 3D point to the point cloud
	/// @param[in] point the 3D point to add to the persistent point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode addPoint(const SRef<SolAR::datastructure::CloudPoint> point);

	/// @brief This method allow to add a vector of 3D points to the point cloud
	/// @param[in] a vector of the 3D points to add to the persistent point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode addPoints(const std::vector<SRef<SolAR::datastructure::CloudPoint>>& points);

	/// @brief This method allow to add a 3D point to the point cloud
	/// @param[in] point the 3D point to add to the persistent point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode addPoint(const SolAR::datastructure::CloudPoint &point);

    /// @brief This method allow to add a vector of 3D points to the point cloud
    /// @param[in] a vector of the 3D points to add to the persistent point cloud
    /// @param[in] definePointId if true an id will be set for the added point, else the id of the point will be used
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode addPoints(const std::vector<SolAR::datastructure::CloudPoint> &points, bool definePointId = true);

	/// @brief This method allows to get a 3D point stored in the point cloud by its id
	/// @param[in] id of the point to get
	/// @param[out] a 3D point stored in the point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getPoint(const uint32_t id, SRef<SolAR::datastructure::CloudPoint>& point) const;

	/// @brief This method allows to get a set of 3D points stored in the point cloud by their ids
	/// @param[in] a vector of ids of the points to get
	/// @param[out] a vector of 3D points stored in the point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getPoints(const std::vector<uint32_t> &ids, std::vector<SRef<SolAR::datastructure::CloudPoint>>& points) const;

	/// @brief This method allows to get all 3D points stored in the point cloud
	/// @param[out] the set of 3D point stored in the point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode getAllPoints(std::vector<SRef<SolAR::datastructure::CloudPoint>>& points) const;

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

	/// @brief This method allows to get the descriptor type used to extract descriptor for each cloud point
	/// @return Descriptor type
    SolAR::datastructure::DescriptorType getDescriptorType() const;

	/// @brief This method allows to set the descriptor type used to extract descriptor for each cloud point
	/// @param[in] type the descriptor type
	/// @return @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    FrameworkReturnCode setDescriptorType(const SolAR::datastructure::DescriptorType & type);

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int version);

    std::map<uint32_t, SRef<SolAR::datastructure::CloudPoint>>	m_pointCloud;
    SolAR::datastructure::DescriptorType                        m_descriptorType;
    uint32_t                                                    m_id;
};

DECLARESERIALIZE(PointCloud);

}
}  // end of namespace SolAR

#endif // POINTCLOUD_H
