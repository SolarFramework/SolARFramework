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

#ifndef IMAPFROMIMAGEPROCESSING_H
#define IMAPFROMIMAGEPROCESSING_H

#include "api/map/IMapFromDatastructureProcessing.h"
#include "datastructure/Image.h"

namespace SolAR {
namespace api {
namespace map {

/**
 * @class IMapFromImageProcessing
 * @brief <B>Abstract class defining a generic base interface for interfaces that specify processing on SolAR Image in order to generate a new SolAR Map.</B>
 * <TT>UUID: 0a0c8c19-67f9-498d-b581-82d574afd20b</TT>
 *
 */

class XPCF_IGNORE IMapFromImageProcessing : virtual public IMapFromDatastructureProcessing
{

public:

    ///@brief IMapFromImageProcessing default destructor.
    virtual ~IMapFromImageProcessing() override = default;

    /// @brief Create a new map resulting from the processing of a set of images
    /// @param[in] images the set of images to process
    /// @return FrameworkReturnCode::_SUCCESS if the processing succeed, else FrameworkReturnCode::_ERROR_
    /// @note This method is not applicable for this interface
    virtual FrameworkReturnCode createMap(const std::vector<SRef<SolAR::datastructure::Image>>& images) = 0;

};

} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::IMapFromImageProcessing,
                             "0a0c8c19-67f9-498d-b581-82d574afd20b",
                             "IMapFromImageProcessing",
                             "IMapFromImageProcessing interface description");

#endif // IMAPFROMIMAGEPROCESSING_H
