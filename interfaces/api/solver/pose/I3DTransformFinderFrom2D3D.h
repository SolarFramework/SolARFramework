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

#ifndef SOLAR_I3DTRANSFORMFINDERFROM2D3D_H
#define SOLAR_I3DTRANSFORMFINDERFROM2D3D_H

#include "xpcf/api/IComponentIntrospect.h"

#include "core/Messages.h"

#include "datastructure/CameraDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Image.h"

namespace SolAR {
namespace api {
namespace solver {
namespace pose {
/**
 * @class I3DTransformFinderFrom2D3D
 * @brief <B>Finds the 3D transform of 2D-3D points correspondences.</B>
 * <TT>UUID: 77281cda-47c2-4bb7-bde6-5b0d02e75dae</TT>
 */
class XPCF_CLIENTUUID("201fb9e7-9452-42e2-a587-9e9b3e49c889") XPCF_SERVERUUID("cf5a7828-f6e1-482a-bb0c-b8e44ac9a22d") I3DTransformFinderFrom2D3D :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief I3DTransformFinderFrom2D3D default constructor.
    I3DTransformFinderFrom2D3D() = default;

    ///@brief I3DTransformFinderFrom2D3D default destructor.
    virtual ~I3DTransformFinderFrom2D3D() = default;

    /// @brief Estimates camera pose from a set of 2D image points of their corresponding 3D world points.
    /// @param[in] imagePoints the set of 2D image points.
    /// @param[in]  worldPoints the set of 3d world points.
    /// @param[in] camParams the camera parameters.
    /// @param[out] pose camera pose (pose of the camera defined in world corrdinate system) expressed as a Transform3D.
    /// @param[in] initialPose (Optional) a transform3D to initialize the pose (reducing the convergence time and improving its success).
    /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode estimate(const std::vector<SolAR::datastructure::Point2Df> & imagePoints,
                                         const std::vector<SolAR::datastructure::Point3Df> & worldPoints,
                                         const SolAR::datastructure::CameraParameters & camParams,
                                         SolAR::datastructure::Transform3Df & pose,
                                         const SolAR::datastructure::Transform3Df initialPose = SolAR::datastructure::Transform3Df::Identity()) =0;
};

}
}
}
}


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::I3DTransformFinderFrom2D3D,
                             "77281cda-47c2-4bb7-bde6-5b0d02e75dae",
                             "I3DTransformFinderFrom2D3D",
                             "SolAR::api::solver::pose::I3DTransformFinderFrom2D3D");
                            

#endif // SOLAR_I3DTRANSFORMFINDERFROM2D3D_H

