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

///
/// @typedef TransformStatus
/// @brief <B>Indicate the status of the 3D transformation matrix</B>
///
typedef enum {
    NO_3DTRANSFORM = 0,       // No 3D transform available
    PREVIOUS_3DTRANSFORM = 1, // 3D transform previously given by the relocalization service
    NEW_3DTRANSFORM = 2       // New 3D transform given by the relocalization service
} TransformStatus;

///
/// @typedef PipelineMode
/// @brief <B>Modes available for the pipeline processing</B>
///
typedef enum {
    RELOCALIZATION_AND_MAPPING = 0,         // Relocalization and mapping
    RELOCALIZATION_AND_STEREO_MAPPING = 1,  // Relocalization and stereo mapping
    RELOCALIZATION_ONLY = 2                 // Only relocalization
} PipelineMode;

///
/// @typedef PoseType
/// @brief <B>Type of pose according to a specific coordinate system</B>
///
typedef enum {
    SOLAR_POSE = 0,  // Pose in the SolAR coordinate system
    DEVICE_POSE = 1  // Pose in the device coordinate system
} PoseType;

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

    /// @brief Register a new client and return its UUID to use for future requests
    /// @param[out] the UUID for this new client
    /// @return FrameworkReturnCode::_SUCCESS if the client is registered with its UUID, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode registerClient(std::string & uuid) = 0;

    /// @brief Unregister a client using its UUID
    /// @param[in] the UUID of the client to unregister
    /// @return FrameworkReturnCode::_SUCCESS if the client is unregistered, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode unregisterClient(const std::string & uuid) = 0;

    /// @brief Return all current clients UUID
    /// @param[out] uuidList: the list of UUID of all clients currently registered
    /// @return FrameworkReturnCode::_SUCCESS if the method succeeds, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getAllClientsUUID(std::vector<std::string> & uuidList) const = 0;

    /// @brief Initialization of the service
    /// @param[in] uuid: UUID of the client
    /// @return FrameworkReturnCode::_SUCCESS if the init succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode init(const std::string & uuid) = 0;

    /// @brief Init the service and specify the mode for the pipeline processing
    /// @param[in] uuid: UUID of the client
    /// @param[in] pipelineMode: mode to use for pipeline processing
    /// @return FrameworkReturnCode::_SUCCESS if the mode is correctly initialized, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode init(const std::string & uuid, PipelineMode pipelineMode) = 0;

    /// @brief Start the service
    /// @param[in] uuid: UUID of the client
    /// @return FrameworkReturnCode::_SUCCESS if the stard succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode start(const std::string & uuid) = 0;

    /// @brief Stop the service.
    /// @param[in] uuid: UUID of the client
    /// @return FrameworkReturnCode::_SUCCESS if the stop succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode stop(const std::string & uuid) = 0;

    /// @brief Return the current mode used for the pipeline processing
    /// @param[in] uuid: UUID of the client
    /// @param[out] pipelineMode: the current pipeline mode
    /// @return FrameworkReturnCode::_SUCCESS if the method succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getProcessingMode(const std::string & uuid, PipelineMode & pipelineMode) const = 0;

    /// @brief Set the camera parameters
    /// @param[in] uuid: UUID of the client
    /// @param[in] cameraParams the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCameraParameters(const std::string & uuid,
                                                    const SolAR::datastructure::CameraParameters & cameraParams) = 0;

    /// @brief Set the camera parameters (use for stereo camera)
    /// @param[in] uuid: UUID of the client
    /// @param[in] cameraParams1 the camera parameters of the first camera
    /// @param[in] cameraParams2 the camera parameters of the second camera
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCameraParameters(const std::string & uuid,
                                                    const SolAR::datastructure::CameraParameters & cameraParams1,
                                                    const SolAR::datastructure::CameraParameters & cameraParams2) = 0;

    /// @brief Set the rectification parameters (use for stereo camera)
    /// @param[in] uuid: UUID of the client
    /// @param[in] rectCam1 the rectification parameters of the first camera
    /// @param[in] rectCam2 the rectification parameters of the second camera
    /// @return FrameworkReturnCode::_SUCCESS if the rectification parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setRectificationParameters(const std::string & uuid,
                                                           const SolAR::datastructure::RectificationParameters & rectCam1,
                                                           const SolAR::datastructure::RectificationParameters & rectCam2) = 0;

    /// @brief Get the camera parameters
    /// @param[in] uuid: UUID of the client
    /// @param[out] cameraParams the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly returned, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCameraParameters(const std::string & uuid,
                                                    SolAR::datastructure::CameraParameters & cameraParams) const = 0;

    /// @brief Request the front end to process a new image to calculate
    /// the corresponding 3D transformation to the SolAR coordinates system
    /// @param[in] uuid: UUID of the client
    /// @param[in] images the images to process
    /// @param[in] poses the poses associated to images in the client coordinates system
    /// @param[in] timestamp the timestamp of the image
    /// @param[out] transform3DStatus the status of the current 3D transformation matrix
    /// @param[out] transform3D the current 3D transformation matrix (if available)
    /// @param[out] confidence the confidence score of the 3D transformation matrix
    /// @param[out] mappingStatus the status of the current mapping processing
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    FrameworkReturnCode relocalizeProcessRequest(const std::string & uuid,
                                                 const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                                 const std::vector<SolAR::datastructure::Transform3Df> & poses,
                                                 const std::chrono::system_clock::time_point & timestamp,
                                                 TransformStatus & transform3DStatus,
                                                 SolAR::datastructure::Transform3Df & transform3D,
                                                 float_t & confidence,
                                                 SolAR::api::pipeline::MappingStatus & mappingStatus)
    {
        SolAR::datastructure::Transform3Df worldTransform(SolAR::datastructure::Maths::Matrix4f::Zero());
        return relocalizeProcessRequest(uuid,
                                        images,
                                        poses,
                                        /* fixedPose = */ false,
                                        worldTransform,
                                        timestamp,
                                        transform3DStatus,
                                        transform3D,
                                        confidence,
                                        mappingStatus);
    }

    /// @brief Request the front end to process a new image to calculate
    /// the corresponding 3D transformation to the SolAR coordinates system
    /// @param[in] uuid: UUID of the client
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
    virtual FrameworkReturnCode relocalizeProcessRequest(const std::string & uuid,
                                                         const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                                         const std::vector<SolAR::datastructure::Transform3Df> & poses,
                                                         bool fixedPose,
                                                         const SolAR::datastructure::Transform3Df & worldTransform,
                                                         const std::chrono::system_clock::time_point & timestamp,
                                                         TransformStatus & transform3DStatus,
                                                         SolAR::datastructure::Transform3Df & transform3D,
                                                         float_t & confidence,
                                                         SolAR::api::pipeline::MappingStatus & mappingStatus) = 0;

    /// @brief Request the front end to get the 3D transform offset
    /// between the device coordinate system and the SolAR coordinate system
    /// @param[in] uuid: UUID of the client
    /// @param[out] transform3DStatus the status of the current 3D transformation matrix
    /// @param[out] transform3D the current 3D transformation matrix (if available)
    /// @param[out] confidence the confidence score of the 3D transformation matrix
    /// @return FrameworkReturnCode::_SUCCESS if the 3D transform is available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode get3DTransformRequest(const std::string & uuid,
                                                      TransformStatus & transform3DStatus,
                                                      SolAR::datastructure::Transform3Df & transform3D,
                                                      float_t & confidence) = 0;

    /// @brief Provide the current data from the mapping service context
    /// (resulting from all mapping processing since the start of the service)
    /// @param[in] uuid: UUID of the client
    /// @param[out] outputPointClouds: service current point clouds
    /// @param[out] keyframePoses: service current keyframe poses
    /// @return FrameworkReturnCode::_SUCCESS if data are available, else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getMappingDataRequest(
        const std::string & uuid,
        std::vector<SRef<SolAR::datastructure::CloudPoint>> & outputPointClouds,
        std::vector<SolAR::datastructure::Transform3Df> & keyframePoses) const = 0;

    /// @brief Return the last pose processed by the service
    /// @param[in] uuid: UUID of the client
    /// @param[out] pose the last pose if available
    /// @param[in] poseType the type of the requested pose
    ///            - in the SolAR coordinate system (by default)
    ///            - in the device coordinate system
    /// @return FrameworkReturnCode::_SUCCESS if the last pose is available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getLastPose(const std::string & uuid,
                                            SolAR::datastructure::Transform3Df & pose,
                                            const PoseType poseType = SOLAR_POSE) const = 0;

    /// @brief Request the global map stored by the map update service
    /// @param[out] map: the output global map
    /// @return FrameworkReturnCode::_SUCCESS if the global map is available, else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getMapRequest(
        SRef<SolAR::datastructure::Map> & map) const = 0;

    /// @brief Request to the map update service to update the global map from a local map
    /// @param[in] map: the input local map to process
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    [[grpc::client_sendSize("-1")]] virtual FrameworkReturnCode setMapRequest(
        const SRef<SolAR::datastructure::Map> map) = 0;

    /// @brief Reset the map stored by the map update service
    /// @return FrameworkReturnCode::_SUCCESS if the map is correctly reset, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode resetMap() const = 0;

    /// @brief Request the point cloud of the global map stored by the map update service
    /// @param[out] pointCloud: the output point cloud
    /// @return FrameworkReturnCode::_SUCCESS if the point cloud is available, else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getPointCloudRequest(
        SRef<SolAR::datastructure::PointCloud> & pointCloud) const = 0;

protected:
    /// @brief Mode to use for the pipeline processing (Relocalization and Mapping by default)
    PipelineMode m_PipelineMode = RELOCALIZATION_AND_MAPPING;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::service::IFrontEnd,
                             "58389ff0-5695-11ec-bf63-0242ac130002",
                             "IFrontEnd",
                             "The interface to define a Front End for services")

#endif // SOLAR_FRONTEND_H
