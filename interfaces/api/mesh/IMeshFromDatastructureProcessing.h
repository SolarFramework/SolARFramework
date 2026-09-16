/**
 * @copyright Copyright (c) 2026 B-com http://www.b-com.com/
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

#ifndef IMESHFROMDATASTRUCTUREPROCESSING_H
#define IMESHFROMDATASTRUCTUREPROCESSING_H

#include "api/datastructure/IDatastructureFromDatastructureProcessing.h"
#include "core/Messages.h"
#include "datastructure/Mesh.h"

namespace SolAR {
namespace api {
namespace mesh {

/**
 * @class IMeshFromDatastructureProcessing
 * @brief <B>Abstract class defining a generic base interface for interfaces that specify processing on SolAR datastructure in order to generate a new SolAR Mesh.</B>
 * <TT>UUID: 09186a13-ba08-4a93-9e79-2c9116fb2377</TT>
 *
 */

class XPCF_IGNORE IMeshFromDatastructureProcessing : virtual public SolAR::api::datastructure::IDatastructureFromDatastructureProcessing
{

public:

    ///@brief IMeshFromDatastructureProcessing default destructor.
    virtual ~IMeshFromDatastructureProcessing() override = default;

    /// @brief Get output mesh resulting from processing
    /// @param[out] mesh the output mesh
    /// @return FrameworkReturnCode::_SUCCESS if mesh was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getOutputMesh(SRef<SolAR::datastructure::Mesh>& mesh) const = 0;

};

} // namespace mesh
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::mesh::IMeshFromDatastructureProcessing,
                             "09186a13-ba08-4a93-9e79-2c9116fb2377",
                             "IMeshFromDatastructureProcessing",
                             "IMeshFromDatastructureProcessing interface description");

#endif // IMESHFROMDATASTRUCTUREPROCESSING_H
