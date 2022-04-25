/**
 * @copyright Copyright (c) 2021 B-com http://www.b-com.com/
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

#ifndef SOLAR_ASYNCRELOCALIZATIONPIPELINE_H
#define SOLAR_ASYNCRELOCALIZATIONPIPELINE_H


#include "api/pipeline/IPipeline.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Image.h"
#include "xpcf/core/helpers.h"


namespace SolAR {
namespace api {
namespace pipeline {

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
    RELOCALIZATION_AND_MAPPING = 0,  // Relocalization and mapping
    RELOCALIZATION_ONLY = 1          // Only relocalization
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
 * @class IAsyncRelocalizationPipeline
 * @brief <B>Defines an asynchronous relocalization pipeline.</B>
 * <TT>UUID: 58389ff0-5695-11ec-bf63-0242ac130002</TT>
 *
 * This class provides the interface to define an asynchronous relocalization processing pipeline.
 */

class [[xpcf::clientUUID("91a569da-5695-11ec-bf63-0242ac130002")]] [[xpcf::serverUUID("95913e8e-5695-11ec-bf63-0242ac130002")]] IAsyncRelocalizationPipeline :
    virtual public IPipeline {
public:
    /// @brief IAsyncRelocalizationPipeline default constructor
    IAsyncRelocalizationPipeline() = default;

    /// @brief IAsyncRelocalizationPipeline default destructor
    virtual ~IAsyncRelocalizationPipeline() = default;

    using IPipeline::init;

    /// @brief Init the pipeline and specify the mode for the pipeline processing
    /// @param[in] pipelineMode: mode to use for pipeline processing
    /// @return FrameworkReturnCode::_SUCCESS if the mode is correctly initialized, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode init(PipelineMode pipelineMode) = 0;

    /// @brief Return the current mode used for the pipeline processing
    /// @return current mode
    PipelineMode getProcessingMode() const {
        return m_PipelineMode;
    }

    /// @brief Set the camera parameters
    /// @param[in] cameraParams the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCameraParameters(const SolAR::datastructure::CameraParameters & cameraParams) = 0;

    /// @brief Set the rectification parameters (use for stereo camera)
    /// @param[in] rectCam1 the rectification parameters of the first camera
    /// @param[in] rectCam2 the rectification parameters of the second camera
    /// @return FrameworkReturnCode::_SUCCESS if the rectification parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setRectificationParameters(const SolAR::datastructure::RectificationParameters & rectCam1,
                                                           const SolAR::datastructure::RectificationParameters & rectCam2) = 0;

    /// @brief Get the camera parameters
    /// @param[out] cameraParams the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly returned, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCameraParameters(SolAR::datastructure::CameraParameters & cameraParams) const = 0;

    /// @brief Request the asynchronous relocalization pipeline to process a new image to calculate
    /// the corresponding 3D transformation to the SolAR coordinates system
    /// @param[in] images the images to process
    /// @param[in] poses the poses associated to images in the client coordinates system
    /// @param[in] timestamp the timestamp of the image
    /// @param[out] transform3DStatus the status of the current 3D transformation matrix
    /// @param[out] transform3D the current 3D transformation matrix (if available)
    /// @param[out] confidence the confidence score of the 3D transformation matrix
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode relocalizeProcessRequest(const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                                         const std::vector<SolAR::datastructure::Transform3Df> & poses,
                                                         const std::chrono::system_clock::time_point & timestamp,
                                                         TransformStatus & transform3DStatus,
                                                         SolAR::datastructure::Transform3Df & transform3D,
                                                         float_t & confidence) = 0;

    /// @brief Request the asynchronous relocalization pipeline to get the 3D transform offset
    /// between the device coordinate system and the SolAR coordinate system
    /// @param[out] transform3DStatus the status of the current 3D transformation matrix
    /// @param[out] transform3D the current 3D transformation matrix (if available)
    /// @param[out] confidence the confidence score of the 3D transformation matrix
    /// @return FrameworkReturnCode::_SUCCESS if the 3D transform is available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode get3DTransformRequest(TransformStatus & transform3DStatus,
                                                      SolAR::datastructure::Transform3Df & transform3D,
                                                      float_t & confidence) = 0;

    /// @brief Return the last pose processed by the pipeline
    /// @param[out] pose the last pose if available
    /// @param[in] poseType the type of the requested pose
    ///            - in the SolAR coordinate system (by default)
    ///            - in the device coordinate system
    /// @return FrameworkReturnCode::_SUCCESS if the last pose is available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getLastPose(SolAR::datastructure::Transform3Df & pose,
                                            const PoseType poseType = SOLAR_POSE) const = 0;

protected:
    /// @brief Mode to use for the pipeline processing (Relocalization and Mapping by default)
    PipelineMode m_PipelineMode = RELOCALIZATION_AND_MAPPING;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IAsyncRelocalizationPipeline,
                             "58389ff0-5695-11ec-bf63-0242ac130002",
                             "IAsyncRelocalizationPipeline",
                             "The interface to define an asynchronous relocalization processing pipeline")

#endif // SOLAR_ASYNCRELOCALIZATIONPIPELINE_H
