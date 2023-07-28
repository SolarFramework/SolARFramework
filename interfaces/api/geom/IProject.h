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

#ifndef SOLAR_IPROJECT_H
#define SOLAR_IPROJECT_H


#include "xpcf/api/IComponentIntrospect.h"
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/CloudPoint.h"

namespace SolAR {
namespace api {
namespace geom {

/**
 * @class IProject
 * @brief <B>Projects 3D points on a 2D image plane.</B>
 * <TT>UUID: b485f37d-a8ea-49f6-b361-f2b30777d9ba</TT>
 */

class XPCF_CLIENTUUID("64351b8a-7801-4ca9-841f-a4254506abc3") XPCF_SERVERUUID("8edec0aa-8547-49b0-a1a5-0eb148e44386") IProject :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IProjection default constructor
    IProject() = default;

    /// @brief I3DTransform default destructor
    virtual ~IProject() = default;

    /// @brief This method project a set of 3D points in the image plane
    /// @param[in] inputPoints the set of 3D points to project
    /// @param[in] pose the 3D pose of the camera (a 4x4 float matrix)
    /// @param[in] camParams the camera parameters.
    /// @param[out] imagePoints the resulting set of 2D points defined in the image coordinate systemn    
    /// @return FrameworkReturnCode::_SUCCESS_ if 3D projection succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode project(const std::vector<SolAR::datastructure::Point3Df> & inputPoints,
                                        const SolAR::datastructure::Transform3Df& pose,
                                        const SolAR::datastructure::CameraParameters & camParams,
                                        std::vector<SolAR::datastructure::Point2Df> & imagePoints) = 0;

    /// @brief This method project a set of 3D cloud points in the image plane
    /// @param[in] inputPoints the set of 3D cloud points to project
    /// @param[in] pose the 3D pose of the camera (a 4x4 float matrix)
    /// @param[in] camParams the camera parameters.
    /// @param[out] imagePoints the resulting set of 2D points defined in the image coordinate systemn
    /// @return FrameworkReturnCode::_SUCCESS_ if 3D projection succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode project(const std::vector<SRef<SolAR::datastructure::CloudPoint>> & inputPoints,
                                        const SolAR::datastructure::Transform3Df& pose,
                                        const SolAR::datastructure::CameraParameters & camParams,
                                        std::vector<SolAR::datastructure::Point2Df> & imagePoints) = 0;


};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::geom::IProject,
                             "b485f37d-a8ea-49f6-b361-f2b30777d9ba",
                             "IProjection",
                             "SolAR::api::geom::IProject");


#endif //SOLAR_IPROJECT_H

