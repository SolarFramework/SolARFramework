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

// Definition of IMapper Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/Keyframe.h"
#include "datastructure/DescriptorMatch.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace solver {
namespace map {
    ///
    /// @brief The IKeyframeSelector class
    ///
    class  IKeyframeSelector : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    IKeyframeSelector() = default;
    ///
    ///@brief ~IKeyframeSelector
    ///
    virtual ~IKeyframeSelector() {}

    /// @brief  Select if a frame can be considered as a keyframe
    /// @param[in] frame: the frame tested to know if it could be a Keyframe
    /// @param[in] matches: the matches between the frame and its keyframe of reference.
    /// @return true if the frame can be considered as a new keyframe, false otherwise.
    virtual bool select(const SRef<Frame> frame, const std::vector<DescriptorMatch>& matches) = 0;
};
}

}
}
}
XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IKeyframeSelector,
                             "4d5f2abe-beb7-11e8-a355-529269fb1459",
                             "IKeyframeSelector",
                             "SolAR::api::solver::map::IKeyframeSelector interface");


#endif // IKEYFRAMESELECTOR_H
