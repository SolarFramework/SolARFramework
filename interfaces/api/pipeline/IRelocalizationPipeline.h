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
#include "datastructure/Map.h"
#include "xpcf/core/helpers.h"


namespace SolAR {
namespace api {
namespace pipeline {

/**
 * @class IRelocalizationPipeline
 * @brief <B>Defines a relocalization pipeline.</B>
 * <TT>UUID: ef2a631d-93c9-4979-ad1e-5fa16d5d00ef</TT>
 *
 * This class provides the interface to define a relocalization processing pipeline.
 */

class XPCF_CLIENTUUID("597d510d-452a-4da2-9c3a-8d4b8d15c584") XPCF_SERVERUUID("234bb765-ac3b-4755-8825-5cd92145b7a8") 
#ifndef DOXYGEN_SHOULD_SKIP_THIS // Doxygen does not support custom DSL
	XPCF_GRPC_CLIENT_RECV_SIZE("-1") XPCF_GRPC_CLIENT_SEND_SIZE("-1")
#endif
	IRelocalizationPipeline : virtual public IPipeline {
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
    /// @param[in] poseCoarse: (optional) coarse pose which needs to be refined by reloc, by default, poseCoarse equals identity matrix meaning that no coarse pose is provided
    /// @return FrameworkReturnCode::_SUCCESS if the processing is successful, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode relocalizeProcessRequest(const SRef<SolAR::datastructure::Image> image,
                                                         SolAR::datastructure::Transform3Df& pose, float_t & confidence, const SolAR::datastructure::Transform3Df& poseCoarse = SolAR::datastructure::Transform3Df::Identity()) = 0;

	/// @brief Request to the relocalization pipeline to get the map
	/// @param[out] map the output map
	/// @return FrameworkReturnCode::_SUCCESS if the map is available, else FrameworkReturnCode::_ERROR_
	[[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getMapRequest(SRef<SolAR::datastructure::Map> & map) const = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IRelocalizationPipeline,
                             "ef2a631d-93c9-4979-ad1e-5fa16d5d00ef",
                             "IRelocalizationPipeline",
                             "The interface to define a relocalization processing pipeline")

#endif // SOLAR_RELOCALIZATIONPIPELINE_H
