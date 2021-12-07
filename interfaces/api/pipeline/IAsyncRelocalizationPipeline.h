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

/**
* @typedef TransformStatus
* @brief <B>Indicate the status of the 3D transformation matrix</B>
*/
typedef enum {
    NO_3DTRANSFORM = 0,       // No 3D transform available
    PREVIOUS_3DTRANSFORM = 1, // 3D transform previously given by the relocalization service
    NEW_3DTRANSFORM = 2       // New 3D transform given by the relocalization service
} TransformStatus;

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

    /// @brief Set the camera parameters
    /// @param[in] cameraParams: the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCameraParameters(const SolAR::datastructure::CameraParameters & cameraParams) = 0;

    /// @brief Get the camera parameters
    /// @param[out] cameraParams: the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly returned, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCameraParameters(SolAR::datastructure::CameraParameters & cameraParams) const = 0;

    /// @brief Request the asynchronous relocalization pipeline to process a new image to calculate
    /// the corresponding 3D transformation to the SolAR coordinates system
    /// @param[in] image: the image to process
    /// @param[in] pose: the original pose in the client coordinates system
    /// @param[in] timestamp: the timestamp of the image
    /// @param[out] transform3DStatus: the status of the current 3D transformation matrix
    /// @param[out] transform3D : the current 3D transformation matrix (if available)
    /// @param[out] confidence: the confidence score of the 3D transformation matrix
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode relocalizeProcessRequest(const SRef<SolAR::datastructure::Image> image,
                                                         const SolAR::datastructure::Transform3Df & pose,
                                                         const std::chrono::system_clock::time_point & timestamp,
                                                         TransformStatus & transform3DStatus,
                                                         SolAR::datastructure::Transform3Df & transform3D,
                                                         float_t & confidence) = 0;

    /// @brief Request the asynchronous relocalization pipeline to get the 3D transform to the SolAR coordinates system
    /// @param[out] transform3DStatus: the status of the current 3D transformation matrix
    /// @param[out] transform3D : the current 3D transformation matrix (if available)
    /// @param[out] confidence: the confidence score of the 3D transformation matrix
    /// @return FrameworkReturnCode::_SUCCESS if the 3D transform is available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode get3DTransformRequest(TransformStatus & transform3DStatus,
                                                      SolAR::datastructure::Transform3Df & transform3D,
                                                      float_t & confidence) const = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IAsyncRelocalizationPipeline,
                             "58389ff0-5695-11ec-bf63-0242ac130002",
                             "IAsyncRelocalizationPipeline",
                             "The interface to define an asynchronous relocalization processing pipeline")

#endif // SOLAR_ASYNCRELOCALIZATIONPIPELINE_H
