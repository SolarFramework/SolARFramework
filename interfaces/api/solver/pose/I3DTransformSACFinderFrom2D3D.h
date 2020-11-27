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

#ifndef SOLAR_I3DTRANSFORMSACFINDERFROM2D3D_H
#define SOLAR_I3DTRANSFORMSACFINDERFROM2D3D_H

#include "xpcf/api/IComponentIntrospect.h"

#include "core/Messages.h"

#include "datastructure/CameraDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Image.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace solver {
namespace pose {
/**
 * @class I3DTransformSACFinderFrom2D3D
 * @brief <B>Finds the 3D transform of 2D-3D points correspondences with a SAmple Consensus.</B>
 * <TT>UUID: 8dd889c5-e8e6-4b3b-92e4-34cf7442f272</TT>
 */
    class I3DTransformSACFinderFrom2D3D : virtual public org::bcom::xpcf::IComponentIntrospect {
    public:
        ///@brief I3DTransformSACFinderFrom2D3D default constructor.
        I3DTransformSACFinderFrom2D3D() = default;

        ///@brief I3DTransformSACFinderFrom2D3D default destructor.
        virtual ~I3DTransformSACFinderFrom2D3D() = default;

        /// @brief this method is used to set intrinsic parameters and distorsion of the camera
        /// @param[in] intrinsicParams camera calibration matrix parameters.
        /// @param[in] intrinsicParams camera distorsion parameters.
        virtual void setCameraParameters(const CamCalibration & intrinsicParams, const CamDistortion & distorsionParams) = 0;

        /// @brief Estimates camera pose from a set of 2D image points of their corresponding 3D  world points.
        /// @param[in] imagePoints, set of 2d_points seen in view_1.
        /// @param[in]  worldPoints, set of 3d_points corresponding to view_1.
		/// @param[out] inliers: indices of inlier correspondences.
        /// @param[out] pose, camera pose (pose of the camera defined in world corrdinate system) expressed as a Transform3D.
        /// @param[in] initialPose (Optional), a transform3D to initialize the pose (reducing the convergence time and improving its success).
        virtual FrameworkReturnCode estimate(const std::vector<Point2Df> & imagePoints,
                                             const std::vector<Point3Df> & worldPoints,
                                             std::vector<uint32_t> & inliers,
                                             Transform3Df & pose,
                                             const Transform3Df initialPose = Transform3Df::Identity()) =0;

    };

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::I3DTransformSACFinderFrom2D3D,
                             "8dd889c5-e8e6-4b3b-92e4-34cf7442f272",
                             "I3DTransformSACFinderFrom2D3D",
                             "SolAR::api::solver::pose::I3DTransformSACFinderFrom2D3D");
                            
#endif // SOLAR_I3DTransformSACFinderFrom2D3D_H
