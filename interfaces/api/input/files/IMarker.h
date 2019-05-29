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

#ifndef SOLAR_IMARKER_H
#define SOLAR_IMARKER_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace input {
namespace files {

/**
 * @class IMarker
 * @brief <B>Specifies a general Marker.</B>
 * <TT>UUID: b05f3dbb-f93d-465c-aee1-fb58e1480c42</TT>
 *
 */
class IMarker : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    IMarker() = default;
    virtual ~IMarker() = default;
    /// @brief Load a specific marker and its features (size, descriptors..). 
    virtual FrameworkReturnCode loadMarker() = 0;

};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::files::IMarker,
                             "b05f3dbb-f93d-465c-aee1-fb58e1480c42",
                             "IMarker",
                             "SolAR::api::input::files::IMarker interface");

#endif // SOLAR_IMARKER_H

