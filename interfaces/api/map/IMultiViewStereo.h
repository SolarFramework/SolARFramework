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

#ifndef IMULTIVIEWSTEREO_H
#define IMULTIVIEWSTEREO_H

#include <api/map/IProcessMap.h>

namespace SolAR {
namespace api {
namespace map {

/**
 * @class IMultiViewStereo
 * @brief <B>Create a dense point cloud from images with corresponding poses.</B>
 * <TT>UUID: d73ae23f-e1ce-4abe-91cd-9aa2f34c8dff</TT>
 *
 */

class XPCF_IGNORE IMultiViewStereo : virtual public IProcessMap
{
public:

    /// @enum class MVSProcessingStatus
    /// @brief define the different status of processing
    enum class MVSProcessingStatus: std::underlying_type_t<ProcessingStatus> {
        RUNNING_IMAGE_UNDISTORTION = 5,
        IDLE_IMAGE_UNDISTORTION_FINISHED,
        RUNNING_STEREO,
        IDLE_STEREO_FINISHED,
        RUNNING_FUSION,
        IDLE_FUSION_FINISHED,
        RUNNING_MESHING,
        IDLE_MESHING_FINISHED,
    };

    /// @brief return a string value of a ProcessingStatus value
    std::string toString(ProcessingStatus status) override {
        switch ((ProcessingStatus)status) {
            case ProcessingStatus::NOT_DEFINED: return "NOT_DEFINED";
            case ProcessingStatus::NOT_INITIALIZED: return "NOT_INITIALIZED";
            case ProcessingStatus::IDLE_INITIALIZED: return "IDLE_INITIALIZED";
            case ProcessingStatus::IDLE_COMPLETED: return "IDLE_COMPLETED";
            case ProcessingStatus::IDLE_ABORTED: return "IDLE_ABORTED";
            case (ProcessingStatus)MVSProcessingStatus::RUNNING_IMAGE_UNDISTORTION: return "RUNNING_IMAGE_UNDISTORTION";
            case (ProcessingStatus)MVSProcessingStatus::IDLE_IMAGE_UNDISTORTION_FINISHED: return "IDLE_IMAGE_UNDISTORTION_FINISHED";
            case (ProcessingStatus)MVSProcessingStatus::RUNNING_STEREO: return "RUNNING_STEREO";
            case (ProcessingStatus)MVSProcessingStatus::IDLE_STEREO_FINISHED: return "IDLE_STEREO_FINISHED";
            case (ProcessingStatus)MVSProcessingStatus::RUNNING_FUSION: return "RUNNING_FUSION";
            case (ProcessingStatus)MVSProcessingStatus::IDLE_FUSION_FINISHED: return "IDLE_FUSION_FINISHED";
            case (ProcessingStatus)MVSProcessingStatus::RUNNING_MESHING: return "RUNNING_MESHING";
            case (ProcessingStatus)MVSProcessingStatus::IDLE_MESHING_FINISHED: return "IDLE_MESHING_FINISHED";
            default: return "NOT_DEFINED";
        }
    }

public:
    ///@brief IStructureFromMotion default constructor.
    IMultiViewStereo() = default;

    ///@brief IStructureFromMotion default destructor.
    virtual ~IMultiViewStereo() override = default;

    /// @brief Get current keyframe poses
    /// @param[out] keyframePoses current keyframes' poses
    /// @return FrameworkReturnCode::_SUCCESS if keyframe was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode getCurrentKeyframePoses(std::vector<SolAR::datastructure::Transform3Df>& keyframePoses) override { return FrameworkReturnCode::_NOT_IMPLEMENTED; }
};


} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::IMultiViewStereo,
                             "d73ae23f-e1ce-4abe-91cd-9aa2f34c8dff",
                             "IMultiViewStereo",
                             "IMultiViewStereo interface description");

#endif // IMULTIVIEWSTEREO_H
