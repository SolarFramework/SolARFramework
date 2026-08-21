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
 * @brief <B>Estimates a dense depth map per view for a set of POSED views.</B>
 * <TT>UUID: 44f73076-f3bc-4d70-b2d6-c5f765592b32</TT>
 *
 * Unlike SolAR::api::geom::IMonocularDepthEstimation, which predicts each image in isolation,
 * an implementation of this interface is given the whole posed view set up front and may reason
 * jointly over it. That is what pose-conditioned multi-view models need in order to return depth
 * maps that are mutually consistent in one metric frame, instead of a per-image affine-invariant
 * depth that has to be re-aligned view by view afterwards.
 *
 * Depth is produced one view at a time rather than all at once, so a caller fusing a large map
 * never has to hold every depth map in memory.
 *
 * Implementations may also return a per-pixel confidence, which callers can use to reject the
 * pixels a model has no real prediction for and to weight the rest.
 *
 * A model that reasons jointly over a group of views typically resolves that group's geometry only
 * up to one overall scale, and nothing forces two groups to land on the same one. estimate()
 * therefore reports which group a depth map came from: maps sharing a group id are mutually
 * consistent and share a single unknown scale, while maps from different groups are not comparable
 * until each group's scale is resolved. A caller recovering metric depth must fit its scale PER
 * GROUP -- fitting one scale over several groups, or one per view, both give the wrong answer.
 */
class XPCF_IGNORE IMultiViewDepthEstimation :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IMultiViewDepthEstimation default constructor
    IMultiViewDepthEstimation() = default;

    /// @brief IMultiViewDepthEstimation default destructor
    virtual ~IMultiViewDepthEstimation() = default;

    /// @brief Declare the posed views this estimator will be asked about.
    /// Must be called before estimate(). Implementations that reason jointly over the view set
    /// build their context here; implementations that do not may simply record the views.
    /// @param[in] keyframes the posed keyframes, carrying the view images and their poses.
    /// @param[in] cameraParameters the camera parameters referenced by those keyframes.
    /// @return FrameworkReturnCode::_SUCCESS if the view set is accepted, else
    /// FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setViews(const std::vector<SRef<SolAR::datastructure::Keyframe>>& keyframes,
                                         const std::vector<SRef<SolAR::datastructure::CameraParameters>>& cameraParameters) = 0;

    /// @brief Estimate the dense depth map of one of the views declared by setViews().
    /// @param[in] keyframeId id of the keyframe to estimate.
    /// @param[out] depthMap the estimated depth map. Single-channel image (LAYOUT_GREY) whose
    /// buffer holds one 32-bit floating point value per pixel, stored in a TYPE_32U container as
    /// the framework Image has no native float type: reinterpret the buffer as float* to read it.
    /// A value of 0 means "no depth at this pixel".
    /// @param[out] confidenceMap per-pixel confidence, same size, layout and encoding as depthMap.
    /// Left null by implementations that do not estimate confidence, so callers must check it.
    /// The scale is implementation-defined; only the ordering and the estimator's own floor value
    /// are meaningful across pixels.
    /// @param[out] viewGroupId identifies the group of views this depth map was estimated with.
    /// Depth maps sharing a group id are mutually consistent and carry one common unknown scale;
    /// maps from different groups do not. Implementations that estimate every view in a single
    /// joint pass return the same id throughout.
    /// @return FrameworkReturnCode::_SUCCESS if estimation succeeds, else
    /// FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode estimate(uint32_t keyframeId,
                                         SRef<SolAR::datastructure::Image>& depthMap,
                                         SRef<SolAR::datastructure::Image>& confidenceMap,
                                         uint32_t& viewGroupId) = 0;
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::geom::IMultiViewDepthEstimation,
                             "44f73076-f3bc-4d70-b2d6-c5f765592b32",
                             "IMultiViewDepthEstimation",
                             "SolAR::api::geom::IMultiViewDepthEstimation interface");

#endif // SOLAR_IMULTIVIEWDEPTHESTIMATION_H
