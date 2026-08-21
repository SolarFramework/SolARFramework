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

#ifndef SOLAR_IMONOCULARDEPTHESTIMATION_H
#define SOLAR_IMONOCULARDEPTHESTIMATION_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "datastructure/Image.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace geom {

/** @class IMonocularDepthEstimation
 * @brief <B>Estimates a dense depth map from a single (monocular) RGB image.</B>
 * <TT>UUID: fc585010-1292-4d61-a2ef-d773def81b7f</TT>
 *
 * Unlike SolAR::api::geom::IDepthEstimation (which recovers depth from the
 * disparity of matched stereo keypoints), this interface predicts a per-pixel
 * depth map directly from a single image, typically using a deep neural network.
 */
class XPCF_IGNORE IMonocularDepthEstimation :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IMonocularDepthEstimation default constructor
    IMonocularDepthEstimation() = default;

    /// @brief IMonocularDepthEstimation default destructor
    virtual ~IMonocularDepthEstimation() = default;

    /// @brief Estimate a dense depth map from a single RGB image.
    /// @param[in] image the input image.
    /// @param[out] depthMap the estimated depth map, with the same width and
    /// height as the input image. It is a single-channel image (LAYOUT_GREY)
    /// whose buffer holds one 32-bit floating point depth value per pixel
    /// (stored in a TYPE_32U container as the framework Image has no native
    /// float type). Reinterpret the buffer as float* to read the depth values.
    /// @return FrameworkReturnCode::_SUCCESS if estimation succeeds, else
    /// FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode estimate(const SRef<SolAR::datastructure::Image> image,
                                         SRef<SolAR::datastructure::Image> & depthMap) = 0;
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::geom::IMonocularDepthEstimation,
                             "fc585010-1292-4d61-a2ef-d773def81b7f",
                             "IMonocularDepthEstimation",
                             "SolAR::api::geom::IMonocularDepthEstimation interface");

#endif // SOLAR_IMONOCULARDEPTHESTIMATION_H
