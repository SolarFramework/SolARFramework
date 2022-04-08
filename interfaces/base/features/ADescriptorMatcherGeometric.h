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

#ifndef SOLAR_ADESCRIPTORMATCHERGEOMETRIC_H
#define SOLAR_ADESCRIPTORMATCHERGEOMETRIC_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "core/SolARFrameworkDefinitions.h"
#include "api/features/IDescriptorMatcherGeometric.h"
#include <xpcf/component/ConfigurableBase.h>

namespace SolAR {
namespace base {
namespace features {

class XPCF_IGNORE SOLARFRAMEWORK_API ADescriptorMatcherGeometric : public org::bcom::xpcf::ConfigurableBase,
													virtual public SolAR::api::features::IDescriptorMatcherGeometric {
public:
    /// @brief ADescriptorMatcherGeometric constructor
    ADescriptorMatcherGeometric(std::map<std::string,std::string> componentInfosMap);

    virtual ~ADescriptorMatcherGeometric() override = default;

    /// @brief Match two sets of descriptors from two frames based on epipolar constraint.
    /// @param[in] descriptors1 The first set of descriptors.
    /// @param[in] descriptors2 The second set of descriptors.
    /// @param[in] undistortedKeypoints1 The first set of undistorted keypoints.
    /// @param[in] undistortedKeypoints2 The second set of undistorted keypoints.
    /// @param[in] pose1 The first pose.
    /// @param[in] pose2 The second pose.
    /// @param[in] camParams The intrinsic parameters of the camera.
    /// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
    /// @param[in] mask The indices of descriptors in the first frame are used for matching to the second frame. If it is empty then all will be used.
    /// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::DescriptorBuffer> descriptors1,
                                      const SRef<SolAR::datastructure::DescriptorBuffer> descriptors2,
                                      const std::vector<SolAR::datastructure::Keypoint> &undistortedKeypoints1,
                                      const std::vector<SolAR::datastructure::Keypoint> &undistortedKeypoints2,
                                      const SolAR::datastructure::Transform3Df& pose1,
                                      const SolAR::datastructure::Transform3Df& pose2,
                                      const SolAR::datastructure::CameraParameters & camParams,
                                      std::vector<SolAR::datastructure::DescriptorMatch> & matches,
                                      const std::vector<uint32_t>& mask = {}) override
    { return FrameworkReturnCode::_NOT_IMPLEMENTED; }

    /// @brief Match two sets of descriptors from two frames based on epipolar constraint.
    /// @param[in] frame1 The first frame containing descriptors and undistorted keypoints.
    /// @param[in] frame2 The second frame containing descriptors and undistorted keypoints.
    /// @param[in] camParams The intrinsic parameters of the camera.
    /// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
    /// @param[in] mask The indices of descriptors in the first frame are used for matching to the second frame. If it is empty then all will be used.
    /// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::Frame> frame1,
                                      const SRef<SolAR::datastructure::Frame> frame2,
                                      const SolAR::datastructure::CameraParameters & camParams,
                                      std::vector<SolAR::datastructure::DescriptorMatch> & matches,
                                      const std::vector<uint32_t>& mask = {}) override;
};
}
}
}  // end of namespace SolAR


#endif // SOLAR_ADESCRIPTORMATCHERGEOMETRIC_H
