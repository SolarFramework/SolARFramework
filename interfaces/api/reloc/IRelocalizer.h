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

#ifndef IRELOCALIZER_H
#define IRELOCALIZER_H

#include "datastructure/Keyframe.h"
#include "datastructure/Frame.h"
#include "core/Messages.h"
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace reloc {


/**
 * @class IRelocalizer
 * @brief <B>Returns a camera pose giving a frame.</B>
 * <TT>UUID: 3531a734-be88-11e8-a355-529269fb1459</TT>
 *
 * This class provides a solution to get the pose given a frame.
 */

class XPCF_CLIENTUUID("fcbc25a8-d706-4a80-9d18-820bebbe45d6") XPCF_SERVERUUID("cc39b0cc-9236-46b2-8188-937992010c9f") IRelocalizer :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief IRelocalizer default constructor.
    IRelocalizer() = default;

    ///@brief IRelocalizer default destructor.
    virtual ~IRelocalizer() = default;

    /// @brief Add a keyframe containing a pose and its keypoints and descriptors to the relocalizer
    /// @param[in] keyframe: the keyframe to add to the bag of words
    /// @return FrameworkReturnCode::_SUCCESS if the keyfram adding succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode addKeyframe(const SRef<SolAR::datastructure::Keyframe> keyframe) = 0;


    /// @brief Get the pose of the camera corresponding to the frame.
    /// @param[in] frame: the frame for which we want to retrieve close keyframes.
    /// @param[out] pose: the pose of the camera corresponding to the frame
    /// @return FrameworkReturnCode::_SUCCESS if the retrieve succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode relocalize(const SRef<SolAR::datastructure::Frame> frame, SolAR::datastructure::Transform3Df & pose) = 0;
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::reloc::IRelocalizer,
                             "3531a734-be88-11e8-a355-529269fb1459",
                             "IRelocalizer",
                             "Interface SolAR::api::reloc::IRelocalizer allows to retrieve the pose for a given frame.");

#endif // IRELOCALIZER_H
