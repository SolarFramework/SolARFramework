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

#ifndef SOLAR_SERVICEMANAGER_H
#define SOLAR_SERVICEMANAGER_H

#include "core/Messages.h"
#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/api/IComponentManager.h>
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace service {

///
/// @typedef ServiceType
/// @brief <B>Indicate the type of the service</B>
///
enum class ServiceType {
    MAP_UPDATE_SERVICE = 0,
    RELOCALIZATION_SERVICE = 1,
    RELOCALIZATION_MARKERS_SERVICE = 2,
    MAPPING_SERVICE = 3,
    MAPPING_STEREO_SERVICE = 4,
    MAP_PROCESSING_SFM_SERVICE = 5,
    MAP_PROCESSING_DENSE_MAPPING_SERVICE = 6
};

/// @brief Return the name (string) of a service according to its type
/// @param[in] serviceType type of the service
/// @return the name of the service (string)
static std::string getServiceName(const ServiceType serviceType)
{
    std::string serviceName = "";

    switch(serviceType) {
    case ServiceType::MAP_UPDATE_SERVICE:
        serviceName = "Map Update Service";
        break;
    case ServiceType::RELOCALIZATION_SERVICE:
        serviceName = "Relocalization Service";
        break;
    case ServiceType::RELOCALIZATION_MARKERS_SERVICE:
        serviceName = "Relocalization Markers Service";
        break;
    case ServiceType::MAPPING_SERVICE:
        serviceName = "Mapping Service";
        break;
    case ServiceType::MAPPING_STEREO_SERVICE:
        serviceName = "Stereo Mapping Service";
        break;
    case ServiceType::MAP_PROCESSING_SFM_SERVICE:
        serviceName = "Map Processing Structure From Motion Service";
        break;
    case ServiceType::MAP_PROCESSING_DENSE_MAPPING_SERVICE:
        serviceName = "Map Processing Dense Mapping Service";
        break;
    default:
        serviceName = "Unknown service";
        break;
    }

    return serviceName;
}

/**
 * @class IServiceManager
 * @brief <B>Defines the service manager interface.</B>
 * <TT>UUID: 48c83eda-6432-11ed-81ce-0242ac120002</TT>
 *
 * This class provides the interface to define a manager for all SolAR remote services.
 */

class XPCF_CLIENTUUID("600ca5f4-6432-11ed-81ce-0242ac120002") XPCF_SERVERUUID("65c3a736-6432-11ed-81ce-0242ac120002")
    IServiceManager : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IServiceManager default constructor
    IServiceManager() = default;

    /// @brief IServiceManager default destructor
    virtual ~IServiceManager() = default;

    /// @brief Register a new service to the service manager
    /// @param[in] serviceType type of the service
    /// @param[in] serviceURL URL of the service
    /// @return FrameworkReturnCode::_SUCCESS if the service is registered, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode registerService(const ServiceType serviceType, const std::string & serviceURL) = 0;

    /// @brief Unregister a service from the service manager
    /// @param[in] serviceType type of the service
    /// @param[in] serviceURL URL of the service
    /// @return FrameworkReturnCode::_SUCCESS if the service is unregistered, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode unregisterService(const ServiceType serviceType, const std::string & serviceURL) = 0;

    /// @brief Get an available URL for a specific service type
    /// @param[in] serviceType type of the service
    /// @param[out] serviceURL URL of the service
    /// @return FrameworkReturnCode::_SUCCESS if a service URL is available, else
    ///         FrameworkReturnCode::_NO_SERVICE_REGISTERED if no service of the given type is registered
    ///         FrameworkReturnCode::_NO_SERVICE_AVAILABLE if no service of the given type is available
    ///         FrameworkReturnCode::_ERROR_ for other errors
    virtual FrameworkReturnCode getService(const ServiceType serviceType, std::string & serviceURL) const = 0;

    /// @brief Get an available URL for a specific service type, and lock it for the given UUID
    ///        If a service of the specific type is already locked for the given UUID, return its URL
    /// @param[in] serviceType type of the service
    /// @param[in] uuid UUID of the client or the map
    /// @param[out] serviceURL URL of the service
    /// @return FrameworkReturnCode::_SUCCESS if a service URL is available and the service locked, else
    ///         FrameworkReturnCode::_NO_SERVICE_REGISTERED if no service of the given type is registered
    ///         FrameworkReturnCode::_NO_SERVICE_AVAILABLE if no service of the given type is available
    ///         FrameworkReturnCode::_ERROR_ for other errors
    virtual FrameworkReturnCode getAndLockService(const ServiceType serviceType,
                                                  const std::string & uuid,
                                                  std::string & serviceURL) = 0;

    /// @brief Unlock the service of the given type, for the given UUID and URL
    /// @param[in] serviceType type of the service
    /// @param[in] uuid UUID of the client or the map
    /// @param[in] serviceURL URL of the service
    /// @return FrameworkReturnCode::_SUCCESS if the service is unlocked, else
    ///         FrameworkReturnCode::_NO_SERVICE_LOCKED if no service is locked for the UUID
    ///         FrameworkReturnCode::_ERROR_ for other errors
    virtual FrameworkReturnCode unlockService(const ServiceType serviceType,
                                              const std::string & uuid,
                                              const std::string & serviceURL) = 0;
};

} // service
} // api
} // SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::service::IServiceManager,
                             "48c83eda-6432-11ed-81ce-0242ac120002",
                             "IServiceManager",
                             "The interface to define the service manager")

#endif // SOLAR_SERVICEMANAGER_H
