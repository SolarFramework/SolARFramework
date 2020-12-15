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

#ifndef SOLAR_I3DTRANSFORMFINDERFROM3D3D_H
#define SOLAR_I3DTRANSFORMFINDERFROM3D3D_H

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/PointCloud.h"
#include "datastructure/MathDefinitions.h"

namespace SolAR {
namespace api {
namespace solver {
namespace pose {
/**
 * @class I3DTransformFinderFrom3D3D
 * @brief Finds the 3D transform of a depth sensor from a point cloud captured by this sensor and a point cloud representing a geometric knowledge of the real world.
 */
class I3DTransformFinderFrom3D3D : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief I3DTransformFinderFrom3D3D default constructor.
    I3DTransformFinderFrom3D3D() = default;

    ///@brief I3DTransformFinderFrom3D3D default destructor.
    virtual ~I3DTransformFinderFrom3D3D() = default;

    /// @brief Estimates depth sensor pose from a set of 3D points captured by the depth sensor and defined in the depth sensor coordinate and a point cloud representing the real world geometry.
    /// @param[in] sourcePointCloud a point cloud captured by the depth sensor defined in the depth sensor coordinate system.
    /// @param[in] targetPointCloud a point cloud representing the geometry of the real world.
    /// @param[out] pose depth camera pose (pose of the depth camera defined in world coordinate system) expressed as a Transform3D.
    /// @param[in] initialPose (Optional) a transform3D to initialize the pose (reducing the convergence time and improving its success).
    /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode estimate(const SRef<datastructure::PointCloud> sourcePointCloud,
                                         const SRef<datastructure::PointCloud> targetPointCloud,
                                         datastructure::Transform3Df& pose,
                                         const datastructure::Transform3Df& initialPose = datastructure::Transform3Df::Identity()) =0;

};

}
}
}
}


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::I3DTransformFinderFrom3D3D,
                             "f2873a5d-0f9f-43a3-816c-1850ea7fe32d",
                             "I3DTransformFinderFrom3D3D",
                             "Estimate the 3D pose of a camera according to 3D-3D correspondences");


#endif // SOLAR_I3DTRANSFORMFINDERFROM3D3D_H
