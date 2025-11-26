/**
 * @copyright Copyright (c) 2025 B-com http://www.b-com.com/
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

#ifndef SOLAR_CLIENTCONTEXTMANAGER_H
#define SOLAR_CLIENTCONTEXTMANAGER_H


#include "api/pipeline/IMappingPipeline.h"
#include "api/pipeline/IImageSegmentationPipeline.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/DetectedObject.h"
#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/api/IComponentManager.h>
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace service {

/**
 * @typedef DeviceType
 * @brief <B>Define the types of all devices.</B>
 */
enum class DeviceType {
    OTHER_DEVICE = 0,
    HOLOLENS2_HEADSET = 1,
    LYNX_HEADSET = 2,
    ANDROID_DEVICE = 3,
    IOS_DEVICE = 4
};

/// @brief Return the text definition (string) of a DeviceType object
/// @param[in] deviceType the device type
/// @return the text definition (string)
static std::string toString(const DeviceType deviceType)
{
    std::string textDefinition = "";

    switch (deviceType) {
        case DeviceType::OTHER_DEVICE:
            textDefinition = "OTHER_DEVICE";
            break;
        case DeviceType::HOLOLENS2_HEADSET:
            textDefinition = "HOLOLENS2_HEADSET";
            break;
        case DeviceType::LYNX_HEADSET:
            textDefinition = "LYNX_HEADSET";
            break;
        case DeviceType::ANDROID_DEVICE:
            textDefinition = "ANDROID_DEVICE";
            break;
        case DeviceType::IOS_DEVICE:
            textDefinition = "IOS_DEVICE";
            break;
        default:
            textDefinition = "Unknown value";
            break;
    }

    return textDefinition;
}

/**
 * @struct DeviceInfo
 * @brief <B>Define any device that can request the Front End.</B>
 */
struct DeviceInfo
{
    std::string deviceUUID;         // Unique ID given by the device
    DeviceType deviceType;          // Type of the device
    std::string deviceModel;        // Model reference given by the device
    std::string deviceDescription;  // Additional device description

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & deviceUUID;
        ar & deviceType;
        ar & deviceModel;
        ar & deviceDescription;
    }
};

///
/// @typedef TransformStatus
/// @brief <B>Indicate the status of the 3D transformation matrix</B>
///
enum class TransformStatus {
    NO_3DTRANSFORM = 0,       // No 3D transform available
    PREVIOUS_3DTRANSFORM = 1, // 3D transform previously given by the relocalization service
    NEW_3DTRANSFORM = 2       // New 3D transform given by the relocalization service
};

/// @brief Return the text definition (string) of a TransformStatus object
/// @param[in] transformStatus the transformation status
/// @return the text definition (string)
static std::string toString(const TransformStatus transformStatus)
{
    std::string textDefinition = "";

    switch (transformStatus) {
        case TransformStatus::NO_3DTRANSFORM:
            textDefinition = "NO_3DTRANSFORM";
            break;
        case TransformStatus::PREVIOUS_3DTRANSFORM:
            textDefinition = "PREVIOUS_3DTRANSFORM";
            break;
        case TransformStatus::NEW_3DTRANSFORM:
            textDefinition = "NEW_3DTRANSFORM";
            break;
        default:
            textDefinition = "Unknown value";
            break;
    }

    return textDefinition;
}

///
/// @typedef PipelineMode
/// @brief <B>Modes available for the pipeline processing</B>
///
enum class PipelineMode {
    RELOCALIZATION_AND_MAPPING = 0,         // Relocalization and mapping
    RELOCALIZATION_AND_STEREO_MAPPING = 1,  // Relocalization and stereo mapping
    RELOCALIZATION_ONLY = 2,                // Only relocalization
    IMAGE_SEGMENTATION = 3                  // Image segmentation
};

/// @brief Return the text definition (string) of a PipelineMode object
/// @param[in] pipelineMode the pipeline mode
/// @return the text definition (string)
static std::string toString(const PipelineMode pipelineMode)
{
    std::string textDefinition = "";

    switch (pipelineMode) {
        case PipelineMode::RELOCALIZATION_AND_MAPPING:
            textDefinition = "RELOCALIZATION_AND_MAPPING";
            break;
        case PipelineMode::RELOCALIZATION_AND_STEREO_MAPPING:
            textDefinition = "RELOCALIZATION_AND_STEREO_MAPPING";
            break;
        case PipelineMode::RELOCALIZATION_ONLY:
            textDefinition = "RELOCALIZATION_ONLY";
            break;
        case PipelineMode::IMAGE_SEGMENTATION:
            textDefinition = "IMAGE_SEGMENTATION";
            break;
        default:
            textDefinition = "Unknown value";
            break;
    }

    return textDefinition;
}

