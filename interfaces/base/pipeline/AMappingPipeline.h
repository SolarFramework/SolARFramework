/**
 * @copyright Copyright (c) 2017 B-com http://www.b-com.com/
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

#ifndef SOLAR_AMAPPINGPIPELINE_H
#define SOLAR_AMAPPINGPIPELINE_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "core/SolARFrameworkDefinitions.h"
#include "xpcf/component/ConfigurableBase.h"
#include "api/pipeline/IMappingPipeline.h"

namespace SolAR {
namespace base {
namespace pipeline {

class XPCF_IGNORE SOLARFRAMEWORK_API AMappingPipeline : public org::bcom::xpcf::ConfigurableBase,
                                            virtual public SolAR::api::pipeline::IMappingPipeline {
public:
    /// @brief AMappingPipeline constructor
    AMappingPipeline(std::map<std::string,std::string> componentInfosMap);

    virtual ~AMappingPipeline() override = default;

    /// @brief Set the camera parameters
    /// @param[in] cameraParams: the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCameraParameters(const SolAR::datastructure::CameraParameters & cameraParams) override
    { return FrameworkReturnCode::_NOT_IMPLEMENTED; }

    /// @brief Set the rectification parameters (use for stereo camera)
    /// @param[in] rectCam1 the rectification parameters of the first camera
    /// @param[in] rectCam2 the rectification parameters of the second camera
    /// @return FrameworkReturnCode::_SUCCESS if the rectification parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setRectificationParameters(const SolAR::datastructure::RectificationParameters & rectCam1,
                                                           const SolAR::datastructure::RectificationParameters & rectCam2) override
    { return FrameworkReturnCode::_NOT_IMPLEMENTED; }

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
                                                      SolAR::api::pipeline::MappingStatus & status) override
    { return FrameworkReturnCode::_NOT_IMPLEMENTED; }

    /// @brief Request to the mapping pipeline to process a new image/pose
    /// @param[in] images the input images to process
    /// @param[in] poses the input poses in the world coordinate system
    /// @param[out] status the current status of the mapping pipeline
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode mappingProcessRequest(const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                                      const std::vector<SolAR::datastructure::Transform3Df> & poses,
                                                      SolAR::api::pipeline::MappingStatus & status) override;

    /// @brief Request to the mapping pipeline to process a new image/pose
    /// @param[in] images the input images to process
    /// @param[in] poses the input poses in the world coordinate system
    /// @param[out] updatedTransform the refined transformation by a loop closure detection
    /// @param[out] status the current status of the mapping pipeline
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode mappingProcessRequest(const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                                      const std::vector<SolAR::datastructure::Transform3Df> & poses,
                                                      SolAR::datastructure::Transform3Df & updatedTransform,
                                                      SolAR::api::pipeline::MappingStatus & status) override;

    /// @brief Provide the current data from the mapping pipeline context for visualization
    /// (resulting from all mapping processing since the start of the pipeline)
    /// @param[out] outputPointClouds: pipeline current point clouds
    /// @param[out] keyframePoses: pipeline current keyframe poses
    /// @return FrameworkReturnCode::_SUCCESS if data are available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getDataForVisualization(std::vector<SRef<SolAR::datastructure::CloudPoint>> & outputPointClouds,
                                                        std::vector<SolAR::datastructure::Transform3Df> & keyframePoses) const override
    { return FrameworkReturnCode::_NOT_IMPLEMENTED; }
};
}
}
}  // end of namespace SolAR


#endif // SOLAR_AMAPPINGPIPELINE_H
