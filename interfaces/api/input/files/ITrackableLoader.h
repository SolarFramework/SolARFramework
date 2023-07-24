/**
 * @copyright Copyright (c) 2020 B-com http://www.b-com.com/
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

#ifndef ITRACKABLELOADER_H
#define ITRACKABLELOADER_H

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/Trackable.h"

namespace SolAR {
namespace api {
namespace input {
namespace files {

/**
 * @class ITrackableLoader
 * @brief <B>Loads a general Trackable object.</B>
 * <TT>UUID: 8e54d5d0-f7a3-4d62-b012-728e5704b46a</TT>
 *
 */
class XPCF_CLIENTUUID("7f62f9da-c21c-44fe-aebe-fedca94f6be6") XPCF_SERVERUUID("9361175d-d517-4a54-ac49-e41610b6d64f") ITrackableLoader :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ITrackableLoader() = default;
    virtual ~ITrackableLoader() = default;

    /// @brief Loads a specific trackable object and its features.
    /// @param [in,out] trackable: the loaded trackable loaded
    /// @return FrameworkReturnCode::_SUCCESS if load succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode loadTrackable(SRef<SolAR::datastructure::Trackable>& trackable) = 0;

};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::files::ITrackableLoader,
                             "8e54d5d0-f7a3-4d62-b012-728e5704b46a",
                             "ITrackableLoader",
                             "Interface for Trackable objects");

#endif // ITRACKABLELOADER_H
