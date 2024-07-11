/**
 * @copyright Copyright (c) 2022-2024 B-com http://www.b-com.com/
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

#ifndef SOLAR_MAPSMANAGER_H
#define SOLAR_MAPSMANAGER_H

#include "core/Messages.h"
#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/api/IComponentManager.h>
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace service {

/**
 * @class IMapsManager
 * @brief <B>Defines the maps manager interface.</B>
 * <TT>UUID: 3ae30e7d-9685-4860-8510-89fe98035a0f</TT>
 *
 * This class provides the interface to define a manager for all SolAR maps.
 */

class XPCF_CLIENTUUID("4863f2d1-023c-4095-8842-e6083e6ec54a") XPCF_SERVERUUID("2bc10e03-8a2d-44a1-b53e-d72d09f99b9b")
    IMapsManager : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IMapsManager default constructor
    IMapsManager() = default;

    /// @brief IMapsManager default destructor
    virtual ~IMapsManager() = default;

    /// @brief Create a new map which will be managed by the maps manager instance
    /// @param[in] mapUUID UUID of the map to create
    /// @return FrameworkReturnCode::_SUCCESS if the map is created, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMap(const std::string & mapUUID) = 0;

    /// @brief Delete a map managed by the maps manager instance
    /// @param[in] mapUUID UUID of the map to delete
    /// @return FrameworkReturnCode::_SUCCESS if the map is deleted, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode deleteMap(const std::string & mapUUID) = 0;

    /// @brief Get the list of all maps (UUID) managed by the maps manager instance
    /// @param[out] mapUUIDList list of UUID of all maps
    /// @return FrameworkReturnCode::_SUCCESS if the method succeeds, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getAllMaps(std::vector<std::string> & mapUUIDList) const = 0;

    /// @brief Register a new MapUpdate service to the map manager
    /// @param[in] serviceURL URL of the MapUpdate service
    /// @return FrameworkReturnCode::_SUCCESS if the MapUpdate service is registered, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode registerMapUpdateService(const std::string & serviceURL) = 0;

    /// @brief Unregister a MapUpdate service from the map manager
    /// @param[in] serviceURL URL of the MapUpdate service
    /// @return FrameworkReturnCode::_SUCCESS if the MapUpdate service is unregistered, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode unregisterMapUpdateService(const std::string & serviceURL) = 0;

    /// @brief Increase the number of clients using the map defined by its UUID
    /// @brief and return the URL of the MapUpdate service instance handling this map
    /// @param[in] mapUUID UUID of the map used by client
    /// @param[out] serviceURL URL of the MapUpdate service instance managing the map
    /// @return FrameworkReturnCode::_SUCCESS if a MapUpdate service URL is available, else
    ///         FrameworkReturnCode::_NO_SERVICE_REGISTERED if no MapUpdate service is registered
    ///         FrameworkReturnCode::_NO_SERVICE_AVAILABLE if no MapUpdate service is available
    ///         FrameworkReturnCode::_ERROR_ for other errors
    virtual FrameworkReturnCode increaseMapClients(const std::string & mapUUID, std::string & serviceURL) = 0;

    /// @brief Decrease the number of clients using the map defined by its UUID
    /// @param[in] mapUUID UUID of the map no more used by client
    /// @return FrameworkReturnCode::_SUCCESS if the method succeeds, else
    ///         FrameworkReturnCode::_NO_SERVICE_AVAILABLE if no MapUpdate service is handling the map
    ///         FrameworkReturnCode::_ERROR_ for other errors
    virtual FrameworkReturnCode decreaseMapClients(const std::string & mapUUID) = 0;
};

} // service
} // api
} // SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::service::IMapsManager,
                             "3ae30e7d-9685-4860-8510-89fe98035a0f",
                             "IMapsManager",
                             "The interface to define the maps manager")

#endif // SOLAR_MAPSMANAGER_H
