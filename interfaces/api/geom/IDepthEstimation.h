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

#ifndef SOLAR_IDEPTHESTIMATION_H
#define SOLAR_IDEPTHESTIMATION_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Keypoint.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/StereoCameraDefinitions.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace geom {

/** @class IDepthEstimation
* @brief <B>Depth estimation based on disparity of matched features.</B>
* <TT>UUID: 0d3c4b5d-bbb2-4adc-80b0-b7e8720a704d</TT>
*/
class  IDepthEstimation : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IDepthEstimation constructor
    IDepthEstimation() = default;

    /// @brief ~IDepthEstimation
    virtual ~IDepthEstimation() = default;

    /// @brief Depth estimation based on disparity of matched rectified keypoints in a stereo camera
    /// @param[in,out] rectKeypoints1 Rectified keypoints of the first image and the depth estimation is stored in the keypoints.
    /// @param[in,out] rectKeypoints2 Rectified keypoints of the second image and the depth estimation is stored in the keypoints.
	/// @param[in] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
	/// @param[in] focal The common focal of the camera.
	/// @param[in] baseline The baseline distance of two cameras.
	/// @param[in] type Stereo type
    /// @return FrameworkReturnCode::_SUCCESS if estimating succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode estimate(std::vector<SolAR::datastructure::Keypoint>& rectKeypoints1,
                                         std::vector<SolAR::datastructure::Keypoint>& rectKeypoints2,
                                         const std::vector<SolAR::datastructure::DescriptorMatch>& matches,
                                         const float& focal,
                                         const float& baseline,
                                         const SolAR::datastructure::StereoType& type) = 0;
};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::stereo::IDepthEstimation,
							"0d3c4b5d-bbb2-4adc-80b0-b7e8720a704d",
                            "IDepthEstimation",
                            "SolAR::api::geom::IDepthEstimation interface");

#endif // SOLAR_IDEPTHESTIMATION_H
