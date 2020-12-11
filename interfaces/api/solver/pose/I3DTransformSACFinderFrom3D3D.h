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

#ifndef SOLAR_I3DTRANSFORMSACFINDERFROM3D3D_H
#define SOLAR_I3DTRANSFORMSACFINDERFROM3D3D_H

#include "xpcf/api/IComponentIntrospect.h"

#include "core/Messages.h"

#include "datastructure/CameraDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/Keyframe.h"

namespace SolAR {
namespace api {
namespace solver {
namespace pose {
/**
 * @class I3DTransformSACFinderFrom3D3D
 * @brief <B>Finds the 3D transform of 3D-3D points correspondences with a SAmple Consensus.</B>
 * <TT>UUID: 940bddba-da70-4a6e-a327-890c1e61386d</TT>
 */
    class I3DTransformSACFinderFrom3D3D : virtual public org::bcom::xpcf::IComponentIntrospect {
    public:
        ///@brief I3DTransformSACFinderFrom3D3D default constructor.
        I3DTransformSACFinderFrom3D3D() = default;

        ///@brief I3DTransformSACFinderFrom3D3D default destructor.
        virtual ~I3DTransformSACFinderFrom3D3D() = default;

		/// @brief this method is used to set intrinsic parameters and distorsion of the camera
		/// @param[in] intrinsicParams: Camera calibration matrix parameters.
		/// @param[in] distortionParams: Camera distortion parameters.
		virtual void setCameraParameters(const datastructure::CamCalibration & intrinsicParams, const datastructure::CamDistortion & distortionParams) = 0;

        /// @brief Estimates camera pose from a set of 3D-3D point correspondences.
        /// @param[in] firstPoints3D: first set of 3D points.
        /// @param[in] secondPoints3D: second set of 3D points.
        /// @param[out] pose: 3D transformation maps the first set of 3D points to the second one.
        /// @param[out] inliers: indices of inlier correspondences.
        virtual FrameworkReturnCode estimate(const std::vector<datastructure::Point3Df> & firstPoints3D,
                                             const std::vector<datastructure::Point3Df> & secondPoints3D,
                                             datastructure::Transform3Df & pose,
                                             std::vector<int> &inliers) =0;

		/// @brief Estimates camera pose from a set of 3D-3D point correspondences.
		/// @param[in] firstKeyframe: first keyframe.
		/// @param[in] secondKeyframe: second keyframe.
		/// @param[in] matches: matches between two keyframes.
		/// @param[in] firstPoints3D: first set of 3D points.
		/// @param[in] secondPoints3D: second set of 3D points.
		/// @param[out] pose: 3D transformation maps the first set of 3D points to the second one.
		/// @param[out] inliers: indices of inlier correspondences.
		virtual FrameworkReturnCode estimate(const SRef<datastructure::Keyframe> &firstKeyframe,
											 const SRef<datastructure::Keyframe> &secondKeyframe,
											 const std::vector<datastructure::DescriptorMatch> &matches,
											 const std::vector<datastructure::Point3Df> & firstPoints3D,
											 const std::vector<datastructure::Point3Df> & secondPoints3D,
											 datastructure::Transform3Df & pose,
											 std::vector<int> &inliers) = 0;
    };

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::I3DTransformSACFinderFrom3D3D,
                             "940bddba-da70-4a6e-a327-890c1e61386d",
                             "I3DTransformSACFinderFrom3D3D",
                             "SolAR::api::solver::pose::I3DTransformSACFinderFrom3D3D");
                            
#endif // SOLAR_I3DTRANSFORMSACFINDERFROM3D3D_H
