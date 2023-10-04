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

#ifndef SOLAR_IPOINTCLOUDMANAGER_H
#define SOLAR_IPOINTCLOUDMANAGER_H


#include <xpcf/api/IComponentIntrospect.h>
#include "datastructure/CloudPoint.h"
#include "datastructure/PointCloud.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/DescriptorBuffer.h"

namespace SolAR {
namespace api {
namespace storage {

/**
 * @class IPointCloudManager
 * @brief <B>Allows to store a point cloud.</B>
 * <TT>UUID: 264d4406-b726-4ce9-a430-35d8b5e70331</TT>
 *
 * This storage component can be accessed by processing components to share persistent data.
 */

class XPCF_IGNORE IPointCloudManager :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IPointCloudStorage default constructor
	IPointCloudManager() = default;

    /// @brief IPointCloudStorage default destructor
    virtual ~IPointCloudManager() = default;

    /// @brief This method allow to add a 3D point to the point cloud
    /// @param[in] point the 3D point to add to the persistent point cloud
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode addPoint(const SRef<SolAR::datastructure::CloudPoint> point) = 0;

	/// @brief This method allow to add a vector of 3D points to the point cloud
	/// @param[in] points a vector of the 3D points to add to the persistent point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode addPoints(const std::vector<SRef<SolAR::datastructure::CloudPoint>> & points) = 0;

	/// @brief This method allow to add a 3D point to the point cloud
	/// @param[in] point the 3D point to add to the persistent point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode addPoint(const SolAR::datastructure::CloudPoint & point) = 0;

	/// @brief This method allow to add a vector of 3D points to the point cloud
	/// @param[in] points a vector of the 3D points to add to the persistent point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode addPoints(const std::vector<SolAR::datastructure::CloudPoint> & points) = 0;

	/// @brief This method allows to get a 3D point stored in the point cloud by its id
	/// @param[in] id id of the point to get
	/// @param[out] point a 3D point stored in the point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getPoint(const uint32_t id, SRef<SolAR::datastructure::CloudPoint>& point) const = 0;

	/// @brief This method allows to get a set of 3D points stored in the point cloud by their ids
	/// @param[in] ids a vector of ids of the points to get
	/// @param[out] points a vector of 3D points stored in the point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getPoints(const std::vector<uint32_t> & ids, std::vector<SRef<SolAR::datastructure::CloudPoint>> & points) const = 0;

	/// @brief This method allows to get all 3D points stored in the point cloud
	/// @param[out] points the set of 3D point stored in the point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode getAllPoints(std::vector<SRef<SolAR::datastructure::CloudPoint>> & points) const = 0;

    /// @brief This method allow to suppress a point stored in the point cloud by its id
    /// @param[in] id of the point to suppress
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode suppressPoint(const uint32_t id) = 0;

	/// @brief This method allow to suppress a vector of points stored in the point cloud by their ids
	/// @param[in] ids the vector of ids of the point to suppress
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode suppressPoints(const std::vector<uint32_t> & ids) = 0;

	/// @brief This method allows to get the descriptor type used to extract descriptor for each cloud point
	/// @return Descriptor type
    virtual SolAR::datastructure::DescriptorType getDescriptorType() const = 0;

	/// @brief This method allows to set the descriptor type used to extract descriptor for each cloud point
	/// @param[in] type Descriptor type
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode setDescriptorType(const SolAR::datastructure::DescriptorType & type) = 0;

    /// @brief This method allows to know if a point is already stored in the component
	/// @param[in] id id of this point
    /// @return true if exist, else false
    virtual bool isExistPoint(const uint32_t id) const = 0;

    /// @brief This method allows to get the number of points stored in the point cloud
    /// @return The number of points
    virtual int getNbPoints() const = 0;

	/// @brief This method allows to save the point cloud to the external file
	/// @param[in] file the file name
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode saveToFile(const std::string& file) const = 0;

	/// @brief This method allows to load the point cloud from the external file
	/// @param[in] file the file name
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode loadFromFile(const std::string& file) = 0;

	/// @brief This method returns the point cloud
	/// @return the point cloud
    virtual const SRef<SolAR::datastructure::PointCloud> & getConstPointCloud() const = 0;

	/// @brief This method returns the point cloud
	/// @param[out] pointCloud the point cloud
	/// @return the point cloud
    virtual std::unique_lock<std::mutex> getPointCloud(SRef<SolAR::datastructure::PointCloud>& pointCloud) = 0;

	/// @brief This method is to set the point cloud
	/// @param[in] pointCloud the point cloud
    virtual void setPointCloud(const SRef<SolAR::datastructure::PointCloud> pointCloud) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IPointCloudManager,
                             "264d4406-b726-4ce9-a430-35d8b5e70331",
                             "IPointCloudManager",
                             "A component interface for managing a set of persistent 3D points accesisble by processing components.");


#endif //SOLAR_IPOINTCLOUDMANAGER_H