///
/// @typedef PoseType
/// @brief <B>Type of pose according to a specific coordinate system</B>
///
enum class PoseType {
    SOLAR_POSE = 0,  // Pose in the SolAR coordinate system
    DEVICE_POSE = 1  // Pose in the device coordinate system
};

/// @brief Return the text definition (string) of a PoseType object
/// @param[in] poseType the pose type
/// @return the text definition (string)
static std::string toString(const PoseType poseType)
{
    std::string textDefinition = "";

    switch (poseType) {
        case PoseType::SOLAR_POSE:
            textDefinition = "SOLAR_POSE";
            break;
        case PoseType::DEVICE_POSE:
            textDefinition = "DEVICE_POSE";
            break;
        default:
            textDefinition = "Unknown value";
            break;
    }

    return textDefinition;
}

/**
 * @class IClientContextManager
 * @brief <B>Defines the client context manager interface for services.</B>
 * <TT>UUID: d43f5a3b-f66b-4f27-a3b6-cb009a166994</TT>
 *
 * This class provides the interface to define a Client Context Manager for services.
 */
class XPCF_CLIENTUUID("b675a1c5-078e-4c7a-82f7-d75a7d3d6dbe") XPCF_SERVERUUID("4303e7b0-66d6-4b35-9988-1edda751ecc6")
    XPCF_GRPC_CLIENT_RECV_SIZE("-1") XPCF_GRPC_CLIENT_SEND_SIZE("-1")
    IClientContextManager : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IClientContextManager default constructor
    IClientContextManager() = default;

    /// @brief IClientContextManager default destructor
    virtual ~IClientContextManager() = default;

    /// @brief Register a new client, set the map to use (for mapping/relocalization)
    /// @brief and return its UUID to use for future requests
    /// @param[in] deviceInfo information on the client's device
    /// @param[in] worldElementUUID the UUID of the world element to use for the World Graph request
    /// @param[out] clientUUID the UUID for this new client
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the client is registered with its UUID
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode registerClient(const DeviceInfo & deviceInfo,
                                               const std::string & worldElementUUID,
                                               std::string & clientUUID) = 0;

    /// @brief Unregister a client using its UUID
    /// @param[in] clientUUID the UUID of the client to unregister
    /// @return FrameworkReturnCode::_SUCCESS if the client is unregistered, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode unregisterClient(const std::string & clientUUID) = 0;

    /// @brief Return all current clients UUID
    /// @param[out] clientUUIDList the list of UUID of all clients currently registered
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the method succeeds
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getAllClientsUUID(std::vector<std::string> & clientUUIDList) const = 0;

    /// @brief Return the device information for the given client UUID
    /// @param[in] clientUUID UUID of the client
    /// @param[out] deviceInfo information on the client's device
    /// @return FrameworkReturnCode::_SUCCESS if the method succeeds, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getDeviceInfo(const std::string & clientUUID,
                                              DeviceInfo & deviceInfo) const = 0;

    /// @brief Initialization of the service
    /// @param[in] clientUUID UUID of the client
    /// @return FrameworkReturnCode::_SUCCESS if the init succeed, FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode init(const std::string & clientUUID) = 0;

    /// @brief Init the service and specify the mode for the pipeline processing
    /// @param[in] clientUUID UUID of the client
    /// @param[in] pipelineMode mode to use for pipeline processing
    /// @return FrameworkReturnCode::_SUCCESS if the mode is correctly initialized, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode init(const std::string & clientUUID,
                                     PipelineMode pipelineMode) = 0;

    /// @brief Start the service
    /// @param[in] clientUUID UUID of the client
    /// @return FrameworkReturnCode::_SUCCESS if the stard succeed, FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode start(const std::string & clientUUID) = 0;

    /// @brief Stop the service.
    /// @param[in] clientUUID UUID of the client
    /// @return FrameworkReturnCode::_SUCCESS if the stop succeed, FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode stop(const std::string & clientUUID) = 0;

    /// @brief Return the current mode used for the pipeline processing
    /// @param[in] clientUUID UUID of the client
    /// @param[out] pipelineMode the current pipeline mode
    /// @return FrameworkReturnCode::_SUCCESS if the method succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getProcessingMode(const std::string & clientUUID,
                                                  PipelineMode & pipelineMode) const = 0;

    /// @brief Set the camera parameters
    /// @param[in] clientUUID UUID of the client
    /// @param[in] cameraParams the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCameraParameters(const std::string & clientUUID,
                                                    const SolAR::datastructure::CameraParameters & cameraParams) = 0;

    /// @brief Set the camera parameters (use for stereo camera)
    /// @param[in] clientUUID UUID of the client
    /// @param[in] cameraParams1 the camera parameters of the first camera
    /// @param[in] cameraParams2 the camera parameters of the second camera
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCameraParameters(const std::string & clientUUID,
                                                    const SolAR::datastructure::CameraParameters & cameraParams1,
                                                    const SolAR::datastructure::CameraParameters & cameraParams2) = 0;

    /// @brief Set the rectification parameters (use for stereo camera)
    /// @param[in] clientUUID UUID of the client
    /// @param[in] rectCam1 the rectification parameters of the first camera
    /// @param[in] rectCam2 the rectification parameters of the second camera
    /// @return FrameworkReturnCode::_SUCCESS if the rectification parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setRectificationParameters(const std::string & clientUUID,
                                                           const SolAR::datastructure::RectificationParameters & rectCam1,
                                                           const SolAR::datastructure::RectificationParameters & rectCam2) = 0;

    /// @brief Get the camera parameters
    /// @param[in] clientUUID UUID of the client
    /// @param[out] cameraParams the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly returned, FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCameraParameters(const std::string & clientUUID,
                                                    SolAR::datastructure::CameraParameters & cameraParams) const = 0;

    /// @brief Request the front end to process a new image to calculate
    /// @brief the corresponding 3D transformation to the SolAR coordinates system
    /// @param[in] clientUUID UUID of the client
    /// @param[in] images the images to process
    /// @param[in] poses the poses associated to images in the client coordinates system
    /// @param[in] timestamp the timestamp of the image
    /// @param[out] transform3DStatus the status of the current 3D transformation matrix
    /// @param[out] transform3D the current 3D transformation matrix (if available)
    /// @param[out] confidence the confidence score of the 3D transformation matrix
    /// @param[out] mappingStatus the status of the current mapping processing
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    FrameworkReturnCode relocalizeProcessRequest(const std::string & clientUUID,
                                                 const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                                 const std::vector<SolAR::datastructure::Transform3Df> & poses,
                                                 const std::chrono::system_clock::time_point & timestamp,
                                                 TransformStatus & transform3DStatus,
                                                 SolAR::datastructure::Transform3Df & transform3D,
                                                 float_t & confidence,
                                                 SolAR::api::pipeline::MappingStatus & mappingStatus)
    {
        SolAR::datastructure::Transform3Df worldTransform(SolAR::datastructure::Maths::Matrix4f::Zero());
        std::vector<SolAR::datastructure::DetectedObject> detectedObjects;
        return relocalizeProcessRequest(clientUUID,
                                        images,
                                        poses,
                                        /* fixedPose = */ false,
                                        worldTransform,
                                        timestamp,
                                        transform3DStatus,
                                        transform3D,
                                        confidence,
                                        mappingStatus,
                                        detectedObjects);
    }

    /// @brief Request the front end to process a new image to calculate
    /// @brief the corresponding 3D transformation to the SolAR coordinates system
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
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode relocalizeProcessRequest(const std::string & clientUUID,
                                                         const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                                         const std::vector<SolAR::datastructure::Transform3Df> & poses,
                                                         bool fixedPose,
                                                         const SolAR::datastructure::Transform3Df & worldTransform,
                                                         const std::chrono::system_clock::time_point & timestamp,
                                                         TransformStatus & transform3DStatus,
                                                         SolAR::datastructure::Transform3Df & transform3D,
                                                         float_t & confidence,
                                                         SolAR::api::pipeline::MappingStatus & mappingStatus) = 0;

    /// @brief Request the front end to process a new image to calculate
    /// @brief the corresponding 3D transformation to the SolAR coordinates system
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
    /// @param[out] detectedObjects: list of objects detected in the last processed image
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode relocalizeProcessRequest(const std::string & clientUUID,
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


    /// @brief Request the front end to get the 3D transform offset
    /// @brief between the device coordinate system and the SolAR coordinate system
    /// @param[in] clientUUID UUID of the client
    /// @param[out] transform3DStatus the status of the current 3D transformation matrix
    /// @param[out] transform3D the current 3D transformation matrix (if available)
    /// @param[out] confidence the confidence score of the 3D transformation matrix
    /// @return FrameworkReturnCode::_SUCCESS if the 3D transform is available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode get3DTransformRequest(const std::string & clientUUID,
                                                      TransformStatus & transform3DStatus,
                                                      SolAR::datastructure::Transform3Df & transform3D,
                                                      float_t & confidence) = 0;

    /// @brief Provide the current data from the mapping service context
    /// @brief (resulting from all mapping processing since the start of the service)
    /// @param[in] clientUUID UUID of the client
    /// @param[out] outputPointClouds service current point clouds
    /// @param[out] keyframePoses service current keyframe poses
    /// @return FrameworkReturnCode::_SUCCESS if data are available, FrameworkReturnCode::_NO_SERVICE_AVAILABLE if a necessary service is not available else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getMappingDataRequest(
                                            const std::string & clientUUID,
                                            std::vector<SRef<SolAR::datastructure::CloudPoint>> & outputPointClouds,
                                            std::vector<SolAR::datastructure::Transform3Df> & keyframePoses) const = 0;

    /// @brief Return the last pose processed by the service
    /// @param[in] clientUUID UUID of the client
    /// @param[out] pose the last pose if available
    /// @param[in] poseType the type of the requested pose
    ///            - in the SolAR coordinate system (by default)
    ///            - in the device coordinate system
    /// @return FrameworkReturnCode::_SUCCESS if the last pose is available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getLastPose(const std::string & clientUUID,
                                            SolAR::datastructure::Transform3Df & pose,
                                            const PoseType poseType = PoseType::SOLAR_POSE) const = 0;

    /// @brief Return the map UUID used by a client specified by its UUID
    /// @param[in] clientUUID UUID of the client
    /// @param[out] mapUUID: UUID of the map used by the client
    /// @return FrameworkReturnCode::_SUCCESS if the method succeeds, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getClientMapUUID(const std::string & clientUUID,
                                                 std::string & mapUUID) const = 0;

    /// @brief Request for a segmentation processing for one input image
    /// @param[in] clientUUID UUID of the client
    /// @param[in] image pointer to image
    /// @return FrameworkReturnCode::_SUCCESS (segmentation succeeded) or FrameworkReturnCode::_ERROR_ (segmentation failed)
    virtual FrameworkReturnCode imageSegmentationProcessRequest(const std::string & clientUUID,
                                                                SRef<SolAR::datastructure::Image> image) = 0;

    /// @brief Request for a segmentation processing for a list of images
    /// @param[in] clientUUID UUID of the client
    /// @param[in] images list of pointers to images to be segmented
    /// @param[in] temporalConsistency flag indicating whether the images are temporally consistent (true) or not (false)
    /// @return FrameworkReturnCode::_SUCCESS (segmentation succeeded) or FrameworkReturnCode::_ERROR_ (segmentation failed)
    virtual FrameworkReturnCode imageSegmentationProcessRequest(const std::string & clientUUID,
                                                                const std::vector<SRef<SolAR::datastructure::Image>>& images,
                                                                bool temporalConsistency = false) = 0;

    /// @brief Get the status and the progress percentage of a current image segmentation processing
    /// @param[in] clientUUID UUID of the client
    /// @param[out] status the current image segmentation processing status
    /// @param[out] progress the current progress percentage (valid value should be between 0 and 1)
    /// @return FrameworkReturnCode::_SUCCESS if the status and progress are successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getImageSegmentationProcessStatus(const std::string & clientUUID,
                                                                  SolAR::api::pipeline::IImageSegmentationPipeline::Status & status,
                                                                  float & progress) const = 0;

    /// @brief Get the output masks resulting from an image segmentation processing
    /// @param[in] clientUUID UUID of the client
    /// @param[out] mask output mask collection
    /// @return FrameworkReturnCode::_SUCCESS (get output mask succeeded) or FrameworkReturnCode::_ERROR_ (get output mask failed)
    virtual FrameworkReturnCode getImageSegmentationProcessOutputMasks(const std::string & clientUUID,
                                                                       SRef<SolAR::datastructure::Mask2DCollection> & mask) const = 0;


protected:
    /// @brief Mode to use for the pipeline processing (Relocalization and Mapping by default)
    PipelineMode m_PipelineMode = PipelineMode::RELOCALIZATION_AND_MAPPING;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::service::IClientContextManager,
                             "d43f5a3b-f66b-4f27-a3b6-cb009a166994",
                             "IClientContextManager",
                             "The interface to define a Client Context Manager for services")

#endif // SOLAR_CLIENTCONTEXTMANAGER_H
