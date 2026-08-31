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

#ifndef SOLAR_IMULTIVIEWDEPTHESTIMATION_H
#define SOLAR_IMULTIVIEWDEPTHESTIMATION_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/Keyframe.h"
#include "core/Messages.h"

#include <vector>

namespace SolAR {
namespace api {
namespace geom {

/** @class IMultiViewDepthEstimation
 * @brief <B>Estimates a dense depth map per view for a set of posed views.</B>
 * <TT>UUID: 44f73076-f3bc-4d70-b2d6-c5f765592b32</TT>
 */
class XPCF_IGNORE IMultiViewDepthEstimation :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IMultiViewDepthEstimation default constructor
    IMultiViewDepthEstimation() = default;

    /// @brief IMultiViewDepthEstimation default destructor
    virtual ~IMultiViewDepthEstimation() = default;

    /// @brief Set the posed views to estimate, must be called before estimate().
    /// @param[in] keyframes the posed keyframes with their images.
    /// @param[in] cameraParameters the camera parameters of the keyframes.
    /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setViews(const std::vector<SRef<SolAR::datastructure::Keyframe>>& keyframes,
                                         const std::vector<SRef<SolAR::datastructure::CameraParameters>>& cameraParameters) = 0;

    /// @brief Estimate the dense depth map of a view set by setViews().
    /// @param[in] keyframeId id of the keyframe.
    /// @param[out] depthMap the depth map, LAYOUT_GREY, float values stored in a TYPE_32U buffer, 0 = no depth.
    /// @param[out] confidenceMap per-pixel confidence, same encoding as depthMap, null if not estimated.
    /// @param[out] viewGroupId group of views sharing one unknown scale.
    /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode estimate(uint32_t keyframeId,
                                         SRef<SolAR::datastructure::Image>& depthMap,
                                         SRef<SolAR::datastructure::Image>& confidenceMap,
                                         uint32_t& viewGroupId) = 0;

    /// @brief Release device resources, estimate() is invalid until the next setViews().
    /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode releaseDeviceResources() { return FrameworkReturnCode::_SUCCESS; }
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::geom::IMultiViewDepthEstimation,
                             "44f73076-f3bc-4d70-b2d6-c5f765592b32",
                             "IMultiViewDepthEstimation",
                             "SolAR::api::geom::IMultiViewDepthEstimation interface");

#endif // SOLAR_IMULTIVIEWDEPTHESTIMATION_H
