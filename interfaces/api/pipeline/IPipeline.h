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

#ifndef SOLAR_PIPELINE_H
#define SOLAR_PIPELINE_H

#include "datastructure/CameraDefinitions.h"
#include "api/sink/ISinkReturnCode.h"
#include "api/source/ISourceReturnCode.h"
#include "core/Messages.h"
#include "xpcf/api/IComponentIntrospect.h"
#include "xpcf/api/IComponentManager.h"
#include "datastructure/Image.h"


namespace xpcf  = org::bcom::xpcf;
namespace SolAR {
namespace api {
using namespace sink;
using namespace source;
using namespace datastructure;
namespace pipeline {

/**
 * @class IPipeline
 * @brief <B>Defines a pose estimation pipeline.</B>
 * <TT>UUID: b5a6225e-6a91-4050-b298-886f4c17d9d2</TT>
 *
 * This class provides the interface to define a video see-through pipeline.
 */

class [[xpcf::ignore]] IPipeline : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IPipeline default constructor
    IPipeline() = default;

    /// @brief IPipeline default destructor
    virtual ~IPipeline() = default;

    /// @brief Initialization of the pipeline
    /// Initialize the pipeline by providing a reference to the component manager loaded by the PipelineManager.
    /// @param[in] componentManager a shared reference to the component manager which has loaded the components and configuration in the pipleine manager
    virtual FrameworkReturnCode init(SRef<xpcf::IComponentManager> componentManager) = 0;

    /// @brief Provide the camera parameters
    /// @return the camera parameters (its resolution and its focal)
    virtual CameraParameters getCameraParameters() = 0;

    /// @brief Starts the pipeline and provides a texture buffer which will be updated when required.
    /// @param[in] textureHandle a pointer to the texture buffer which will be updated at each call of the update method.
    ///     /// @return FrameworkReturnCode::_SUCCESS if the stard succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode start(void* textureHandle) = 0;

    /// @brief Stop the pipeline.
   /// @return FrameworkReturnCode::_SUCCESS if the stop succeed, else FrameworkReturnCode::_ERROR_

    virtual FrameworkReturnCode stop() = 0;

    /// @brief update the pipeline
    /// Get the new pose and update the texture buffer with the image that has to be displayed
    virtual SinkReturnCode update(datastructure::Transform3Df & pose) = 0;

    /// @brief load a generic texture buffer.
    /// @param[in] textureHandle a pointer to the texture buffer which will be updated at each call of the update method.    
    /// @param[in] width textureHandle buffer width.
    /// @param[in] width textureHandle buffer height.
    /// @return FrameworkReturnCode::_SUCCESS if the loading succeed, else FrameworkReturnCode::_ERROR_   
    virtual SourceReturnCode loadSourceImage(void* sourceTextureHandle, int width, int height) = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IPipeline,
                             "b5a6225e-6a91-4050-b298-886f4c17d9d2",
                             "IPipeline",
                             "The interface to define a video see-throuh pipeline")

#endif // SOLAR_PIPELINE_H
