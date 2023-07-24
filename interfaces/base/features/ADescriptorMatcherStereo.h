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

#ifndef SOLAR_ADESCRIPTORMATCHERSTEREO_H
#define SOLAR_ADESCRIPTORMATCHERSTEREO_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "core/SolARFrameworkDefinitions.h"
#include "api/features/IDescriptorMatcherStereo.h"
#include <xpcf/component/ConfigurableBase.h>

namespace SolAR {
namespace base {
namespace features {

class XPCF_IGNORE SOLARFRAMEWORK_API ADescriptorMatcherStereo : public org::bcom::xpcf::ConfigurableBase,
													virtual public SolAR::api::features::IDescriptorMatcherStereo {
public:
    /// @brief ADescriptorMatcherStereo constructor
    ADescriptorMatcherStereo(std::map<std::string,std::string> componentInfosMap);

    virtual ~ADescriptorMatcherStereo() override = default;

    /// @brief Match two sets of descriptors from stereo images.
    /// @param[in] descriptors1 Descirptors of the first image.
    /// @param[in] descriptors2 Descirptors of the second image.
    /// @param[in] undistortedKeypoints1 Undistorted keypoints of the first image.
    /// @param[in] undistortedKeypoints2 Undistorted keypoints of the second image.
    /// @param[in] type Stereo type (horizontal or vertical).
    /// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
    /// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::DescriptorBuffer>& /*descriptors1*/,
                                      const SRef<SolAR::datastructure::DescriptorBuffer>& /*descriptors2*/,
                                      const std::vector<SolAR::datastructure::Keypoint>& /*undistortedKeypoints1*/,
                                      const std::vector<SolAR::datastructure::Keypoint>& /*undistortedKeypoints2*/,
                                      SolAR::datastructure::StereoType /*type*/,
                                      std::vector<SolAR::datastructure::DescriptorMatch> &/*matches*/) override
	{ return FrameworkReturnCode::_NOT_IMPLEMENTED; }

    /// @brief Match two sets of descriptors from stereo images.
    /// @param[in] frame1 The first frame containing descriptors and undistorted keypoints.
    /// @param[in] frame2 The second frame containing descriptors and undistorted keypoints.
    /// @param[in] type Stereo type (horizontal or vertical).
    /// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
    /// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::Frame> frame1,
                                      const SRef<SolAR::datastructure::Frame> frame2,
                                      SolAR::datastructure::StereoType type,
                                      std::vector<SolAR::datastructure::DescriptorMatch> &matches) override;


};
}
}
}  // end of namespace SolAR


#endif // SOLAR_ADESCRIPTORMATCHERSTEREO_H
