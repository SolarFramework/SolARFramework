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
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace geom {

/** @class IDepthEstimation
* @brief <B>Depth estimation based on disparity of matched features.</B>
* <TT>UUID: 0d3c4b5d-bbb2-4adc-80b0-b7e8720a704d</TT>
*/
class XPCF_CLIENTUUID("a0d958fd-53ed-490b-aec4-2a5a93a60d98") XPCF_SERVERUUID("d47a2503-e1c6-4db2-9bff-52a3259bcbe1") IDepthEstimation :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IDepthEstimation constructor
    IDepthEstimation() = default;

    /// @brief ~IDepthEstimation
    virtual ~IDepthEstimation() = default;

    /// @brief Depth estimation based on disparity of matched rectified keypoints in a stereo camera
    /// @param[in,out] rectKeypoints1 Rectified keypoints of the first image. The implementation stores depth estimation in the keypoints.
    /// @param[in,out] rectKeypoints2 Rectified keypoints of the second image. The implementation stores depth estimation in the keypoints.
	/// @param[in] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
	/// @param[in] focal The common focal of the camera.
	/// @param[in] baseline The baseline distance of two cameras.
	/// @param[in] type Stereo type
    /// @return FrameworkReturnCode::_SUCCESS if estimating succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode estimate(std::vector<SolAR::datastructure::Keypoint>& rectKeypoints1,
                                         std::vector<SolAR::datastructure::Keypoint>& rectKeypoints2,
                                         const std::vector<SolAR::datastructure::DescriptorMatch>& matches,
                                         float focal,
                                         float baseline,
                                         SolAR::datastructure::StereoType type) = 0;
};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::geom::IDepthEstimation,
							"0d3c4b5d-bbb2-4adc-80b0-b7e8720a704d",
                            "IDepthEstimation",
                            "SolAR::api::geom::IDepthEstimation interface");

#endif // SOLAR_IDEPTHESTIMATION_H
