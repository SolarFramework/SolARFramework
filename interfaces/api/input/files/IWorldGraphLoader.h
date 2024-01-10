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

#ifndef IWORLDGRAPHLOADER_H
#define IWORLDGRAPHLOADER_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/FiducialMarker.h"
#include "datastructure/ImageMarker.h"
#include "datastructure/QRCode.h"

namespace SolAR {
namespace api {
namespace input {
namespace files {

/**
 * @class IWorldGraphLoader
 * @brief <B>Loads a world graph of trackables.</B>
 * <TT>UUID: b68a0544-c9f2-48eb-9542-c2048ff25c08</TT>
 *
 */
class XPCF_CLIENTUUID("1dd71248-747b-4a90-b2c6-7811aed57ba0") XPCF_SERVERUUID("15716f60-7688-44cb-867c-a8a49d4b9a80") IWorldGraphLoader :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    IWorldGraphLoader() = default;
    virtual ~IWorldGraphLoader() = default;

    /// @brief Loads a world graph of trackables.
    /// @param [out] trackables the set of trackables.
    /// @return FrameworkReturnCode::_SUCCESS if load succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode load(std::vector<SRef<SolAR::datastructure::Trackable>>& trackables) = 0;

};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::files::IWorldGraphLoader,
                             "b68a0544-c9f2-48eb-9542-c2048ff25c08",
                             "IWorldGraphLoader",
                             "Interface for loading a world graph of trackables");

#endif // IWORLDGRAPHLOADER_H
