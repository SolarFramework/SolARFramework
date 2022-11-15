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

#ifndef SOLAR_SERVICEMANAGERPIPELINE_H
#define SOLAR_SERVICEMANAGERPIPELINE_H

#include "api/pipeline/IPipeline.h"
#include "xpcf/core/helpers.h"

namespace SolAR {
namespace api {
namespace pipeline {

/**
 * @class IServiceManagerPipeline
 * @brief <B>Defines the service manager interface.</B>
 * <TT>UUID: 48c83eda-6432-11ed-81ce-0242ac120002</TT>
 *
 * This class provides the interface to define a manager for all SolAR remote services.
 */

class [[xpcf::clientUUID("600ca5f4-6432-11ed-81ce-0242ac120002")]] [[xpcf::serverUUID("65c3a736-6432-11ed-81ce-0242ac120002")]] IServiceManagerPipeline :
    virtual public IPipeline {
public:
    /// @brief IServiceManagerPipeline default constructor
    IServiceManagerPipeline() = default;

    /// @brief IServiceManagerPipeline default destructor
    virtual ~IServiceManagerPipeline() = default;

    /// @brief Test
    /// @return FrameworkReturnCode::_SUCCESS
    virtual FrameworkReturnCode test() = 0;
};

} // pipeline
} // api
} // SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IServiceManagerPipeline,
                             "48c83eda-6432-11ed-81ce-0242ac120002",
                             "IServiceManagerPipeline",
                             "The interface to define the service manager")

#endif // SOLAR_SERVICEMANAGERPIPELINE_H
