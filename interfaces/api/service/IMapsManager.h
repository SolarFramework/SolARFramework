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
#include "datastructure/Map.h"
#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/api/IComponentManager.h>
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace service {

///
/// @typedef MapProcessingType
/// @brief <B>Define the different types of map processing available</B>
///
typedef enum {
    UNDEFINED = 0,
    STRUCTURE_FROM_MOTION = 1
} MapProcessingType;

///
/// @typedef MapProcessingStatus
/// @brief <B>Indicate the status of a map processing</B>
///
typedef enum {
    NO_PROCESSING = 0,    // No current processing for the map
    IN_PROGRESS = 1,      // Processing for the map still in progress
    FAILED = 2,           // Processing failed (and stopped) for the map
    COMPLETED = 3         // Processing completed and successful for the map
} MapProcessingStatus;

/**
 * @class IMapsManager
 * @brief <B>Defines the maps manager interface.</B>
 * <TT>UUID: 3ae30e7d-9685-4860-8510-89fe98035a0f</TT>
 *
 * This class provides the interface to define a manager for all SolAR maps.
 */

class XPCF_CLIENTUUID("4863f2d1-023c-4095-8842-e6083e6ec54a") XPCF_SERVERUUID("2bc10e03-8a2d-44a1-b53e-d72d09f99b9b")
    XPCF_GRPC_CLIENT_RECV_SIZE("-1") XPCF_GRPC_CLIENT_SEND_SIZE("-1")
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

    /// @brief Request the map manager to get the datastructure of a specific map
    /// @param[in] mapUUID UUID of the map
    /// @param[out] map the output map datastructure
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the map is available
    /// * FrameworkReturnCode::_UNKNOWN_MAP_UUID if mapUUID is unkown
    /// * else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getMapRequest(
        const std::string & mapUUID,
        SRef<SolAR::datastructure::Map> & map) const = 0;

    /// @brief Request the map manager to update the datastructure of a specific map
    /// @param[in] mapUUID UUID of the map to use
    /// @param[in] mapDatastructure the input map datastructure
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    [[grpc::client_sendSize("-1")]] virtual FrameworkReturnCode setMapRequest(
        const std::string & mapUUID,
        const SRef<SolAR::datastructure::Map> mapDatastructure) = 0;

    /// @brief Request the map manager to get the point cloud of a map
    /// @param[in] mapUUID UUID of the map
    /// @param[out] pointCloud the output point cloud
    /// @return FrameworkReturnCode::_SUCCESS if the point cloud is available, else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getPointCloudRequest(
        const std::string & mapUUID,
        SRef<SolAR::datastructure::PointCloud> & pointCloud) const = 0;

    /// @brief Register a new Map Processing service to the map manager
    /// @param[in] processingType the type of process managed by the service
    /// @param[in] serviceURL URL of the Map Processing service
    /// @return FrameworkReturnCode::_SUCCESS if the Map Processing service is registered, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode registerMapProcessingService(const MapProcessingType & processingType,
                                                             const std::string & serviceURL) = 0;

    /// @brief Unregister a Map Processing service from the map manager
    /// @param[in] processingType the type of process managed by the service
    /// @param[in] serviceURL URL of the Map Processing service
    /// @return FrameworkReturnCode::_SUCCESS if the Map Processing service is unregistered, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode unregisterMapProcessingService(const MapProcessingType & processingType,
                                                               const std::string & serviceURL) = 0;

    /// @brief Request for a map processing giving the type of process to apply (asynchronous)
    /// @param[in] mapUUID the UUID of the map to process
    /// @param[in] processingType the type of process to apply on the map
    /// @return FrameworkReturnCode::_SUCCESS if processing is able to proceed
    ///         FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available
    ///         else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode requestForMapProcessing(const std::string & mapUUID,
                                                        const MapProcessingType & processingType) = 0;

    /// @brief Get status and progress percentage concerning a map processing in progress
    ///        If status = COMPLETED then give the map UUID of the new resulting map
    /// @param[in] mapUUID the UUID of the map being processed
    /// @param[out] status the current map processing status
    /// @param[out] progress the current progress percentage (valid value should be between 0 and 1)
    /// @param[out] resultingMapUUID the map UUID of the new created map (processing result)
    /// @return FrameworkReturnCode::_SUCCESS if the status and progress are available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getStatusForMapProcessing(const std::string & mapUUID,
                                                          MapProcessingStatus & status,
                                                          float & progress,
                                                          std::string & resultingMapUUID) const = 0;

    /// @brief Provide the current data from a map processing for visualization
    /// (resulting from all map processing since the start of the pipeline)
    /// @param[in] mapUUID the UUID of the map being processed
    /// @param[out] pointCloud pipeline current point cloud
    /// @param[out] keyframePoses pipeline current keyframe poses
    /// @return FrameworkReturnCode::_SUCCESS if data is available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getDataForMapProcessing(const std::string & mapUUID,
                                                        std::vector<SRef<SolAR::datastructure::CloudPoint>> & pointCloud,
                                                        std::vector<SolAR::datastructure::Transform3Df> & keyframePoses) const = 0;

};

} // service
} // api
} // SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::service::IMapsManager,
                             "3ae30e7d-9685-4860-8510-89fe98035a0f",
                             "IMapsManager",
                             "The interface to define the maps manager")

#endif // SOLAR_MAPSMANAGER_H
