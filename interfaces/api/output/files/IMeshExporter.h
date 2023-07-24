/**
 * @copyright Copyright (c) 2022 B-com http://www.b-com.com/
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

#ifndef SOLAR_IMESHEXPORTER_H
#define SOLAR_IMESHEXPORTER_H

#include <xpcf/api/IComponentIntrospect.h>

#include "core/Messages.h"
#include "datastructure/Mesh.h"

namespace SolAR::api::output::files 
{

/**
 * @class IMeshExporter
 * @brief <B>Exports a mesh to a file.</B>
 * <TT>UUID: faf50760-462c-11ed-b878-0242ac120002</TT>
 *
 */
class XPCF_CLIENTUUID("0e1263d8-462d-11ed-b878-0242ac120002") XPCF_SERVERUUID("14cbf040-462d-11ed-b878-0242ac120002") IMeshExporter :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    IMeshExporter() = default;
    virtual ~IMeshExporter() = default;

    /// @brief Export a Mesh to a file
    /// @param[in] mesh: the mesh to export
    /// @return FrameworkReturnCode::_SUCCESS if export succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode exportMesh(const SRef<SolAR::datastructure::Mesh> & mesh) = 0;
};

} // namespace SolAR::api::output::files 


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::output::files::IMeshExporter,
                             "faf50760-462c-11ed-b878-0242ac120002",
                             "IMeshExporter",
                             "Export a mesh to a file");


#endif // SOLAR_IMESHEXPORTER_H
