/**
 * @copyright Copyright (c) 2020 B-com http://www.b-com.com/
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

#ifndef SOLAR_MAPPINGPIPELINE_H
#define SOLAR_MAPPINGPIPELINE_H


#include "api/pipeline/IPipeline.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/CloudPoint.h"
#include "datastructure/Keypoint.h"
#include "xpcf/core/helpers.h"


namespace SolAR {
namespace api {
namespace pipeline {

///
/// @typedef MappingStatus
/// @brief <B>Indicate the status of the mapping pipeline</B>
///
typedef enum {
    BOOTSTRAP = 0,      // bootstrapping to initialize the map
    MAPPING = 1,        // mapping
    TRACKING_LOST = 2,  // tracking lost need to relocalization
    LOOP_CLOSURE = 3    // loop closure optimization
} MappingStatus;

/**
 * @class IMappingPipeline
 * @brief <B>Defines a mapping pipeline.</B>
 * <TT>UUID: 2dc3cd33-5a11-4748-94a3-e7ab40462097</TT>
 *
 * This class provides the interface to define a mapping processing pipeline.
 */

class [[xpcf::clientUUID("110a089c-0bb1-488e-b24b-c1b96bc9df3b")]] [[xpcf::serverUUID("aced265d-832c-44e3-9356-dab531fa153a")]]
#ifndef DOXYGEN_SHOULD_SKIP_THIS // Doxygen does not support custom DSL
    XPCF_GRPC_CLIENT_RECV_SIZE("-1")
#endif
    IMappingPipeline : virtual public IPipeline {
public:
    /// @brief IMappingPipeline default constructor
    IMappingPipeline() = default;

    /// @brief IMappingPipeline default destructor
    virtual ~IMappingPipeline() = default;

    /// @brief Method used to test if the pipeline is ready
    /// @return FrameworkReturnCode::_SUCCESS if the init succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode isAlive() {return FrameworkReturnCode::_SUCCESS;}

    /// @brief Set the camera parameters
    /// @param[in] cameraParams the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCameraParameters(const SolAR::datastructure::CameraParameters & cameraParams) = 0;

	/// @brief Set the camera parameters (use for stereo camera)
    /// @param[in] cameraParams1 the camera parameters of the first camera
    /// @param[in] cameraParams2 the camera parameters of the second camera
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
	virtual FrameworkReturnCode setCameraParameters(const SolAR::datastructure::CameraParameters & cameraParams1,
													const SolAR::datastructure::CameraParameters & cameraParams2) = 0;

    /// @brief Set the rectification parameters (use for stereo camera)
    /// @param[in] rectCam1 the rectification parameters of the first camera
    /// @param[in] rectCam2 the rectification parameters of the second camera
    /// @return FrameworkReturnCode::_SUCCESS if the rectification parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setRectificationParameters(const SolAR::datastructure::RectificationParameters & rectCam1,
                                                           const SolAR::datastructure::RectificationParameters & rectCam2) = 0;

    /// @brief Request to the mapping pipeline to process a new image/pose
    /// @param[in] images the input images to process
    /// @param[in] poses the input poses in the device coordinate system
    /// @param[in] transform the transformation matrix from the device coordinate system to the world coordinate system
    /// @param[out] updatedTransform the refined transformation by a loop closure detection
    /// @param[out] status the current status of the mapping pipeline
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode mappingProcessRequest(const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                                      const std::vector<SolAR::datastructure::Transform3Df> & poses,
                                                      const SolAR::datastructure::Transform3Df & transform,
                                                      SolAR::datastructure::Transform3Df & updatedTransform,
                                                      MappingStatus & status) = 0;

    /// @brief Request to the mapping pipeline to process a new image/pose
    /// @param[in] images the input images to process
    /// @param[in] poses the input poses in the world coordinate system
    /// @param[out] status the current status of the mapping pipeline
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode mappingProcessRequest(const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                                      const std::vector<SolAR::datastructure::Transform3Df> & poses,
                                                      MappingStatus & status) = 0;

    /// @brief Request to the mapping pipeline to process a new image/pose
    /// @param[in] images the input images to process
    /// @param[in] poses the input poses in the world coordinate system
    /// @param[out] updatedTransform the refined transformation by a loop closure detection
    /// @param[out] status the current status of the mapping pipeline
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode mappingProcessRequest(const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                                      const std::vector<SolAR::datastructure::Transform3Df> & poses,
                                                      SolAR::datastructure::Transform3Df & updatedTransform,
                                                      MappingStatus & status) = 0;

    /// @brief Provide the current data from the mapping pipeline context for visualization
    /// (resulting from all mapping processing since the start of the pipeline)
    /// @param[out] outputPointClouds: pipeline current point clouds
    /// @param[out] keyframePoses: pipeline current keyframe poses
    /// @return FrameworkReturnCode::_SUCCESS if data are available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getDataForVisualization(std::vector<SRef<SolAR::datastructure::CloudPoint>> & outputPointClouds,
                                                        std::vector<SolAR::datastructure::Transform3Df> & keyframePoses) const = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IMappingPipeline,
                             "2dc3cd33-5a11-4748-94a3-e7ab40462097",
                             "IMappingPipeline",
                             "The interface to define a mapping processing pipeline")

#endif // SOLAR_MAPPINGPIPELINE_H
