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

#ifndef SOLAR_POSEESTIMATIONPIPELINE_H
#define SOLAR_POSEESTIMATIONPIPELINE_H

#include "api/pipeline/IPipeline.h"
#include "datastructure/CameraDefinitions.h"
#include "api/sink/ISinkReturnCode.h"
#include "api/source/ISourceReturnCode.h"
#include "datastructure/Image.h"


namespace SolAR {
namespace api {
namespace pipeline {

/**
 * @class IPoseEstimationPipeline
 * @brief <B>Defines a pose estimation pipeline.</B>
 * <TT>UUID: b5a6225e-6a91-4050-b298-886f4c17d9d2</TT>
 *
 * This class provides the interface to define a video see-through pipeline.
 */

class IPoseEstimationPipeline : virtual public IPipeline {
public:
    /// @brief IPoseEstimationPipeline default constructor
    IPoseEstimationPipeline() = default;

    /// @brief IPoseEstimationPipeline default destructor
    virtual ~IPoseEstimationPipeline() = default;

    /// @brief Starts the pipeline and provides a texture buffer which will be updated when required.
    /// @param[in] textureHandle a pointer to the texture buffer which will be updated at each call of the update method.
    virtual FrameworkReturnCode start(void* imageDataBuffer) = 0;

    /// @brief Provide the camera parameters
    /// @return the camera parameters (resolution and focal)
    virtual datastructure::CameraParameters getCameraParameters() = 0;

    /// @brief update the pipeline
    /// Get the new pose and update the texture buffer with the image that has to be displayed
    virtual sink::SinkReturnCode update(datastructure::Transform3Df & pose) = 0;

    /// @brief load a generic texture buffer.
    /// @param[in] textureHandle a pointer to the texture buffer which will be updated at each call of the update method.    
    /// @param[in] width textureHandle buffer width.
    /// @param[in] width textureHandle buffer height.
    /// @return FrameworkReturnCode::_SUCCESS if the loading succeed, else FrameworkReturnCode::_ERROR_   
    virtual source::SourceReturnCode loadSourceImage(void* sourceTextureHandle, int width, int height) = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IPoseEstimationPipeline,
                             "b5a6225e-6a91-4050-b298-886f4c17d9d2",
                             "IPoseEstimationPipeline",
                             "The interface to define a video see-throuh pipeline")

#endif // SOLAR_POSEESTIMATIONPIPELINE_H
