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

#ifndef ISTRUCTUREFROMMOTION_H
#define ISTRUCTUREFROMMOTION_H

#include "core/Messages.h"
#include "datastructure/Map.h"
#include "api/map/IProcessMap.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace map {

/**
 * @class IStructureFromMotion
 * @brief <B>Create a sparse point cloud and estimate camera poses from a set of images or a set of descriptors stored inside the keyframes.</B>
 * <TT>UUID: 3681e09b-1704-4a08-b1cd-42d5a7c961b4</TT>
 *
 */

class XPCF_IGNORE IStructureFromMotion : virtual public IProcessMap
{
public:

    /// @enum class SfmProcessingStatus
    /// @brief define the different status of processing
    enum class SfmProcessingStatus: std::underlying_type_t<ProcessingStatus> {
        RUNNING_DESCRIPTOR_MATCHING = 5,
        IDLE_DESCRIPTOR_MATCHING_FINISHED,
        RUNNING_INITIAL_MAPPING,
        IDLE_INITIAL_MAPPING_FINISHED,
        RUNNING_INCREMENTAL_MAPPING,
        IDLE_INCREMENTAL_MAPPING_FINISHED,
        RUNNING_POST_PROCESSING,
    };

    /// @brief return a string value of a ProcessingStatus value
    std::string toString(ProcessingStatus status) override {
        switch ((ProcessingStatus)status) {
        case ProcessingStatus::NOT_DEFINED: return "NOT_DEFINED";
        case ProcessingStatus::NOT_INITIALIZED: return "NOT_INITIALIZED";
        case ProcessingStatus::IDLE_INITIALIZED: return "IDLE_INITIALIZED";
        case ProcessingStatus::IDLE_COMPLETED: return "IDLE_COMPLETED";
        case ProcessingStatus::IDLE_ABORTED: return "IDLE_ABORTED";
        case (ProcessingStatus)SfmProcessingStatus::RUNNING_DESCRIPTOR_MATCHING: return "RUNNING_DESCRIPTOR_MATCHING";
        case (ProcessingStatus)SfmProcessingStatus::IDLE_DESCRIPTOR_MATCHING_FINISHED: return "IDLE_DESCRIPTOR_MATCHING_FINISHED";
        case (ProcessingStatus)SfmProcessingStatus::RUNNING_INITIAL_MAPPING: return "RUNNING_INITIAL_MAPPING";
        case (ProcessingStatus)SfmProcessingStatus::IDLE_INITIAL_MAPPING_FINISHED: return "IDLE_INITIAL_MAPPING_FINISHED";
        case (ProcessingStatus)SfmProcessingStatus::RUNNING_INCREMENTAL_MAPPING: return "RUNNING_INCREMENTAL_MAPPINGRUNNING_INCREMENTAL_MAPPING";
        case (ProcessingStatus)SfmProcessingStatus::IDLE_INCREMENTAL_MAPPING_FINISHED: return "IDLE_INCREMENTAL_MAPPING_FINISHED";
        case (ProcessingStatus)SfmProcessingStatus::RUNNING_POST_PROCESSING: return "RUNNING_POST_PROCESSING";
        default: return "NOT_DEFINED";
        }
    }

public:

    ///@brief IStructureFromMotion default constructor.
    IStructureFromMotion() = default;

    ///@brief IStructureFromMotion default destructor.
    virtual ~IStructureFromMotion() override = default;

    /// @brief Create a new map resulting from the processing of the original map
    /// @param[in] map the original map
    /// @return FrameworkReturnCode::_SUCCESS if the processing succeed, else FrameworkReturnCode::_ERROR_
    FrameworkReturnCode createMap(const SRef<SolAR::datastructure::Map>& map) override { return FrameworkReturnCode::_NOT_IMPLEMENTED; }

    /// @brief Create map from a set of images while camera parameters are not provided
    /// @param[in] images list of images
    /// @return FrameworkReturnCode::_SUCCESS if map is created successfully, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMap(const std::vector<SRef<Image>>& images) = 0;
    
    /// @brief Create map from a set of images with provided camera parameters
    /// @param[in] imageCamIds list of pairs of image and camera ID
    /// @param[in] cameraParameters list of camera parameters
    /// @return FrameworkReturnCode::_SUCCESS if map is created successfully, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMap(const std::vector<std::pair<SRef<Image>, uint32_t>>& imageCamIds, const std::vector<SRef<CameraParameters>>& cameraParameters) = 0;
    
    /// @brief Create map from a set of keyframes and camera parameters
    /// @param[in] keyframes list of keyframes
    /// @param[in] cameraParameters list of camera parameters
    /// @return FrameworkReturnCode::_SUCCESS if map is created successfully, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMap(const std::vector<SRef<Keyframe>>& keyframes, const std::vector<SRef<CameraParameters>>& cameraParameters) = 0;

    /// @brief Create map from a set of keyframes, camera parameters and covisibility graph
    /// @param[in] keyframes list of keyframes
    /// @param[in] cameraParameters list of camera parameters
    /// @param[in] covGraph covisibility graph
    /// @return FrameworkReturnCode::_SUCCESS if map is created successfully, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMap(const std::vector<SRef<Keyframe>>& keyframes, const std::vector<SRef<CameraParameters>>& cameraParameters, const CovisibilityGraph& covGraph) = 0;

    /// @brief Create map from a set of images with provided camera parameters
    /// @param[in] imageCamIds list of pairs of image and camera ID
    /// @param[in] cameraParameters collection of camera parameters
    /// @return FrameworkReturnCode::_SUCCESS if map is created successfully, otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode createMap(const std::vector<std::pair<SRef<Image>, uint32_t>>& imageCamIds, const SRef<CameraParametersCollection> cameraParameters);

    /// @brief Create map from a set of keyframes and camera parameters
    /// @param[in] keyframes collection of keyframes
    /// @param[in] cameraParameters collection of camera parameters
    /// @return FrameworkReturnCode::_SUCCESS if map is created successfully, otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode createMap(const SRef<KeyframeCollection> keyframes, const SRef<CameraParametersCollection> cameraParameters);

    /// @brief Create map from a set of keyframes and camera parameters
    /// @param[in] keyframes list of keyframes
    /// @param[in] cameraParameters collection of camera parameters
    /// @return FrameworkReturnCode::_SUCCESS if map is created successfully, otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode createMap(const std::vector<SRef<Keyframe>>& keyframes, const SRef<CameraParametersCollection> cameraParameters);

    /// @brief Create map from a set of keyframes and camera parameters
    /// @param[in] keyframes collection of keyframes
    /// @param[in] cameraParameters list of camera parameters
    /// @return FrameworkReturnCode::_SUCCESS if map is created successfully, otherwise FrameworkReturnCode::_ERROR_
    FrameworkReturnCode createMap(const SRef<KeyframeCollection> keyframes, const std::vector<SRef<CameraParameters>>& cameraParameters);

};

} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::IStructureFromMotion,
                             "3681e09b-1704-4a08-b1cd-42d5a7c961b4",
                             "IStructureFromMotion",
                             "IStructureFromMotion interface description");

#endif // ISTRUCTUREFROMMOTION_H
