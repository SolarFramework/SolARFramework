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
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace pipeline {

///
/// @typedef ServiceType
/// @brief <B>Indicate the type of the service</B>
///
enum class ServiceType {
    MAP_UPDATE_SERVICE = 0,
    RELOCALIZATION_SERVICE = 1,
    RELOCALIZATION_MARKERS_SERVICE = 2,
    MAPPING_SERVICE = 3,
    MAPPING_STEREO_SERVICE = 4
};

/**
 * @class IServiceManagerPipeline
 * @brief <B>Defines the service manager interface.</B>
 * <TT>UUID: 48c83eda-6432-11ed-81ce-0242ac120002</TT>
 *
 * This class provides the interface to define a manager for all SolAR remote services.
 */

class XPCF_CLIENTUUID("600ca5f4-6432-11ed-81ce-0242ac120002") XPCF_SERVERUUID("65c3a736-6432-11ed-81ce-0242ac120002") IServiceManagerPipeline :
    virtual public IPipeline {
public:
    /// @brief IServiceManagerPipeline default constructor
    IServiceManagerPipeline() = default;

    /// @brief IServiceManagerPipeline default destructor
    virtual ~IServiceManagerPipeline() = default;

    /// @brief Register a new service to the service manager
    /// @param[in] serviceType: type of the service
    /// @param[in] serviceURL: URL of the service
    /// @return FrameworkReturnCode::_SUCCESS if the service is registered, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode registerService(const ServiceType serviceType, const std::string & serviceURL) = 0;

    /// @brief Unregister a service from the service manager
    /// @param[in] serviceType: type of the service
    /// @param[in] serviceURL: URL of the service
    /// @return FrameworkReturnCode::_SUCCESS if the service is unregistered, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode unregisterService(const ServiceType serviceType, const std::string & serviceURL) = 0;

    /// @brief Get an available URL for a specific service type
    /// @param[in] serviceType: type of the service
    /// @param[out] serviceURL: URL of the service
    /// @return FrameworkReturnCode::_SUCCESS if a service URL is available, else
    ///         FrameworkReturnCode::_NO_SERVICE_REGISTERED if no service of the given type is registered
    ///         FrameworkReturnCode::_NO_SERVICE_AVAILABLE if no service of the given type is available
    ///         FrameworkReturnCode::_ERROR_ for other errors
    virtual FrameworkReturnCode getService(const ServiceType serviceType, std::string & serviceURL) const = 0;

    /// @brief Get an available URL for a specific service type, and lock it for the given client UUID
    ///        If a service of the specific type is already locked for the given client UUID, return its URL
    /// @param[in] serviceType: type of the service
    /// @param[in] clientUUID: UUID of the client
    /// @param[out] serviceURL: URL of the service
    /// @return FrameworkReturnCode::_SUCCESS if a service URL is available and the service locked, else
    ///         FrameworkReturnCode::_NO_SERVICE_REGISTERED if no service of the given type is registered
    ///         FrameworkReturnCode::_NO_SERVICE_AVAILABLE if no service of the given type is available
    ///         FrameworkReturnCode::_ERROR_ for other errors
    virtual FrameworkReturnCode getAndLockService(const ServiceType serviceType, const std::string & clientUUID,
                                                  std::string & serviceURL) = 0;

    /// @brief Unlock the service of the given type, for the given client UUID
    /// @param[in] serviceType: type of the service
    /// @param[in] clientUUID: UUID of the client
    /// @return FrameworkReturnCode::_SUCCESS if the service is unlocked, else
    ///         FrameworkReturnCode::_NO_SERVICE_LOCKED if no service is locked for the client UUID
    ///         FrameworkReturnCode::_ERROR_ for other errors
    virtual FrameworkReturnCode unlockService(const ServiceType serviceType, const std::string & clientUUID) = 0;
};

} // pipeline
} // api
} // SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IServiceManagerPipeline,
                             "48c83eda-6432-11ed-81ce-0242ac120002",
                             "IServiceManagerPipeline",
                             "The interface to define the service manager")

#endif // SOLAR_SERVICEMANAGERPIPELINE_H
