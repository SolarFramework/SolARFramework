/**
 * @copyright Copyright (c) 2024 B-com http://www.b-com.com/
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

#ifndef SOLAR_IPOINTCLOUDLOADER_H
#define SOLAR_IPOINTCLOUDLOADER_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/Map.h"

namespace SolAR {
namespace api {
namespace input {
namespace files {
/**
 * @class IMapLoader
 * @brief <B>Loads a map from a file.</B>
 * <TT>UUID: 84dbbc4f-cc65-40ff-946d-7ed4999fb3a5</TT>
 *
 */
class XPCF_IGNORE IMapLoader :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    IMapLoader() = default;
    virtual ~IMapLoader() = default;

    /// @brief Load a Map from a filepath
    /// @param[out] map the loaded map
	/// @return FrameworkReturnCode::_SUCCESS if load succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode load(SRef<SolAR::datastructure::Map> & map) = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::files::IMapLoader,
                             "84dbbc4f-cc65-40ff-946d-7ed4999fb3a5",
                             "IMapLoader",
                             "Load a map from a file");


#endif // SOLAR_IPOINTCLOUDLOADER_H
