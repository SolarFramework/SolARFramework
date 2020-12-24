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

#ifndef IPIPELINE_H
#define IPIPELINE_H


#include <xpcf/api/IComponentIntrospect.h>
#include "xpcf/api/IComponentManager.h"
#include "core/Messages.h"

namespace xpcf  = org::bcom::xpcf;
namespace SolAR {
namespace api {
namespace pipeline {

/**
 * @class IPipeline
 * @brief <B>Abstract class defining a generic pipeline object.</B>
 * <TT>UUID: b636f583-4f1e-41c9-94da-9d0eac82aa02</TT>
 *
 * This class defines a generic pipeline interface.
 */
class [[xpcf::ignore]] IPipeline : virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
    virtual ~IPipeline() override = default;

    /// @brief Initialization of the pipeline
    /// Initialize the pipeline by providing a reference to the component manager loaded by the PipelineManager.
    /// @param[in] componentManager: a shared reference to the component manager which has loaded
    /// the components and configuration in the pipleine manager
    virtual FrameworkReturnCode init(SRef<xpcf::IComponentManager> componentManager) = 0;

    /// @brief Start the pipeline
    /// @return FrameworkReturnCode::_SUCCESS if the stard succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode start() = 0;

    /// @brief Stop the pipeline.
    /// @return FrameworkReturnCode::_SUCCESS if the stop succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode stop() = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IPipeline,
                             "b636f583-4f1e-41c9-94da-9d0eac82aa02",
                             "IPipeline",
                             "The generic pipeline interface");

#endif // IPIPELINE_H
