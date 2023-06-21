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

#ifndef SOLAR_IUNPROJECT_H
#define SOLAR_IUNPROJECT_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/Keypoint.h"
#include "datastructure/CameraDefinitions.h"

namespace SolAR {
namespace api {
namespace geom {

/**
 * @class IUnproject
 * @brief <B>Recovers 3D points defined in world coordinate system from a set of 2D points defined in the image coordinate system.</B>
 * <TT>UUID: 21113a74-de60-4a3c-8b65-f3112beb3dc6</TT>
 */

class XPCF_CLIENTUUID("7e71a7db-6a67-4c28-ad40-1922370fdc00") XPCF_SERVERUUID("10dc5091-bf42-4a0d-8573-0a099220da39") IUnproject :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IUnproject default constructor
    IUnproject() = default;

    /// @brief IUnproject default destructor
    virtual ~IUnproject() = default;

    /// @brief This method unproject a set of 2D image points in the 3D world coordinate system
    /// @param[in] imagePoints the set of 2D points to unproject
    /// @param[in] pose the 3D pose of the camera (a 4x4 float matrix)
    /// @param[in] camParams the camera parameters
    /// @param[out] worldPoints a set of world 3D points resulting from the unprojection of the 2D image points    
    /// @return FrameworkReturnCode::_SUCCESS_ if 3D projection succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode unproject(const std::vector<SolAR::datastructure::Point2Df> & imagePoints,
                                          const SolAR::datastructure::Transform3Df & pose,
                                          const SolAR::datastructure::CameraParameters & camParams,
                                          std::vector<SolAR::datastructure::Point3Df> & worldPoints) = 0;

    /// @brief This method unproject a set of 2D image points in the 3D world coordinate system
    /// @param[in] imageKeypoints the set of 2D keypoints to unproject
    /// @param[in] pose the 3D pose of the camera (a 4x4 float matrix)
    /// @param[in] camParams the camera parameters
    /// @param[out] worldPoints a set of world 3D points resulting from the unprojection of the 2D image points    
    /// @return FrameworkReturnCode::_SUCCESS_ if 3D projection succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode unproject(const std::vector<SolAR::datastructure::Keypoint> & imageKeypoints,
                                          const SolAR::datastructure::Transform3Df & pose,
                                          const SolAR::datastructure::CameraParameters & camParams,
                                          std::vector<SolAR::datastructure::Point3Df> & worldPoints) = 0;

};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::geom::IUnproject,
                             "21113a74-de60-4a3c-8b65-f3112beb3dc6",
                             "I3DTransform",
                             "SolAR::api::geom::IUnproject");


#endif //SOLAR_IUNPROJECT_H

