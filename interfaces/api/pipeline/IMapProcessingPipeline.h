/**
 * @copyright Copyright (c) 2024 B-com http://www.b-com.com/
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

#ifndef SOLAR_MAPPROCESSINGPIPELINE_H
#define SOLAR_MAPPROCESSINGPIPELINE_H

#include "api/pipeline/IPipeline.h"
#include "datastructure/Map.h"
#include <xpcf/core/helpers.h>


namespace SolAR {
namespace api {
namespace pipeline {

/**
 * @class IMapProcessingPipeline
 * @brief <B>Defines a map processing pipeline.</B>
 * <TT>UUID: 6dfb6b83-d4c0-44c5-be5f-0298a7b9e833</TT>
 *
 * This class provides the interface to define a map processing pipeline.
 */

class XPCF_CLIENTUUID("3e0afc52-5d71-411a-9e5b-bb73ced1cad0") XPCF_SERVERUUID("2dffb653-4d96-41bc-a2f9-1cc850c7498b")
    XPCF_GRPC_CLIENT_RECV_SIZE("-1") XPCF_GRPC_CLIENT_SEND_SIZE("-1")
    IMapProcessingPipeline : virtual public IPipeline {
public:
    /// @brief IMapProcessingPipeline default constructor
    IMapProcessingPipeline() = default;

    /// @brief IMapProcessingPipeline default destructor
    virtual ~IMapProcessingPipeline() = default;

    /// @brief Map processing request
    /// @param[in] map input map
    /// @return FrameworkReturnCode::_SUCCESS if map processed successfully, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode mapProcessingRequest(SRef<const datastructure::Map> map) = 0;

    /// @brief Provide the current data from the map processing pipeline context for visualization
    /// (resulting from all map processing since the start of the pipeline)
    /// @param[out] pointCloud: pipeline current point cloud
    /// @param[out] keyframePoses: pipeline current keyframe poses
    /// @return FrameworkReturnCode::_SUCCESS if data are available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getDataForVisualization(std::vector<SRef<SolAR::datastructure::CloudPoint>>& pointCloud, std::vector<SolAR::datastructure::Transform3Df>& keyframePoses) const = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IMapProcessingPipeline,
                             "6dfb6b83-d4c0-44c5-be5f-0298a7b9e833",
                             "IMapProcessingPipeline",
                             "The interface to define a map processing pipeline")

#endif // SOLAR_MAPPROCESSINGPIPELINE_H
