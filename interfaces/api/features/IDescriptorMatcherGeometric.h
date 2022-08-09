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

#ifndef SOLAR_IDESCRIPTORMATCHERGEOMETRIC_H
#define SOLAR_IDESCRIPTORMATCHERGEOMETRIC_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <vector>
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/Frame.h"
#include "datastructure/CameraDefinitions.h"
#include "xpcf/api/IComponentIntrospect.h"
#include "xpcf/core/helpers.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace features {

/**
 * @class IDescriptorMatcherGeometric
 * @brief <B>Matches two sets of descriptors based on geometric constraints.</B>
 * <TT>UUID: 2ed445a6-32f3-44a1-9dc5-3b0cfec778db</TT>
 * Just implement the first interface, the second interface is implemented in ADescriptorMatcherGeometric.
 */
class [[xpcf::clientUUID("1bd62a3f-3376-45c3-a980-94d042ae509f")]] [[xpcf::serverUUID("75930efc-a96e-4d07-86b0-2ab2d9ea0102")]] IDescriptorMatcherGeometric :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IDescriptorMatcherGeometric default constructor
    IDescriptorMatcherGeometric() = default;

    /// @brief IDescriptorMatcherGeometric default destructor
    virtual ~IDescriptorMatcherGeometric() = default;

    /// @brief Match two sets of descriptors from two frames based on epipolar constraint.
    /// @param[in] descriptors1 The first set of descriptors.
    /// @param[in] descriptors2 The second set of descriptors.
    /// @param[in] undistortedKeypoints1 The first set of undistorted keypoints.
    /// @param[in] undistortedKeypoints2 The second set of undistorted keypoints.
    /// @param[in] pose1 The first pose.
    /// @param[in] pose2 The second pose.
    /// @param[in] camParams1 The intrinsic parameters of the camera 1.
    /// @param[in] camParams2 The intrinsic parameters of the camera 2.
    /// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
    /// @param[in] mask The indices of descriptors in the first frame are used for matching to the second frame. If it is empty then all will be used.
    /// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::DescriptorBuffer> descriptors1,
                                      const SRef<SolAR::datastructure::DescriptorBuffer> descriptors2,
                                      const std::vector<SolAR::datastructure::Keypoint> &undistortedKeypoints1,
                                      const std::vector<SolAR::datastructure::Keypoint> &undistortedKeypoints2,
                                      const SolAR::datastructure::Transform3Df& pose1,
                                      const SolAR::datastructure::Transform3Df& pose2,
                                      const SolAR::datastructure::CameraParameters & camParams1,
                                      const SolAR::datastructure::CameraParameters & camParams2,
                                      std::vector<SolAR::datastructure::DescriptorMatch> & matches,
                                      const std::vector<uint32_t>& mask = {}) = 0;

    /// @brief Match two sets of descriptors from two frames based on epipolar constraint.
    /// @param[in] frame1 The first frame containing descriptors and undistorted keypoints.
    /// @param[in] frame2 The second frame containing descriptors and undistorted keypoints.
    /// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
    /// @param[in] mask The indices of descriptors in the first frame are used for matching to the second frame. If it is empty then all will be used.
    /// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::Frame> frame1,
                                      const SRef<SolAR::datastructure::Frame> frame2,
                                      std::vector<SolAR::datastructure::DescriptorMatch> & matches,
                                      const std::vector<uint32_t>& mask = {}) = 0;
};
}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IDescriptorMatcherGeometric,
                             "2ed445a6-32f3-44a1-9dc5-3b0cfec778db",
                             "IDescriptorMatcherGeometric",
                             "SolAR::api::features::IDescriptorMatcherGeometric");

#endif // SOLAR_IDESCRIPTORMATCHERGEOMETRIC_H
