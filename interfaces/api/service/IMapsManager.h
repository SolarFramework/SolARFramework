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
/// @typedef GetMapRequestOption
/// @brief <B>Indicate if keyframe images must be kept or not in map datastructure</B>
///

enum class GetMapRequestOption {
    WITH_KEYFRAME_IMAGES = 0,
    WITHOUT_KEYFRAME_IMAGES = 1
};

///
/// @typedef MapProcessingType
/// @brief <B>Define the different types of map processing available</B>
///
enum class MapProcessingType {
    UNDEFINED = 0,
    STRUCTURE_FROM_MOTION = 1,
    DENSE_MAPPING = 2
};

/// @brief Return the text definition (string) of a MapProcessingType object
/// @param[in] mapProcessingType the map processing type
/// @return the text definition (string)
static std::string toString(const MapProcessingType mapProcessingType)
{
    std::string textDefinition = "";

    switch (mapProcessingType) {
        case MapProcessingType::UNDEFINED:
            textDefinition = "UNDEFINED";
            break;
        case MapProcessingType::STRUCTURE_FROM_MOTION:
            textDefinition = "STRUCTURE_FROM_MOTION";
            break;
        default:
            textDefinition = "Unknown value";
            break;
    }

    return textDefinition;
}

///
/// @typedef MapProcessingStatus
/// @brief <B>Indicate the status of a map processing</B>
///
enum class MapProcessingStatus {
    NO_PROCESSING = 0,    // No current processing for the map
    IN_PROGRESS = 1,      // Processing for the map still in progress
    FAILED = 2,           // Processing failed (and stopped) for the map
    COMPLETED = 3         // Processing completed and successful for the map
};

/// @brief Return the text definition (string) of a MapProcessingStatus object
/// @param[in] mapProcessingStatus the map processing status
/// @return the text definition (string)
static std::string toString(const MapProcessingStatus mapProcessingStatus)
{
    std::string textDefinition = "";

    switch (mapProcessingStatus) {
        case MapProcessingStatus::NO_PROCESSING:
            textDefinition = "NO_PROCESSING";
            break;
        case MapProcessingStatus::IN_PROGRESS:
            textDefinition = "IN_PROGRESS";
            break;
        case MapProcessingStatus::FAILED:
            textDefinition = "FAILED";
            break;
        case MapProcessingStatus::COMPLETED:
            textDefinition = "COMPLETED";
            break;
    default:
            textDefinition = "Unknown value";
            break;
    }

    return textDefinition;
}

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
    /// @param[in] keyframeImagesOption indicate if the keyframe images are requested in output datastructure (requested by default)
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the map is available
    /// * FrameworkReturnCode::_UNKNOWN_MAP_UUID if mapUUID is unkown
    /// * else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getMapRequest(
        const std::string & mapUUID,
        SRef<SolAR::datastructure::Map> & map,
        const SolAR::api::service::GetMapRequestOption & keyframeImagesOption = SolAR::api::service::GetMapRequestOption::WITH_KEYFRAME_IMAGES) const = 0;

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

    /// @brief Request the map manager for information on a specific map
    /// @param[in] mapUUID UUID of the map
    /// @param[out] version the version of the framework used to create the map
    /// @param[out] globalDescriptorType the global descriptor type used for the map
    /// @param[out] descriptorType the descriptor type used to extract descriptor for each keyframe
    /// @param[out] dataSize global size of the data structure of the map (in bytes)
    /// @param[out] areImageSaved true if images are saved with keyframes, false otherwise
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the map information is available
    /// * FrameworkReturnCode::_UNKNOWN_MAP_UUID if mapUUID is unkown
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getMapInfo(const std::string & mapUUID,
                                           std::string & version,
                                           SolAR::datastructure::GlobalDescriptorType & globalDescriptorType,
                                           SolAR::datastructure::DescriptorType & descriptorType,
                                           uint32_t & dataSize,
                                           bool & areImageSaved) const = 0;

    /// @brief Request for a map processing giving the type of process to apply (asynchronous)
    /// @param[in] mapUUID the UUID of the map to process
    /// @param[in] resultMapUUID the UUID of the new map resulting from the processing
    /// @param[in] processingType the type of process to apply on the map
    /// @return FrameworkReturnCode::_SUCCESS if processing is able to proceed
    ///         FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available
    ///         else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode requestMapProcessing(const std::string & mapUUID,
                                                     const std::string & resultMapUUID,
                                                     const MapProcessingType processingType) = 0;

    /// @brief Get status and progress percentage concerning a map processing in progress
    ///        If status = COMPLETED then give the map UUID of the new resulting map
    /// @param[in] resultMapUUID the UUID of the map resulting from the processing
    /// @param[out] status the current map processing status
    /// @param[out] processingType the current map processing type
    /// @param[out] progress the current progress percentage (valid value should be between 0 and 1)
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the status and progress are available
    /// * FrameworkReturnCode::_NOT_FOUND if data is not available
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getMapProcessingStatus(const std::string & resultMapUUID,
                                                       MapProcessingStatus & status,
                                                       MapProcessingType & processingType,
                                                       float & progress) = 0;

    /// @brief Provide the current data from a map processing for visualization
    /// (resulting from all map processing since the start of the pipeline)
    /// @param[in] resultMapUUID the UUID of the map resulting from the processing
    /// @param[out] pointCloud pipeline current point cloud
    /// @param[out] keyframePoses pipeline current keyframe poses
    /// * FrameworkReturnCode::_SUCCESS if data is available
    /// * FrameworkReturnCode::_NOT_FOUND if data is not available
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getMapProcessingData(const std::string & resultMapUUID,
                                                     std::vector<SRef<SolAR::datastructure::CloudPoint>> & pointCloud,
                                                     std::vector<SolAR::datastructure::Transform3Df> & keyframePoses) = 0;

};

} // service
} // api
} // SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::service::IMapsManager,
                             "3ae30e7d-9685-4860-8510-89fe98035a0f",
                             "IMapsManager",
                             "The interface to define the maps manager")

#endif // SOLAR_MAPSMANAGER_H
