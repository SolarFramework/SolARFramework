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

#include <api/map/IMapFromMapProcessing.h>

namespace SolAR {
namespace api {
namespace map {

/**
 * @class IMultiViewStereo
 * @brief <B>Create a dense point cloud from images with corresponding poses.</B>
 * <TT>UUID: d73ae23f-e1ce-4abe-91cd-9aa2f34c8dff</TT>
 *
 */

class XPCF_IGNORE IMultiViewStereo : virtual public IMapFromMapProcessing
{
public:

    /// @enum class MVSProcessingStatus
    /// @brief define the different status of processing
    enum class MVSProcessingStatus {
        NOT_DEFINED = 0,
        NOT_INITIALIZED,
        IDLE_INITIALIZED,
        IDLE_COMPLETED,
        IDLE_ABORTED,
        RUNNING_IMAGE_UNDISTORTION,
        IDLE_IMAGE_UNDISTORTION_FINISHED,
        RUNNING_STEREO,
        IDLE_STEREO_FINISHED,
        RUNNING_FUSION,
        IDLE_FUSION_FINISHED,
        RUNNING_MESHING,
        IDLE_MESHING_FINISHED,
    };

    /// @brief return a string value of a ProcessingStatus value
    std::string toString(MVSProcessingStatus status) {
        switch (status) {
            case MVSProcessingStatus::NOT_DEFINED: return "NOT_DEFINED";
            case MVSProcessingStatus::NOT_INITIALIZED: return "NOT_INITIALIZED";
            case MVSProcessingStatus::IDLE_INITIALIZED: return "IDLE_INITIALIZED";
            case MVSProcessingStatus::IDLE_COMPLETED: return "IDLE_COMPLETED";
            case MVSProcessingStatus::IDLE_ABORTED: return "IDLE_ABORTED";
            case MVSProcessingStatus::RUNNING_IMAGE_UNDISTORTION: return "RUNNING_IMAGE_UNDISTORTION";
            case MVSProcessingStatus::IDLE_IMAGE_UNDISTORTION_FINISHED: return "IDLE_IMAGE_UNDISTORTION_FINISHED";
            case MVSProcessingStatus::RUNNING_STEREO: return "RUNNING_STEREO";
            case MVSProcessingStatus::IDLE_STEREO_FINISHED: return "IDLE_STEREO_FINISHED";
            case MVSProcessingStatus::RUNNING_FUSION: return "RUNNING_FUSION";
            case MVSProcessingStatus::IDLE_FUSION_FINISHED: return "IDLE_FUSION_FINISHED";
            case MVSProcessingStatus::RUNNING_MESHING: return "RUNNING_MESHING";
            case MVSProcessingStatus::IDLE_MESHING_FINISHED: return "IDLE_MESHING_FINISHED";
            default: throw std::invalid_argument("DensifyProcessingStatus value is unknown");
        }
    }

public:
    ///@brief IMultiViewStereo default constructor.
    IMultiViewStereo() = default;

    ///@brief IMultiViewStereo default destructor.
    virtual ~IMultiViewStereo() override = default;

    /// @brief Get current processing status
    /// @return status the current status
    virtual MVSProcessingStatus getStatus() const = 0;

    /// @brief Get current keyframe poses
    /// @param[out] keyframePoses current keyframes' poses
    /// @return FrameworkReturnCode::_SUCCESS if keyframe was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    /// @note This method is not applicable for this interface
    FrameworkReturnCode getCurrentKeyframePoses(std::vector<SolAR::datastructure::Transform3Df>& keyframePoses) const final;
};


} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::IMultiViewStereo,
                             "d73ae23f-e1ce-4abe-91cd-9aa2f34c8dff",
                             "IMultiViewStereo",
                             "IMultiViewStereo interface description");

#endif // IMULTIVIEWSTEREO_H
