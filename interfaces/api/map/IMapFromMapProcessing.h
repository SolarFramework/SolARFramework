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

#ifndef IMAPFROMMAPPROCESSING_H
#define IMAPFROMMAPPROCESSING_H

#include "api/map/IMapFromDatastructureProcessing.h"
#include "datastructure/Map.h"

namespace SolAR {
namespace api {
namespace map {

/**
 * @class IMapFromMapProcessing
 * @brief <B>Abstract class defining a generic base interface for interfaces that specify processing on SolAR map in order to generate a new one.</B>
 * <TT>UUID: 56f740d2-571f-442c-86c8-b15140a296bf</TT>
 *
 */

class XPCF_IGNORE IMapFromMapProcessing : virtual public IMapFromDatastructureProcessing
{

public:

    ///@brief IMapFromMapProcessing default destructor.
    virtual ~IMapFromMapProcessing() override = default;

    /// @brief Create a new map resulting from the processing of the original map
    /// @param[in] map the original map
    /// @return FrameworkReturnCode::_SUCCESS if the processing succeed, else FrameworkReturnCode::_ERROR_
    /// @note This method is not applicable for this interface
    virtual FrameworkReturnCode createMap(const SRef<SolAR::datastructure::Map>& map) = 0;

};

} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::IMapFromMapProcessing,
                             "56f740d2-571f-442c-86c8-b15140a296bf",
                             "IMapFromMapProcessing",
                             "IMapFromMapProcessing interface description");

#endif // IMAPFROMMAPPROCESSING_H
