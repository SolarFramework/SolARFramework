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
#include <xpcf/api/IComponentIntrospect.h>

namespace SolAR {
using namespace datastructure;
namespace api {
namespace sfm {

///@enum class SfmStatus
enum class SfmStatus {
    NOT_INITIALIZED,
    IDLE_INITIALIZED,
    RUNNING_DESCRIPTOR_MATCHING,
    IDLE_DESCRIPTOR_MATCHING_FINISHED,
    RUNNING_INITIAL_MAPPING,
    IDLE_INITIAL_MAPPING_FINISHED,
    RUNNING_INCREMENTAL_MAPPING,
    IDLE_INCREMENTAL_MAPPING_FINISHED,
    RUNNING_POST_PROCESSING,
    IDLE_COMPLETED,
    IDLE_ABORTED,
};

/// @brief map from SfmStatus to string
const static std::map<SfmStatus, std::string> mapSfmStatusToStr = {
    {SfmStatus::NOT_INITIALIZED, "NOT_INITIALIZED"},
    {SfmStatus::IDLE_INITIALIZED, "IDLE_INITIALIZED"},
    {SfmStatus::RUNNING_DESCRIPTOR_MATCHING, "RUNNING_DESCRIPTOR_MATCHING"},
    {SfmStatus::IDLE_DESCRIPTOR_MATCHING_FINISHED, "IDLE_DESCRIPTOR_MATCHING_FINISHED"},
    {SfmStatus::RUNNING_INITIAL_MAPPING, "RUNNING_INITIAL_MAPPING"},
    {SfmStatus::IDLE_INITIAL_MAPPING_FINISHED, "IDLE_INITIAL_MAPPING_FINISHED"},
    {SfmStatus::RUNNING_INCREMENTAL_MAPPING, "RUNNING_INCREMENTAL_MAPPING"},
    {SfmStatus::IDLE_INCREMENTAL_MAPPING_FINISHED, "IDLE_INCREMENTAL_MAPPING_FINISHED"},
    {SfmStatus::RUNNING_POST_PROCESSING, "RUNNING_POST_PROCESSING"},
    {SfmStatus::IDLE_COMPLETED, "IDLE_COMPLETED"},
    {SfmStatus::IDLE_ABORTED, "IDLE_ABORTED"}
};

/**
 * @class IStructureFromMotion
 * @brief <B>Create a sparse point cloud and estimate camera poses from a set of images or a set of descriptors stored inside the keyframes.</B>
 * <TT>UUID: 3681e09b-1704-4a08-b1cd-42d5a7c961b4</TT>
 *
 */

class XPCF_IGNORE IStructureFromMotion : virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
    ///@brief IStructureFromMotion default constructor.
    IStructureFromMotion() = default;

    ///@brief IStructureFromMotion default destructor.
    virtual ~IStructureFromMotion() override = default;

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

    /// @brief Set information for the map created for SfM processing
    /// @param[in] descriptorType descriptor type used for the map
    /// @param[in] globalDescriptorType global descriptor type used for the map
    /// @param[in] embedKeyframeImages true if images are embedded with keyframes, false otherwise
    /// @return FrameworkReturnCode::_SUCCESS if information are set successfully, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setMapInfo(const DescriptorType descriptorType, const GlobalDescriptorType globalDescriptorType, const bool embedKeyframeImages) = 0;

    /// @brief Get output map
    /// @param[out] map the output SfM map
    /// @return FrameworkReturnCode::_SUCCESS if map was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getOutputMap(SRef<Map>& map) = 0;

    /// @brief Get SfM status
    /// @return status the current SfM status
    virtual SfmStatus getStatus() = 0;

    /// @brief Get SfM progress percentage
    /// @return progress percentage between 0 and 1
    virtual float getProgress() = 0;

    /// @brief Get current cloud points
    /// @param[out] cloudPoints current point cloud consisting of a number of 3D points
    /// @return FrameworkReturnCode::_SUCCESS if points was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCurrentCloudPoints(std::vector<SRef<CloudPoint>>& cloudPoints) = 0;

    /// @brief Get current keyframe poses
    /// @param[out] keyframePoses current keyframes' poses
    /// @return FrameworkReturnCode::_SUCCESS if keyframe was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCurrentKeyframePoses(std::vector<Transform3Df>& keyframePoses) = 0;

    /// @brief force stop
    virtual void forceStop() = 0;

    /// @brief release memory usage
    virtual void releaseMemoryUsage() = 0;

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

} // namespace sfm
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::sfm::IStructureFromMotion,
                             "3681e09b-1704-4a08-b1cd-42d5a7c961b4",
                             "IStructureFromMotion",
                             "IStructureFromMotion interface description");

#endif // ISTRUCTUREFROMMOTION_H
