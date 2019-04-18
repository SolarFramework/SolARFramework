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

#ifndef SOLAR_IPOINTCLOUDSTORAGE_H
#define SOLAR_IPOINTCLOUDSTORAGE_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace storage {

/**
 * @class IPointCloudStorage
 * @brief Allows to store a set of keyframes. This storage component can be accessed by processing components to share persistent data.

 */

class IPointCloudStorage : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IPointCloudStorage default constructor
    IPointCloudStorage() = default;

    /// @brief IPointCloudStorage default destructor
    virtual ~IPointCloudStorage() = default;

    /// @brief This method allow to add a 3D point to the key frame storage component
    /// @param[in] point the 3D point to add to the persistent point cloud
    /// @return FrameworkReturnCode::_SUCCESS_ if the addition succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode AddPoint(const SRef<Point3Df> point) = 0;

    /// @brief This method allow to suppress a frame to the key frame storage component
    /// @param[in] point the 3D point to suppress to the persistent point cloud
    /// @return FrameworkReturnCode::_SUCCESS_ if the suppression succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode SuppressPoint(const SRef<Point3Df> point) = 0;

    /// @brief This method allows to get all 3D points stored in the point cloud
    /// @param[out] the set of 3D point stored in the point cloud
    /// @return FrameworkReturnCode::_SUCCESS_ if succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode GetAllPoints(std::vector<SRef<Point3Df>>& points) = 0;

    /// @brief This method allows to know if a keyframe is already stored in the component
    /// @return true if exist, else false
    virtual bool ExistPoint(SRef<Point3Df> point) = 0;

    /// @brief This method allows to get the number of points stored in the point cloud
    /// @return The number of points
    virtual int GetNbPoints() = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::storage::IPointCloudStorage,
                             "264d4406-b726-4ce9-a430-35d8b5e70331",
                             "IPointCloudStorage",
                             "A component interface for storing a set of persistent 3D points accesisble by processing components.");


#endif //SOLAR_IPOINTCLOUDSTORAGE_H

