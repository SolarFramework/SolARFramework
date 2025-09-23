/**
 * @copyright Copyright (c) 2021-2023 B-com http://www.b-com.com/
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

#ifndef SOLAR_FRONTEND_H
#define SOLAR_FRONTEND_H


#include "api/pipeline/IMappingPipeline.h"
#include "api/service/IClientContextManager.h"
#include "api/service/IMapsManager.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/Map.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/PointCloud.h"
#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/api/IComponentManager.h>
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace service {

/**
 * @struct ClientInfo
 * @brief <B>Define information on a client using a map.</B>
 */
struct ClientInfo
{
    std::string clientUUID;                         // Unique ID of the client
    DeviceInfo deviceInfo;                          // Information on the device used by the client
    TransformStatus transform3DStatus;              // The status of the current 3D transformation matrix
    SolAR::datastructure::Transform3Df transform3D; // The current 3D transformation matrix (if available)
    PipelineMode pipelineMode;                      // Current mode used for image processing

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /* version */)
    {
        ar & clientUUID;
        ar & deviceInfo;
        ar & transform3DStatus;
        ar & transform3D;
        ar & pipelineMode;
    }
};

/**
 * @class IFrontEnd
 * @brief <B>Defines the front end interface for services.</B>
 * <TT>UUID: 58389ff0-5695-11ec-bf63-0242ac130002</TT>
 *
 * This class provides the interface to define a front end for services.
 */
