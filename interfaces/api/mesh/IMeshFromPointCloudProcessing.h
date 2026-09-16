/**
 * @copyright Copyright (c) 2026 B-com http://www.b-com.com/
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

#ifndef IMESHFROMPOINTCLOUDPROCESSING_H
#define IMESHFROMPOINTCLOUDPROCESSING_H

#include "api/mesh/IMeshFromDatastructureProcessing.h"
#include "datastructure/PointCloud.h"

namespace SolAR {
namespace api {
namespace mesh {

/**
 * @class IMeshFromPointCloudProcessing
 * @brief <B>Create a 3D mesh from a 3D dense map.</B>
 * <TT>UUID: 7d810e96-fd9d-4029-a102-61fe3883a633</TT>
 *
 */

class XPCF_IGNORE IMeshFromPointCloudProcessing : virtual public IMeshFromDatastructureProcessing
{
public:

    /// @enum class MeshProcessingStatus
    /// @brief define the different status of processing
    enum class MeshProcessingStatus {
        NOT_DEFINED = 0,
        NOT_INITIALIZED,
        IDLE_INITIALIZED,
        IDLE_COMPLETED,
        IDLE_ABORTED,
    };

    /// @brief return a string value of a MeshProcessingStatus value
    std::string toString(MeshProcessingStatus status) {
        switch (status) {
            case MeshProcessingStatus::NOT_DEFINED: return "NOT_DEFINED";
            case MeshProcessingStatus::NOT_INITIALIZED: return "NOT_INITIALIZED";
            case MeshProcessingStatus::IDLE_INITIALIZED: return "IDLE_INITIALIZED";
            case MeshProcessingStatus::IDLE_COMPLETED: return "IDLE_COMPLETED";
            case MeshProcessingStatus::IDLE_ABORTED: return "IDLE_ABORTED";
            default: throw std::invalid_argument("DensifyProcessingStatus value is unknown");
        }
    }

public:

    ///@brief IMeshFromPointCloudProcessing default destructor.
    virtual ~IMeshFromPointCloudProcessing() override = default;

    /// @brief Get current processing status
    /// @return status the current status
    virtual MeshProcessingStatus getStatus() const = 0;

    /// @brief Create a new mesh resulting from the processing of the original point cloud
    /// @param[in] densePointCloud the original pointcloud
    /// @return FrameworkReturnCode::_SUCCESS if the processing succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMesh(const SRef<SolAR::datastructure::PointCloud>& densePointCloud) = 0;

};

} // namespace mesh
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::mesh::IMeshFromPointCloudProcessing,
                             "7d810e96-fd9d-4029-a102-61fe3883a633",
                             "IMeshFromPointCloudProcessing",
                             "IMeshFromPointCloudProcessing interface description");

#endif // IMESHFROMPOINTCLOUDPROCESSING_H
