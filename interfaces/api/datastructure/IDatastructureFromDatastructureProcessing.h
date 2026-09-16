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

#ifndef IDATASTRUCTUREFROMDATASTRUCTUREPROCESSING_H
#define IDATASTRUCTUREFROMDATASTRUCTUREPROCESSING_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace datastructure {

/**
 * @class IDatastructureFromDatastructureProcessing
 * @brief <B>Abstract class defining a generic base interface for interfaces that specify processing on SolAR datastructure in order to generate a new one.</B>
 * <TT>UUID: 08aaa0d1-ec0d-4564-aa0e-5bf6211931cc</TT>
 *
 */

class XPCF_IGNORE IDatastructureFromDatastructureProcessing : virtual public org::bcom::xpcf::IComponentIntrospect
{

public:

    ///@brief IDatastructureFromDatastructureProcessing default destructor.
    virtual ~IDatastructureFromDatastructureProcessing() override = default;

    /// @brief Get current processing progress percentage
    /// @return progress percentage between 0 and 1
    virtual float getProgress() const = 0;

    /// @brief force stop
    virtual void forceStop() = 0;

    /// @brief release memory usage
    virtual void releaseMemoryUsage() = 0;

};

} // namespace datastructure
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::datastructure::IDatastructureFromDatastructureProcessing,
                             "08aaa0d1-ec0d-4564-aa0e-5bf6211931cc",
                             "IDatastructureFromDatastructureProcessing",
                             "IDatastructureFromDatastructureProcessing interface description");

#endif // IDATASTRUCTUREFROMDATASTRUCTUREPROCESSING_H
