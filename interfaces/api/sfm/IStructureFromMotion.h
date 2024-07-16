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
namespace api {
namespace sfm {

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
    /// @param[out] map output map created by structure from motion
    /// @return FrameworkReturnCode::_SUCCESS if map is created successfully, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMap(const std::vector<SRef<SolAR::datastructure::Image>>& images,
                                          SRef<SolAR::datastructure::Map> map) = 0;

    /// @brief Create map from a set of images with provided camera parameters
    /// @param[in] imageCamIds list of pairs of image and camera ID
    /// @param[in] cameraParameters collection of camera parameters
    /// @param[out] map output map created by structure from motion
    /// @return FrameworkReturnCode::_SUCCESS if map is created successfully, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMap(const std::vector<std::pair<SRef<SolAR::datastructure::Image>, uint32_t>>& imageCamIds,
                                          const SRef<SolAR::datastructure::CameraParametersCollection> cameraParameters,
                                          SRef<SolAR::datastructure::Map> map) = 0;

    /// @brief Create map from a set of keyframes and camera parameters
    /// @param[in] keyframes collection of keyframes
    /// @param[in] cameraParameters collection of camera parameters
    /// @param[out] map output map created by structure from motion
    /// @return FrameworkReturnCode::_SUCCESS if map is created successfully, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMap(const SRef<SolAR::datastructure::KeyframeCollection> keyframes,
                                          const SRef<SolAR::datastructure::CameraParametersCollection> cameraParameters,
                                          SRef<SolAR::datastructure::Map> map) = 0;

    /// @brief Create map from a set of keyframes and camera parameters
    /// @param[in] keyframes list of keyframes
    /// @param[in] cameraParameters collection of camera parameters
    /// @param[out] map output map created by structure from motion
    /// @return FrameworkReturnCode::_SUCCESS if map is created successfully, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMap(const std::vector<SRef<SolAR::datastructure::Keyframe>>& keyframes,
                                          const SRef<SolAR::datastructure::CameraParametersCollection> cameraParameters,
                                          SRef<SolAR::datastructure::Map> map) = 0;
};

} // namespace sfm
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::sfm::IStructureFromMotion,
                             "3681e09b-1704-4a08-b1cd-42d5a7c961b4",
                             "IStructureFromMotion",
                             "IStructureFromMotion interface description");

#endif // ISTRUCTUREFROMMOTION_H
