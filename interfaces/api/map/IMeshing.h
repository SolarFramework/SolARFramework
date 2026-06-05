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

#ifndef IMESHING_H
#define IMESHING_H


#include "api/map/IProcessMap.h"
#include "datastructure/Map.h"
#include "datastructure/Mesh.h"

namespace SolAR {
namespace api {
namespace map {

/**
 * @class IMeshing
 * @brief <B>Create a 3D mesh from a 3D dense map.</B>
 * <TT>UUID: 7d810e96-fd9d-4029-a102-61fe3883a633</TT>
 */

class XPCF_IGNORE IMeshing : virtual public IProcessMap
{
public:

    /// @brief return a string value of a ProcessingStatus value
    std::string toString(ProcessingStatus status) override { return "NOT_DEFINED"; }

public:

    ///@brief IMeshing default constructor.
    IMeshing() = default;

    ///@brief IMeshing default destructor.
    virtual ~IMeshing() override = default;

    /// @brief Create a new map resulting from the processing of the original map
    /// @param[in] map the original map
    /// @return FrameworkReturnCode::_SUCCESS if the processing succeed, else FrameworkReturnCode::_ERROR_
    FrameworkReturnCode createMap(const SRef<SolAR::datastructure::Map>& map) override { return FrameworkReturnCode::_NOT_IMPLEMENTED; }

    /// @brief Get output map resulting from processing
    /// @param[out] map the output map
    /// @return FrameworkReturnCode::_SUCCESS if map was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode getOutputMap(SRef<SolAR::datastructure::Map>& map) override { return FrameworkReturnCode::_NOT_IMPLEMENTED; }

    /// @brief Get current processing status
    /// @return status the current status
    ProcessingStatus getStatus() override { return ProcessingStatus::NOT_DEFINED; }

    /// @brief Get current processing progress percentage
    /// @return progress percentage between 0 and 1
    float getProgress() override { return 0.0; }

    /// @brief Get current cloud points
    /// @param[out] cloudPoints current point cloud consisting of a number of 3D points
    /// @return FrameworkReturnCode::_SUCCESS if points was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode getCurrentCloudPoints(std::vector<SRef<SolAR::datastructure::CloudPoint>>& cloudPoints) override { return FrameworkReturnCode::_NOT_IMPLEMENTED; }

    /// @brief Get current keyframe poses
    /// @param[out] keyframePoses current keyframes' poses
    /// @return FrameworkReturnCode::_SUCCESS if keyframe was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode getCurrentKeyframePoses(std::vector<SolAR::datastructure::Transform3Df>& keyframePoses) override { return FrameworkReturnCode::_NOT_IMPLEMENTED; }

    /// @brief force stop
    void forceStop() override { }

    /// @brief release memory usage
    void releaseMemoryUsage() override { }

    /// @brief Create mesh from a dense 3D point cloud
    /// @param[in] densePointCloud: the dense point cloud to mesh with triangles
    /// @param[out] mesh: the resulting meshes
    /// @return FrameworkReturnCode::_SUCCESS if the meshing succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMesh(const SRef<SolAR::datastructure::PointCloud>& densePointCloud,
                                           SRef<SolAR::datastructure::Mesh>& mesh) = 0;
};


} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::IMeshing,
                             "7d810e96-fd9d-4029-a102-61fe3883a633",
                             "IMeshing",
                             "IMeshing interface description");

#endif // IMESHING_H
