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

#ifndef SOLAR_IDESCRIPTORMATCHERSTEREO_H
#define SOLAR_IDESCRIPTORMATCHERSTEREO_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/Frame.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/Keypoint.h"
#include "datastructure/DescriptorMatch.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace features {

/** @class IDescriptorMatcherStereo
* @brief <B>Matches two sets of descriptors from stereo images.</B>
* <TT>UUID: 272f1ef0-c269-4631-b75c-fc7316d10915</TT>
* Just implement the first interface, the second interface is implemented in ADescriptorMatcherStereo.
*/
class XPCF_CLIENTUUID("06bc0b35-6240-4bb9-ae8a-1de2c5f77a13") XPCF_SERVERUUID("9f72e88e-ca7a-4ac9-af81-cf08382dda03") IDescriptorMatcherStereo :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IDescriptorMatcherStereo constructor
    IDescriptorMatcherStereo() = default;

    /// @brief ~IDescriptorMatcherStereo
    virtual ~IDescriptorMatcherStereo() {};

	/// @brief Match two sets of descriptors from stereo images.
	/// @param[in] descriptors1 Descirptors of the first image.
	/// @param[in] descriptors2 Descirptors of the second image.
    /// @param[in] undistortedKeypoints1 Undistorted keypoints of the first image.
    /// @param[in] undistortedKeypoints2 Undistorted keypoints of the second image.
	/// @param[in] type Stereo type (horizontal or vertical).
	/// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
	/// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::DescriptorBuffer>& descriptors1,
                                      const SRef<SolAR::datastructure::DescriptorBuffer>& descriptors2,
                                      const std::vector<SolAR::datastructure::Keypoint>& undistortedKeypoints1,
                                      const std::vector<SolAR::datastructure::Keypoint>& undistortedKeypoints2,
                                      SolAR::datastructure::StereoType type,
                                      std::vector<SolAR::datastructure::DescriptorMatch> &matches) = 0;

    /// @brief Match two sets of descriptors from stereo images.
    /// @param[in] frame1 The first frame containing descriptors and undistorted keypoints.
    /// @param[in] frame2 The second frame containing descriptors and undistorted keypoints.
    /// @param[in] type Stereo type (horizontal or vertical).
    /// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
    /// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::Frame> frame1,
                                      const SRef<SolAR::datastructure::Frame> frame2,
                                      SolAR::datastructure::StereoType type,
                                      std::vector<SolAR::datastructure::DescriptorMatch> &matches) = 0;
};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IDescriptorMatcherStereo,
							"272f1ef0-c269-4631-b75c-fc7316d10915",
                            "IDescriptorMatcherStereo",
                            "SolAR::api::features::IDescriptorMatcherStereo interface");

#endif // SOLAR_IDESCRIPTORMATCHERSTEREO_H
