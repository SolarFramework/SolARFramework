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

#ifndef SOLAR_IDESCRIPTORMATCHER_H
#define SOLAR_IDESCRIPTORMATCHER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <vector>
//#include "IDescriptor.h"
#include "datastructure/DescriptorBuffer.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/Frame.h"

// Definition of IDescriptorMatcher Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"
#include "xpcf/core/helpers.h"

namespace SolAR {
namespace api {
namespace features {

/**
 * @class IDescriptorMatcher
 * @brief <B>Matches two sets of descriptors together.</B>
 * <TT>UUID: dda38a40-c50a-4e7d-8433-0f04c7c98518</TT>
 *
 * This class provides a filtering method to prune a set of contours.
 */
    class  IDescriptorMatcher : virtual public org::bcom::xpcf::IComponentIntrospect {
    public:
        enum  RetCode {
          DESCRIPTORS_MATCHER_OK=0,     /**< the default OK code*/
           DESCRIPTORS_DONT_MATCH,      /**< try to match descriptors of different types*/
           DESCRIPTOR_TYPE_UNDEFINED,   /**< one of the descriptor sets is is unknown*/
           DESCRIPTOR_EMPTY             /**< One set is empty*/
        };

        /// @brief IDescriptorMatcher default constructor
        IDescriptorMatcher() = default;

        /// @brief IDescriptorMatcher default destructor
        virtual ~IDescriptorMatcher() {};


        /// @brief Match two sets of descriptors together
        /// @param[in] descriptors1 The first set of descriptors organized in a dedicated buffer structure.
        /// @param[in] descriptors2 The second set of descriptors organized in a dedicated buffer structure.
        /// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
        /// @return DesciptorMatcher::DESCRIPTORS_MATCHER_OK if matching succeeds, DesciptorMatcher::DESCRIPTORS_DONT_MATCH if the types of descriptors are different, DesciptorMatcher::DESCRIPTOR_TYPE_UNDEFINED if one of the descriptors set is unknown, or DesciptorMatcher::DESCRIPTOR_EMPTY if one of the set is empty.
        virtual RetCode match(
               const SRef<SolAR::datastructure::DescriptorBuffer> descriptors1,
               const SRef<SolAR::datastructure::DescriptorBuffer> descriptors2,
               std::vector<SolAR::datastructure::DescriptorMatch> & matches
            ) = 0;

        /// @brief Match two sets of descriptors together. The second set is organized in a vector of descriptors buffer and can be used if the descriptors have been extracted on subsets of an image.
        /// @param[in] descriptors1 The first set of descriptors organized in a dedicated buffer structure.
        /// @param[in] descriptors2 The second set of descriptors organized in a vectir of dedicated buffer structure.
        /// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
        /// @return DesciptorMatcher::DESCRIPTORS_MATCHER_OK if matching succeeds, DesciptorMatcher::DESCRIPTORS_DONT_MATCH if the types of descriptors are different, DesciptorMatcher::DESCRIPTOR_TYPE_UNDEFINED if one of the descriptors set is unknown, or DesciptorMatcher::DESCRIPTOR_EMPTY if one of the set is empty.
        virtual RetCode match(
               const SRef<SolAR::datastructure::DescriptorBuffer> descriptors1,
               const std::vector<SRef<SolAR::datastructure::DescriptorBuffer>> & descriptors2,
               std::vector<SolAR::datastructure::DescriptorMatch> & matches
            ) = 0;

		/// @brief Match each descriptor input with descriptors of a frame in a region. The searching space is a circle which is defined by a 2D center and a radius
		/// @param[in] points2D The center points of searching regions
		/// @param[in] descriptors The descriptors organized in a vector of dedicated buffer structure.
		/// @param[in] frame The frame contains descriptors to match.
		/// @param[out] matches A vector of matches representing pairs of indices relatively to the first and second set of descriptors.
		/// @return DesciptorMatcher::DESCRIPTORS_MATCHER_OK if matching succeeds, DesciptorMatcher::DESCRIPTORS_DONT_MATCH if the types of descriptors are different, DesciptorMatcher::DESCRIPTOR_TYPE_UNDEFINED if one of the descriptors set is unknown, or DesciptorMatcher::DESCRIPTOR_EMPTY if one of the set is empty.
		virtual RetCode matchInRegion(
            ATTRIBUTE(maybe_unused) const std::vector<SolAR::datastructure::Point2Df> & points2D,
            ATTRIBUTE(maybe_unused) const std::vector<SRef<SolAR::datastructure::DescriptorBuffer>> & descriptors,
            ATTRIBUTE(maybe_unused) const SRef<SolAR::datastructure::Frame> frame,
            ATTRIBUTE(maybe_unused) std::vector<SolAR::datastructure::DescriptorMatch> &matches,
            ATTRIBUTE(maybe_unused) const float radius = 0.f,
            ATTRIBUTE(maybe_unused) const float matchingDistanceMax = 0.f
        ) { return RetCode::DESCRIPTORS_MATCHER_OK; };

		/// @brief Match each descriptor input with descriptors of a frame in a region. The searching space is a circle which is defined by a 2D center and a radius
		/// @param[in] currentFrame the current frame.
		/// @param[in] lastFrame the last frame.
		/// @param[out] matches a vector of matches between two frames representing pairs of keypoint indices relatively.
		/// @param[in] radius the radius of search region around each keypoint of the last frame.
		/// @param[in] matchingDistanceMax the maximum distance to valid a match.
		/// @return DesciptorMatcher::DESCRIPTORS_MATCHER_OK if matching succeeds, DesciptorMatcher::DESCRIPTORS_DONT_MATCH if the types of descriptors are different, DesciptorMatcher::DESCRIPTOR_TYPE_UNDEFINED if one of the descriptors set is unknown, or DesciptorMatcher::DESCRIPTOR_EMPTY if one of the set is empty.
		virtual RetCode matchInRegion(
			ATTRIBUTE(maybe_unused) const SRef<datastructure::Frame> currentFrame,
			ATTRIBUTE(maybe_unused) const SRef<datastructure::Frame> lastFrame,
			ATTRIBUTE(maybe_unused) std::vector<datastructure::DescriptorMatch> &matches,
			ATTRIBUTE(maybe_unused) const float radius = 0.f,
			ATTRIBUTE(maybe_unused) const float matchingDistanceMax = 0.f
		) {
			return RetCode::DESCRIPTORS_MATCHER_OK;
		};
    };
}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IDescriptorMatcher,
                             "dda38a40-c50a-4e7d-8433-0f04c7c98518",
                             "IDescriptorMatcher",
                             "SolAR::api::features::IDescriptorMatcher");

#endif // SOLAR_IDESCRIPTORMATCHER_H
