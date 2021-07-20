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

#ifndef SOLAR_IDESCRIPTORMATCHERREGION_H
#define SOLAR_IDESCRIPTORMATCHERREGION_H

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
 * @class IDescriptorMatcherRegion
 * @brief <B>Matches two sets of descriptors based on region constraints.</B>
 * <TT>UUID: bdef063d-96de-4425-83c5-fec7b7e448c8</TT>
 * Just implement the first interface, the second and third interface are implemented in ADescriptorMatcherRegion.
 */
class  IDescriptorMatcherRegion : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IDescriptorMatcherRegion default constructor
    IDescriptorMatcherRegion() = default;

    /// @brief IDescriptorMatcherRegion default destructor
    virtual ~IDescriptorMatcherRegion() = default;

    /// @brief Match each descriptor of the first set to descriptors in its searching region of the second set.
    /// @param[in] descriptors1 The first set of descriptors.
    /// @param[in] descriptors2 The second set of descriptors.
    /// @param[in] points2D1 The positions of the first set of descriptors.
    /// @param[in] points2D2 The positions of the second set of descriptors.
    /// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
    /// @param[in] radius the radius of search region around each keypoint of the first set.
    /// @param[in] matchingDistanceMax the maximum distance to valid a match.
    /// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::DescriptorBuffer> descriptors1,
                                      const SRef<SolAR::datastructure::DescriptorBuffer> descriptors2,
                                      const std::vector<SolAR::datastructure::Point2Df> & points2D1,
                                      const std::vector<SolAR::datastructure::Point2Df> & points2D2,
                                      std::vector<SolAR::datastructure::DescriptorMatch> &matches,
                                      const float radius = -1.f,
                                      const float matchingDistanceMax = -1.f) = 0;

    /// @brief Match each descriptor input to descriptors of a frame in a region. The searching space is a circle which is defined by a 2D center and a radius
    /// @param[in] points2D The center points of searching regions
    /// @param[in] descriptors The descriptors organized in a vector of dedicated buffer structure.
    /// @param[in] frame The frame contains descriptors to match.
    /// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
    /// @param[in] radius the radius of search region around each keypoint of the first set.
    /// @param[in] matchingDistanceMax the maximum distance to valid a match.
    /// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const std::vector<SolAR::datastructure::Point2Df> & points2D,
                                      const std::vector<SRef<SolAR::datastructure::DescriptorBuffer>> & descriptors,
                                      const SRef<SolAR::datastructure::Frame> frame,
                                      std::vector<SolAR::datastructure::DescriptorMatch> &matches,
                                      const float radius = -1.f,
                                      const float matchingDistanceMax = -1.f) = 0;

    /// @brief Match each descriptor of the current frame to descriptors of the last frame in a region. The searching space is a circle which is defined by a 2D center and a radius
    /// @param[in] currentFrame the current frame.
    /// @param[in] lastFrame the last frame.
    /// @param[out] matches a vector of matches between two frames representing pairs of keypoint indices relatively.
    /// @param[in] radius the radius of search region around each keypoint of the last frame.
    /// @param[in] matchingDistanceMax the maximum distance to valid a match.
    /// @return FrameworkReturnCode::_SUCCESS if matching succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode match(const SRef<SolAR::datastructure::Frame> currentFrame,
                                      const SRef<SolAR::datastructure::Frame> lastFrame,
                                      std::vector<SolAR::datastructure::DescriptorMatch> &matches,
                                      const float radius = -1.f,
                                      const float matchingDistanceMax = -1.f) = 0;
};
}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IDescriptorMatcherRegion,
                             "bdef063d-96de-4425-83c5-fec7b7e448c8",
                             "IDescriptorMatcherRegion",
                             "SolAR::api::features::IDescriptorMatcherRegion");

#endif // SOLAR_IDESCRIPTORMATCHERREGION_H
