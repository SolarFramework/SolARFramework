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

#ifndef IKEYFRAMESELECTOR_H
#define IKEYFRAMESELECTOR_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

// Definition of IMapFilter Class //
// part of SolAR namespace //

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/Keyframe.h"
#include "datastructure/DescriptorMatch.h"

namespace SolAR {
namespace api {
namespace solver {
namespace map {
/**
  * @class IKeyframeSelector
  * @brief <B>Determines if a frame is a keyframe candidate.</B>
  * <TT>UUID: 4d5f2abe-beb7-11e8-a355-529269fb1459</TT>
  *
  */
class XPCF_IGNORE IKeyframeSelector : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IKeyframeSelector default constructor
    IKeyframeSelector() = default;

    /// @brief IKeyframeSelector default destructor
    virtual ~IKeyframeSelector() {}

    /// @brief  Select if a frame can be considered as a keyframe
    /// @param[in] frame: the frame tested to know if it could be a keyframe
    /// @param[in] matches: the matches between the frame and its reference keyframe.
    /// @return true if the frame can be considered as a new keyframe, false otherwise.
    virtual bool select(const SRef<SolAR::datastructure::Frame> frame, const std::vector<SolAR::datastructure::DescriptorMatch> & matches) const = 0;

    /// @brief  Select if a frame can be considered as a keyframe
    /// @param[in] frame: the frame tested to know if it could be a keyframe.
    /// @return true if the frame can be considered as a new keyframe, false otherwise.
    virtual bool select(const SRef<SolAR::datastructure::Frame> frame) const = 0;

    /// @brief  Select if a frame can be considered as a keyframe.
    /// It is based on a selection predicate and provides the mean to use any datastructure in the pipeline context to the decision algorithm.
    /// @param[in] frame: the frame tested to know if it could be a Keyframe
    /// @param[in] func: the function predicate used to test the frame.
    /// This predicate can be any lambda capturing its context (matches, point cloud, bow ...) to select the frame.
    /// @return true if the frame can be considered as a new keyframe, false otherwise.
   virtual bool select(const SRef<SolAR::datastructure::Frame> frame, const std::function<bool(const SRef<SolAR::datastructure::Frame> &)> & func) const = 0;

};
}

}
}
}
XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IKeyframeSelector,
                             "4d5f2abe-beb7-11e8-a355-529269fb1459",
                             "IKeyframeSelector",
                             "SolAR::api::solver::map::IKeyframeSelector interface to determine if a frame can be considered as a keyframe.");


#endif // IKEYFRAMESELECTOR_H
