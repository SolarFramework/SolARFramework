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

///
/// @typedef MapProcessingStatus
/// @brief <B>Indicate the status of the current map processing</B>
///
typedef enum {
    NOT_INITIALIZED = 0,  // Map processing not initialized
    INITIALIZED = 1,      // Map processing correctly initialized, but not started
    IN_PROGRESS = 2,      // Map processing in progress
    COMPLETED = 3,        // Map processing completed
    ABORTED = 4           // Map Processing aborted before completion
} MapProcessingStatus;

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

    /// @brief Set map to process
    /// @param[in] map input map to be processed (datastructure)
    /// @return FrameworkReturnCode::_SUCCESS if the map datastructure is correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setMapToProcess(const SRef<SolAR::datastructure::Map> map) = 0;

    /// @brief Get status and progress percentage
    /// @param[out] status the current map processing status
    /// @param[out] progress the current progress percentage (valid value should be between 0 and 1)
    /// @return FrameworkReturnCode::_SUCCESS if the status and progress are available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getStatus(MapProcessingStatus & status, float & progress) const = 0;

    /// @brief Provide the current data from the map processing pipeline context for visualization
    /// (resulting from all map processing since the start of the pipeline)
    /// @param[out] pointCloud pipeline current point cloud
    /// @param[out] keyframePoses pipeline current keyframe poses
    /// @return FrameworkReturnCode::_SUCCESS if data is available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getDataForVisualization(std::vector<SRef<SolAR::datastructure::CloudPoint>> & pointCloud,
                                                        std::vector<SolAR::datastructure::Transform3Df> & keyframePoses) const = 0;

    /// @brief Get processed map (if processing is completed)
    /// @param[out] map the output map (datastructure)
    /// @return FrameworkReturnCode::_SUCCESS if output map is available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getProcessedMap(SRef<SolAR::datastructure::Map> & map) const = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IMapProcessingPipeline,
                             "6dfb6b83-d4c0-44c5-be5f-0298a7b9e833",
                             "IMapProcessingPipeline",
                             "The interface to define a map processing pipeline")

#endif // SOLAR_MAPPROCESSINGPIPELINE_H
