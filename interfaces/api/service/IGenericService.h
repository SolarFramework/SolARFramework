/**
 * @copyright Copyright (c) 2022-2023 B-com http://www.b-com.com/
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

#ifndef SOLAR_GENERICSERVICE_H
#define SOLAR_GENERICSERVICE_H

#include "core/Messages.h"
#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/api/IComponentManager.h>
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace service {

/**
 * @class IGenericService
 * @brief <B>Defines the service managing a generic  service.</B>
 * <TT>UUID: d193e3e4-54e8-44ff-b7f8-2ffdba2b04e9</TT>
 *
 * This class provides the interface to define a generic service with just an init, start and stop function.
 */

class XPCF_IGNORE XPCF_CLIENTUUID("0c98c9b8-cabb-4e6e-93fb-23cbbfc528e7") XPCF_SERVERUUID("af057b41-75fa-4db3-a502-55b6ffba0962")
    IServiceWorldGraph : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IGenericService default constructor
    IGenericService() = default;

    /// @brief IGenericService default destructor
    virtual ~IGenericService() = default;

    /// @brief Initialization of the service
    /// @return FrameworkReturnCode::_SUCCESS if the init succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode init() = 0;

    /// @brief start the Service managing a world graph
    /// @return FrameworkReturnCode::_SUCCESS if the service is started, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode start() = 0;

    /// @brief stop the Service managing a world graph
    /// @return FrameworkReturnCode::_SUCCESS if the service is stopped, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode stop() = 0;

};

} // service
} // api
} // SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::service::IGenericService,
                             "d193e3e4-54e8-44ff-b7f8-2ffdba2b04e9",
                             "IGenericService",
                             "The interface to define the generic service with an init, start and stop function.")

#endif // SOLAR_GENERICSERVICE_H
