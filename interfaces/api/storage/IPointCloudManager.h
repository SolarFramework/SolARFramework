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


#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/CloudPoint.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/DescriptorBuffer.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace storage {

/**
 * @class IPointCloudManager
 * @brief Allows to store a point cloud. This storage component can be accessed by processing components to share persistent data.

 */

class IPointCloudManager : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IPointCloudStorage default constructor
	IPointCloudManager() = default;

    /// @brief IPointCloudStorage default destructor
    virtual ~IPointCloudManager() = default;

    /// @brief This method allow to add a 3D point to the point cloud
    /// @param[in] point the 3D point to add to the persistent point cloud
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode addPoint(SRef<CloudPoint> point) = 0;

	/// @brief This method allow to add a vector of 3D points to the point cloud
	/// @param[in] a vector of the 3D points to add to the persistent point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode addPoints(std::vector<SRef<CloudPoint>> points) = 0;

	/// @brief This method allow to add a 3D point to the point cloud
	/// @param[in] point the 3D point to add to the persistent point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode addPoint(CloudPoint &point) = 0;

	/// @brief This method allow to add a vector of 3D points to the point cloud
	/// @param[in] a vector of the 3D points to add to the persistent point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode addPoints(std::vector<CloudPoint> &points) = 0;

	/// @brief This method allows to get a 3D point stored in the point cloud by its id
	/// @param[in] id of the point to get
	/// @param[out] a 3D point stored in the point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode getPoint(uint32_t id, SRef<CloudPoint>& point) = 0;

	/// @brief This method allows to get a set of 3D points stored in the point cloud by their ids
	/// @param[in] a vector of ids of the points to get
	/// @param[out] a vector of 3D points stored in the point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode getPoints(std::vector<uint32_t> &ids, std::vector<SRef<CloudPoint>>& points) = 0;

	/// @brief This method allows to get all 3D points stored in the point cloud
	/// @param[out] the set of 3D point stored in the point cloud
	/// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode getAllPoints(std::vector<SRef<CloudPoint>>& points) = 0;

    /// @brief This method allow to suppress a point stored in the point cloud by its id
    /// @param[in] id of the point to suppress
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode suppressPoint(uint32_t id) = 0;

	/// @brief This method allow to suppress a vector of points stored in the point cloud by their ids
	/// @param[in] the vector of ids of the point to suppress
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode suppressPoints(std::vector<uint32_t> &ids) = 0;

	/// @brief This method allows to get the descriptor type used to extract descriptor for each cloud point
	/// @return Descriptor type
	virtual DescriptorType getDescriptorType() = 0;

	/// @brief This method allows to set the descriptor type used to extract descriptor for each cloud point
	/// @return Descriptor type
	virtual FrameworkReturnCode setDescriptorType(DescriptorType type) = 0;

    /// @brief This method allows to know if a point is already stored in the component
	/// @param[in] Id of this point
    /// @return true if exist, else false
    virtual bool isExistPoint(uint32_t id) = 0;

    /// @brief This method allows to get the number of points stored in the point cloud
    /// @return The number of points
    virtual int getNbPoints() = 0;

	/// @brief This method allows to save the point cloud to the external file
	/// @param[out] the file name
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode saveToFile(std::string file) = 0;

	/// @brief This method allows to load the point cloud from the external file
	/// @param[in] the file name
	/// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode loadFromFile(std::string file) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IPointCloudManager,
                             "264d4406-b726-4ce9-a430-35d8b5e70331",
                             "IPointCloudManager",
                             "A component interface for managing a set of persistent 3D points accesisble by processing components.");


#endif //SOLAR_IPOINTCLOUDSTORAGE_H

