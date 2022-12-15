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

#ifndef SOLAR_DENSEMAPPINGPIPELINE_H
#define SOLAR_DENSEMAPPINGPIPELINE_H


#include "api/pipeline/IPipeline.h"
#include "datastructure/Map.h"
#include "datastructure/Mesh.h"
#include "xpcf/core/helpers.h"


namespace SolAR {
namespace api {
namespace pipeline {

///
/// @typedef DenseMappingStatus
/// @brief <B>Indicate the status of the dense mapping pipeline</B>
///
typedef enum {
    MVS = 0,      // Multiview Stereo step to densify points
    MESHING = 1,  // meshing step to create a mesh from the dense point cloud
    DONE = 2      // dense reconstruction is done
} DenseMappingStatus;

/**
 * @class IDenseMappingPipeline
 * @brief <B>Defines pipeline to create a dense point cloud or a mesh from a sparse map.</B>
 * <TT>UUID: 34ab0434-480b-11ed-b878-0242ac120002</TT>
 *
 * This class provides the interface to define a dense mapping processing pipeline.
 */

class [[xpcf::clientUUID("54fc1ed0-480b-11ed-b878-0242ac120002")]] [[xpcf::serverUUID("5ac9298e-480b-11ed-b878-0242ac120002")]]
#ifndef DOXYGEN_SHOULD_SKIP_THIS // Doxygen does not support custom DSL
    XPCF_GRPC_CLIENT_RECV_SIZE("-1") XPCF_GRPC_CLIENT_SEND_SIZE("-1")
#endif
    IDenseMappingPipeline : virtual public IPipeline {
public:
    /// @brief IDenseMappingPipeline default constructor
    IDenseMappingPipeline() = default;

    /// @brief IDenseMappingPipeline default destructor
    virtual ~IDenseMappingPipeline() = default;

    /// @brief Request to the dense mapping pipeline to process a sparse map
    /// @param[in] sparseMap: the sparse map to use to create a dense map
    /// @param[in] createMesh: true to create a mesh, otherwise, just a dense point cloud is created
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    [[grpc::client_sendSize("-1")]] virtual FrameworkReturnCode denseMappingProcessRequest(const SRef<SolAR::datastructure::Map> & sparseMap,
                                                           const bool createMesh) = 0;

    /// @brief Provide the dense pottn cloud resulting from the dense mapping of the sparse map
    /// @param[out] outputPointCloud: the resulting dense point cloud
    /// @param[out] status: the current status of the dense mapping pipeline
    /// @return FrameworkReturnCode::_SUCCESS if data are available, else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getPointCloud(SRef<SolAR::datastructure::PointCloud> & outputPointCloud, DenseMappingStatus & status) const = 0;

    /// @brief Provide the mesh resulting from the dense mapping of the sparse map
    /// @param[out] outputMesh: the resulting mesh
    /// @param[out] status: the current status of the dense mapping pipeline
    /// @return FrameworkReturnCode::_SUCCESS if data are available, else FrameworkReturnCode::_ERROR_
    [[grpc::client_receiveSize("-1")]] virtual FrameworkReturnCode getMesh(SRef<SolAR::datastructure::Mesh>& outputMesh, DenseMappingStatus & status) const = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IDenseMappingPipeline,
                             "34ab0434-480b-11ed-b878-0242ac120002",
                             "IDenseMappingPipeline",
                             "The interface to define a dense mapping processing pipeline")

#endif // SOLAR_DENSEMAPPINGPIPELINE_H
