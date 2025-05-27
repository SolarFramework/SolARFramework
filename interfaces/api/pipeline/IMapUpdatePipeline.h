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

#ifndef SOLAR_IMAPUPDATEPIPELINE_H
#define SOLAR_IMAPUPDATEPIPELINE_H

#include "api/pipeline/IPipeline.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Map.h"
#include <xpcf/core/helpers.h>
#include <xpcf/core/helpers.h>


namespace SolAR {
namespace api {
namespace pipeline {

/**
 * @class IMapUpdatePipeline
 * @brief <B>Defines a map update pipeline.</B>
 * <TT>UUID: 49cbd32c-6dfa-4155-b151-7261dd13f552</TT>
 *
 * This class provides the interface to define a map update pipeline.
 */

class XPCF_CLIENTUUID("d9da863c-c9ff-4562-a3a2-329ac1f44008") XPCF_SERVERUUID("82f9fdff-06ee-471f-a260-b7f4ac414627")
    XPCF_GRPC_CLIENT_RECV_SIZE("-1") XPCF_GRPC_CLIENT_SEND_SIZE("-1")
    IMapUpdatePipeline : virtual public IPipeline {
public:
	/// @brief IMapUpdatePipeline default constructor
	IMapUpdatePipeline() = default;

	/// @brief IMapUpdatePipeline default destructor
	virtual ~IMapUpdatePipeline() = default;

    /// @brief Set the map to use for this Map Update pipeline instance
    /// @param[in] uuid the map UUID
    /// @return FrameworkReturnCode::_SUCCESS if the map UUID is correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setMapUUID(const std::string & uuid) = 0;

    /// @brief Get the map UUID associated to this Map Update pipeline instance
    /// @param[out] uuid the map UUID
    /// @return FrameworkReturnCode::_SUCCESS if the map UUID exists, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getMapUUID(std::string & uuid) const = 0;

    /// @brief Reset the map stored by the map update pipeline
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the map is correctly reset
    /// * FrameworkReturnCode::_BUSY if this pipeline still has pending processing
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode resetMap() = 0;

    /// @brief Set the camera parameters
    /// @param[in] cameraParams the camera parameters (its resolution and its focal)
	/// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCameraParameters(const SolAR::datastructure::CameraParameters & cameraParams) = 0;

	/// @brief Request to the map update pipeline to update the global map from a local map
    /// @param[in] map the input local map to process
	/// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    [[grpc::client_sendSize("-1")]] virtual FrameworkReturnCode mapUpdateRequest(const SRef<SolAR::datastructure::Map> map) = 0;

    /// @brief Request to the map update pipeline to get the global map
    /// @param[out] map the output global map
    /// @param[in] withKeyframeImages indicate if the keyframe images are requested in output datastructure (true by default)
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the global map is available
    /// * FrameworkReturnCode::_NOT_FOUND if no map has already been set
    /// * else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getMapRequest(SRef<SolAR::datastructure::Map> & map,
                                                                                 const bool withKeyframeImages = true) const = 0;

	/// @brief Request to the map update pipeline to get a submap based on a query frame.
	/// @param[in] frame the query frame
	/// @param[out] map the output submap
	/// @return FrameworkReturnCode::_SUCCESS if submap is found, else FrameworkReturnCode::_ERROR_
	[[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getSubmapRequest(const SRef<SolAR::datastructure::Frame> frame, 
																					SRef<SolAR::datastructure::Map> & map) const = 0;

    /// @brief Request to the map update pipeline to get the point cloud of the global map
    /// @param[out] pointCloud the output point cloud
    /// @return FrameworkReturnCode::_SUCCESS if the point cloud is available, else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getPointCloudRequest(SRef<SolAR::datastructure::PointCloud> & pointCloud) const = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IMapUpdatePipeline,
                             "49cbd32c-6dfa-4155-b151-7261dd13f552",
                             "IMapUpdatePipeline",
                             "The interface to define a map update pipeline")

#endif // SOLAR_IMAPUPDATEPIPELINE_H
