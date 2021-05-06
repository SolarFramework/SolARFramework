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

#ifndef SOLAR_RELOCALIZATIONPIPELINE_H
#define SOLAR_RELOCALIZATIONPIPELINE_H


#include "api/pipeline/IPipeline.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Image.h"
#include "xpcf/core/helpers.h"


namespace SolAR {
namespace api {
namespace pipeline {

/**
 * @class IRelocalizationPipeline
 * @brief <B>Defines a relocalization pipeline.</B>
 * <TT>UUID: 2dc3cd33-5a11-4748-94a3-e7ab40462097</TT>
 *
 * This class provides the interface to define a relocalization processing pipeline.
 */

class XPCF_CLIENTUUID("110a089c-0bb1-488e-b24b-c1b96bc9df3b") XPCF_SERVERUUID("aced265d-832c-44e3-9356-dab531fa153a") IRelocalizationPipeline :
    virtual public IPipeline {
public:
    /// @brief IRelocalizationPipeline default constructor
    IRelocalizationPipeline() = default;

    /// @brief IRelocalizationPipeline default destructor
    virtual ~IRelocalizationPipeline() = default;

    /// @brief Set the camera parameters
    /// @param[in] cameraParams: the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCameraParameters(const SolAR::datastructure::CameraParameters & cameraParams) = 0;

    /// @brief Get the camera parameters
    /// @param[out] cameraParams: the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly returned, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCameraParameters(SolAR::datastructure::CameraParameters & cameraParams) const = 0;

    /// @brief Request the relocalization pipeline to process a new image to calculate the corresponding pose
    /// @param[in] image: the image to process
    /// @param[out] pose: the new calculated pose
    /// @param[out] confidence: the confidence score
    /// @return FrameworkReturnCode::_SUCCESS if the processing is successful, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode relocalizeProcessRequest(const SRef<SolAR::datastructure::Image> image,
                                                         SolAR::datastructure::Transform3Df& pose, float_t & confidence) = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IRelocalizationPipeline,
                             "2dc3cd33-5a11-4748-94a3-e7ab40462097",
                             "IRelocalizationPipeline",
                             "The interface to define a relocalization processing pipeline")

#endif // SOLAR_RELOCALIZATIONPIPELINE_H