class XPCF_CLIENTUUID("91a569da-5695-11ec-bf63-0242ac130002") XPCF_SERVERUUID("95913e8e-5695-11ec-bf63-0242ac130002")
    XPCF_GRPC_CLIENT_RECV_SIZE("-1") XPCF_GRPC_CLIENT_SEND_SIZE("-1")
    IFrontEnd : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IFrontEnd default constructor
    IFrontEnd() = default;

    /// @brief IFrontEnd default destructor
    virtual ~IFrontEnd() = default;

    /// @brief Register a new client, set the map to use (for mapping/relocalization)
    /// @brief and return its UUID to use for future requests
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] deviceInfo information on the client's device
    /// @param[in] worldElementUUID the UUID of the world element to use for the World Graph request
    /// @param[out] clientUUID the UUID for this new client
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the client is registered with its UUID
    /// * FrameworkReturnCode::_AUTHENT_SERVICE_UNAVAILABLE if authentication server is unavailable
    /// * FrameworkReturnCode::_AUTHENT_REQUEST_FAILURE if the request to the authentication server failed
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * FrameworkReturnCode::_AUTHENT_RESOURCE_NOT_FOUND if the requested resource was not found on the authentication server
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode registerClient(const std::string & accessToken,
                                               const DeviceInfo & deviceInfo,
                                               const std::string & worldElementUUID,
                                               std::string & clientUUID) = 0;

    /// @brief Unregister a client using its UUID
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID the UUID of the client to unregister
    /// @return FrameworkReturnCode::_SUCCESS if the client is unregistered, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode unregisterClient(const std::string & accessToken,
                                                 const std::string & clientUUID) = 0;

    /// @brief Return all current clients UUID
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[out] clientUUIDList the list of UUID of all clients currently registered
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the method succeeds
    /// * FrameworkReturnCode::_AUTHENT_SERVICE_UNAVAILABLE if authentication server is unavailable
    /// * FrameworkReturnCode::_AUTHENT_REQUEST_FAILURE if the request to the authentication server failed
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * FrameworkReturnCode::_AUTHENT_RESOURCE_NOT_FOUND if the requested resource was not found on the authentication server
    /// * else FrameworkReturnCode::_ERROR_
    [[deprecated("use getClientInfoForMap to get information on clients currently using a map")]]
    virtual FrameworkReturnCode getAllClientsUUID(const std::string & accessToken,
                                                  std::vector<std::string> & clientUUIDList) const = 0;

    /// @brief Return the device information for the given client UUID
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @param[out] deviceInfo information on the client's device
    /// @return FrameworkReturnCode::_SUCCESS if the method succeeds, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getDeviceInfo(const std::string & accessToken,
                                              const std::string & clientUUID,
                                              DeviceInfo & deviceInfo) const = 0;

    /// @brief Initialization of the service
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @return FrameworkReturnCode::_SUCCESS if the init succeed, FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available else FrameworkReturnCode::_ERROR_
    [[deprecated("must set the pipeline mode on init")]]
    virtual FrameworkReturnCode init(const std::string & accessToken,
                                     const std::string & clientUUID) = 0;

    /// @brief Init the service and specify the mode for the pipeline processing
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @param[in] pipelineMode mode to use for pipeline processing
    /// @return FrameworkReturnCode::_SUCCESS if the mode is correctly initialized, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode init(const std::string & accessToken,
                                     const std::string & clientUUID,
                                     PipelineMode pipelineMode) = 0;

    /// @brief Start the service
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @return FrameworkReturnCode::_SUCCESS if the stard succeed, FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode start(const std::string & accessToken,
                                      const std::string & clientUUID) = 0;

    /// @brief Stop the service.
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @return FrameworkReturnCode::_SUCCESS if the stop succeed, FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode stop(const std::string & accessToken,
                                     const std::string & clientUUID) = 0;

    /// @brief Return the current mode used for the pipeline processing
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @param[out] pipelineMode the current pipeline mode
    /// @return FrameworkReturnCode::_SUCCESS if the method succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getProcessingMode(const std::string & accessToken,
                                                  const std::string & clientUUID,
                                                  PipelineMode & pipelineMode) const = 0;

    /// @brief Set the camera parameters
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @param[in] cameraParams the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCameraParameters(const std::string & accessToken,
                                                    const std::string & clientUUID,
                                                    const SolAR::datastructure::CameraParameters & cameraParams) = 0;

    /// @brief Set the camera parameters (use for stereo camera)
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @param[in] cameraParams1 the camera parameters of the first camera
    /// @param[in] cameraParams2 the camera parameters of the second camera
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCameraParameters(const std::string & accessToken,
                                                    const std::string & clientUUID,
                                                    const SolAR::datastructure::CameraParameters & cameraParams1,
                                                    const SolAR::datastructure::CameraParameters & cameraParams2) = 0;

    /// @brief Set the rectification parameters (use for stereo camera)
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @param[in] rectCam1 the rectification parameters of the first camera
    /// @param[in] rectCam2 the rectification parameters of the second camera
    /// @return FrameworkReturnCode::_SUCCESS if the rectification parameters are correctly set, else FrameworkReturnCode::_ERROR_
    [[deprecated("no more use of this method")]]
    virtual FrameworkReturnCode setRectificationParameters(const std::string & accessToken,
                                                           const std::string & clientUUID,
                                                           const SolAR::datastructure::RectificationParameters & rectCam1,
                                                           const SolAR::datastructure::RectificationParameters & rectCam2) = 0;

    /// @brief Get the camera parameters
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @param[out] cameraParams the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly returned, FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCameraParameters(const std::string & accessToken,
                                                    const std::string & clientUUID,
                                                    SolAR::datastructure::CameraParameters & cameraParams) const = 0;

    /// @brief Request the front end to process a new image for mapping or relocalization (depending on the pipeline mode)
    /// @brief the corresponding 3D transformation to the SolAR coordinates system
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @param[in] images the images to process
    /// @param[in] poses the poses associated to images in the client coordinates system
    /// @param[in] fixedPose the input poses are considered as ground truth
    /// @param[in] worldTransform AR device coordinate system (in which poses are defined) to World origin (ex: BIM origin). Pass zero-filled matrix if not set.
    /// @param[in] timestamp the timestamp of the image
    /// @param[out] transform3DStatus the status of the current 3D transformation matrix
    /// @param[out] transform3D the current 3D transformation matrix (if available)
    /// @param[out] confidence the confidence score of the 3D transformation matrix
    /// @param[out] mappingStatus the status of the current mapping processing
    /// @param[out] detectedObjects list of objects detected in the last processed image
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode imageProcessRequest(const std::string & accessToken,
                                                    const std::string & clientUUID,
                                                    const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                                    const std::vector<SolAR::datastructure::Transform3Df> & poses,
                                                    bool fixedPose,
                                                    const SolAR::datastructure::Transform3Df & worldTransform,
                                                    const std::chrono::system_clock::time_point & timestamp,
                                                    TransformStatus & transform3DStatus,
                                                    SolAR::datastructure::Transform3Df & transform3D,
                                                    float_t & confidence,
                                                    SolAR::api::pipeline::MappingStatus & mappingStatus,
                                                    std::vector<SolAR::datastructure::DetectedObject> & detectedObjects) = 0;

    /// @brief Provide the current data from the mapping service context
    /// @brief (resulting from all mapping processing since the start of the service)
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @param[out] outputPointClouds service current point clouds
    /// @param[out] keyframePoses service current keyframe poses
    /// @return FrameworkReturnCode::_SUCCESS if data are available, FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getMappingDataRequest(
                                            const std::string & accessToken,
                                            const std::string & clientUUID,
                                            std::vector<SRef<SolAR::datastructure::CloudPoint>> & outputPointClouds,
                                            std::vector<SolAR::datastructure::Transform3Df> & keyframePoses) const = 0;

    /// @brief Request the front end to get the 3D transform offset
    /// @brief between the device coordinate system and the SolAR coordinate system
    /// @brief and the last pose processed by the service in the specified coordinate system
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @param[out] transform3DStatus the status of the current 3D transformation matrix
    /// @param[out] transform3D the current 3D transformation matrix (if available)
    /// @param[out] confidence the confidence score of the 3D transformation matrix
    /// @param[out] pose the last pose if available
    /// @param[in] poseType the type of the requested pose
    ///            - in the SolAR coordinate system (by default)
    ///            - in the device coordinate system
    virtual FrameworkReturnCode getClientPose(const std::string & accessToken,
                                              const std::string & clientUUID,
                                              TransformStatus & transform3DStatus,
                                              SolAR::datastructure::Transform3Df & transform3D,
                                              float_t & confidence,
                                              SolAR::datastructure::Transform3Df & pose,
                                              const PoseType poseType = PoseType::SOLAR_POSE) = 0;

    /// @brief Create a new map specified by its UUID
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] mapUUID the UUID of the map to create
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the map is created with its UUID
    /// * FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available
    /// * FrameworkReturnCode::_AUTHENT_SERVICE_UNAVAILABLE if authentication server is unavailable
    /// * FrameworkReturnCode::_AUTHENT_REQUEST_FAILURE if the request to the authentication server failed
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * FrameworkReturnCode::_AUTHENT_RESOURCE_NOT_FOUND if the requested resource was not found on the authentication server
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMap(const std::string & accessToken,
                                          const std::string & mapUUID) = 0;

    /// @brief Delete a map specified by its UUID (if not used by some clients)
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] mapUUID the UUID of the map to delete
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the map is deleted
    /// * FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available
    /// * FrameworkReturnCode::_AUTHENT_SERVICE_UNAVAILABLE if authentication server is unavailable
    /// * FrameworkReturnCode::_AUTHENT_REQUEST_FAILURE if the request to the authentication server failed
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * FrameworkReturnCode::_AUTHENT_RESOURCE_NOT_FOUND if the requested resource was not found on the authentication server
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode deleteMap(const std::string & accessToken,
                                          const std::string & mapUUID) = 0;

    /// @brief Return all available maps UUID
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[out] mapUUIDList the list of UUID of all maps currently available
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the method succeeds
    /// * FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available
    /// * FrameworkReturnCode::_AUTHENT_SERVICE_UNAVAILABLE if authentication server is unavailable
    /// * FrameworkReturnCode::_AUTHENT_REQUEST_FAILURE if the request to the authentication server failed
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * FrameworkReturnCode::_AUTHENT_RESOURCE_NOT_FOUND if the requested resource was not found on the authentication server
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getAllMapsUUID(const std::string & accessToken,
                                               std::vector<std::string> & mapUUIDList) const = 0;

    /// @brief Return the map UUID used by a client specified by its UUID
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] clientUUID UUID of the client
    /// @param[out] mapUUID UUID of the map used by the client
    /// @return FrameworkReturnCode::_SUCCESS if the method succeeds, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getClientMapUUID(const std::string & accessToken,
                                                 const std::string & clientUUID,
                                                 std::string & mapUUID) const = 0;

    /// @brief Return a list of information on each client currently using a given map
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] mapUUID UUID of the map to use
    /// @param[out] clientInfoList list of all the clients currently using the map
    /// @return FrameworkReturnCode::_SUCCESS if the method succeeds, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getClientInfoForMap(const std::string & accessToken,
                                                    const std::string & mapUUID,
                                                    std::vector<ClientInfo> & clientInfoList) const = 0;

    /// @brief Request for the datastructure of a specific map
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] mapUUID UUID of the map to use
    /// @param[out] mapDatastructure the output map datastructure
    /// @param[in] keyframeImagesOption indicate if the keyframe images are requested in output datastructure (requested by default)
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the global map is available
    /// * FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available
    /// * FrameworkReturnCode::_AUTHENT_SERVICE_UNAVAILABLE if authentication server is unavailable
    /// * FrameworkReturnCode::_AUTHENT_REQUEST_FAILURE if the request to the authentication server failed
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * FrameworkReturnCode::_AUTHENT_RESOURCE_NOT_FOUND if the requested resource was not found on the authentication server
    /// * FrameworkReturnCode::_UNKNOWN_MAP_UUID if no map is known to be identified by mapUUID
    /// * else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getMapRequest(
        const std::string & accessToken,
        const std::string & mapUUID,
        SRef<SolAR::datastructure::Map> & mapDatastructure,
        const SolAR::api::service::GetMapRequestOption & keyframeImagesOption = SolAR::api::service::GetMapRequestOption::WITH_KEYFRAME_IMAGES) const = 0;

    /// @brief Request to update the datastructure of a specific map
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] mapUUID UUID of the map to use
    /// @param[in] mapDatastructure the input map datastructure
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the data are ready to be processed
    /// * FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available
    /// * FrameworkReturnCode::_AUTHENT_SERVICE_UNAVAILABLE if authentication server is unavailable
    /// * FrameworkReturnCode::_AUTHENT_REQUEST_FAILURE if the request to the authentication server failed
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * FrameworkReturnCode::_AUTHENT_RESOURCE_NOT_FOUND if the requested resource was not found on the authentication server
    /// * else FrameworkReturnCode::_ERROR_
    [[grpc::client_sendSize("-1")]] virtual FrameworkReturnCode setMapRequest(
                                            const std::string & accessToken,
                                            const std::string & mapUUID,
                                            const SRef<SolAR::datastructure::Map> mapDatastructure) = 0;

    /// @brief Request the point cloud of a specific map
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] mapUUID UUID of the map to use
    /// @param[out] pointCloud the output point cloud
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the point cloud is available
    /// * FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available
    /// * FrameworkReturnCode::_AUTHENT_SERVICE_UNAVAILABLE if authentication server is unavailable
    /// * FrameworkReturnCode::_AUTHENT_REQUEST_FAILURE if the request to the authentication server failed
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * FrameworkReturnCode::_AUTHENT_RESOURCE_NOT_FOUND if the requested resource was not found on the authentication server
    /// * else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getPointCloudRequest(
                                            const std::string & accessToken,
                                            const std::string & mapUUID,
                                            SRef<SolAR::datastructure::PointCloud> & pointCloud) const = 0;

    /// @brief Request for information on a specific map
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
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
    virtual FrameworkReturnCode getMapInfo(const std::string & accessToken,
                                           const std::string & mapUUID,
                                           std::string & version,
                                           datastructure::GlobalDescriptorType & globalDescriptorType
                                           datastructure::DescriptorType & descriptorType,
                                           uint32_t & dataSize,
                                           bool & areImageSaved) const = 0;


    /// @brief Request for a map processing giving the type of process to apply (asynchronous)
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] mapUUID the UUID of the map to process
    /// @param[in] resultMapUUID the UUID of the new map resulting from the processing
    /// @param[in] processingType the type of process to apply on the map
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if processing is able to proceed
    /// * FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available
    /// * FrameworkReturnCode::_AUTHENT_SERVICE_UNAVAILABLE if authentication server is unavailable
    /// * FrameworkReturnCode::_AUTHENT_REQUEST_FAILURE if the request to the authentication server failed
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * FrameworkReturnCode::_AUTHENT_RESOURCE_NOT_FOUND if the requested resource was not found on the authentication server
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode requestMapProcessing(const std::string & accessToken,
                                                     const std::string & mapUUID,
                                                     const std::string & resultMapUUID,
                                                     const MapProcessingType processingType) = 0;

    /// @brief Get status and progress percentage concerning a map processing in progress
    /// @brief If status = COMPLETED then give the map UUID of the new resulting map
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] resultMapUUID the UUID of the map resulting from the processing
    /// @param[out] status the current map processing status
    /// @param[out] progress the current progress percentage (valid value should be between 0 and 1)
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the status and progress are available
    /// * FrameworkReturnCode::_NOT_FOUND if data is not available
    /// * FrameworkReturnCode::_AUTHENT_SERVICE_UNAVAILABLE if authentication server is unavailable
    /// * FrameworkReturnCode::_AUTHENT_REQUEST_FAILURE if the request to the authentication server failed
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * FrameworkReturnCode::_AUTHENT_RESOURCE_NOT_FOUND if the requested resource was not found on the authentication server
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getMapProcessingStatus(const std::string & accessToken,
                                                       const std::string & resultMapUUID,
                                                       MapProcessingStatus & status,
                                                       float & progress) const = 0;

    /// @brief Provide the current data from a map processing
    /// @brief (resulting from all map processing since the start of the pipeline)
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] resultMapUUID the UUID of the map resulting from the processing
    /// @param[out] pointCloud pipeline current point cloud
    /// @param[out] keyframePoses pipeline current keyframe poses
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if data is available
    /// * FrameworkReturnCode::_NOT_FOUND if data is not available
    /// * FrameworkReturnCode::_AUTHENT_SERVICE_UNAVAILABLE if authentication server is unavailable
    /// * FrameworkReturnCode::_AUTHENT_REQUEST_FAILURE if the request to the authentication server failed
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * FrameworkReturnCode::_AUTHENT_RESOURCE_NOT_FOUND if the requested resource was not found on the authentication server
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getMapProcessingData(const std::string & accessToken,
                                                     const std::string & resultMapUUID,
                                                     std::vector<SRef<SolAR::datastructure::CloudPoint>> & pointCloud,
                                                     std::vector<SolAR::datastructure::Transform3Df> & keyframePoses) const = 0;

protected:
    /// @brief Mode to use for the pipeline processing (Relocalization and Mapping by default)
    PipelineMode m_PipelineMode = PipelineMode::RELOCALIZATION_AND_MAPPING;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::service::IFrontEnd,
                             "58389ff0-5695-11ec-bf63-0242ac130002",
                             "IFrontEnd",
                             "The interface to define a Front End for services")

#endif // SOLAR_FRONTEND_H
