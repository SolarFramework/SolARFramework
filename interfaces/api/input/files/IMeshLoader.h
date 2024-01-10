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

#ifndef SOLAR_IMESHLOADER_H
#define SOLAR_IMESHLOADER_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/Mesh.h"

namespace SolAR {
namespace api {
namespace input {
namespace files {
/**
 * @class IMeshLoader
 * @brief <B>Loads a mesh from a file.</B>
 * <TT>UUID: 315c7cd4-462d-11ed-b878-0242ac120002</TT>
 *
 */
class XPCF_CLIENTUUID("5580de7a-462d-11ed-b878-0242ac120002") XPCF_SERVERUUID("5973d118-462d-11ed-b878-0242ac120002") IMeshLoader :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    IMeshLoader() = default;
    virtual ~IMeshLoader() = default;

    /// @brief Load a Mesh from a file
    /// @param[out] Mesh: the point cloud to fill
	/// @return FrameworkReturnCode::_SUCCESS if load succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode load(SRef<SolAR::datastructure::Mesh> & Mesh) = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::files::IMeshLoader,
                             "315c7cd4-462d-11ed-b878-0242ac120002",
                             "IMeshLoader",
                             "Load a mesh from a file");


#endif // SOLAR_IMESHLOADER_H
