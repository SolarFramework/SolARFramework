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

#ifndef I3DGSVIEWER_H
#define I3DGSVIEWER_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace display {
/**
 * @class I3DGSViewer
 * @brief <B>Displays 3D Gaussian Splatting in a window.</B>
 * <TT>UUID: cc63d296-3662-480f-a012-b4f10c3527b3</TT>
 *
 * This class provides a viewer to display points cloud in a window.
 */
class XPCF_IGNORE I3DGSViewer :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief I3DGSViewer default constructor
    I3DGSViewer() = default;

    /// @brief I3DGSViewer default destructor
    virtual ~I3DGSViewer() = default;

    /// @brief Display a set of 3D Gaussians rendered as ellipsoid splats in a window.
    /// The data is passed as flat, contiguous, libtorch-free float buffers so that
    /// implementers (e.g. an OpenGL viewer) need no tensor library dependency.
    /// The viewer is expected to own its interactive (orbit) camera, hence no pose is required.
    /// @param[in] centers flat array of Gaussian centers, size 3*N (x,y,z per Gaussian).
    /// @param[in] scales flat array of per-axis scales, size 3*N (sx,sy,sz per Gaussian).
    /// @param[in] quaternions flat array of rotation quaternions, size 4*N (w,x,y,z per Gaussian).
    /// @param[in] colors flat array of RGB colors in [0,1], size 3*N (r,g,b per Gaussian).
    /// @param[in] opacities array of opacities in [0,1], size N.
    /// @return FrameworkReturnCode::_SUCCESS if displayed, FrameworkReturnCode::_NOT_IMPLEMENTED
    /// if the implementer does not support Gaussian display, else FrameworkReturnCode::_ERROR_.
    virtual FrameworkReturnCode displayGaussians(const std::vector<float> & centers,
                                                 const std::vector<float> & scales,
                                                 const std::vector<float> & quaternions,
                                                 const std::vector<float> & colors,
                                                 const std::vector<float> & opacities) final
    {
        return displayGaussians(centers, scales, quaternions, colors, opacities, {}, 0);
    }

    /// @brief Display 3D Gaussians with view-dependent colour (spherical harmonics).
    /// Same as displayGaussians() above, plus the higher-order SH coefficients so the
    /// viewer can evaluate view-dependent colour per frame (degree 0 = DC is in @p colors).
    /// @param[in] centers size 3*N. @param[in] scales size 3*N. @param[in] quaternions size 4*N.
    /// @param[in] colors DC RGB base in [0,1], size 3*N.  @param[in] opacities size N.
    /// @param[in] shCoeffsRest higher-order SH coefficients, size N*3*K with K = coeffs per
    /// channel for the degree (deg1=3, deg2=8, deg3=15); per Gaussian channel-major
    /// [R(K) G(K) B(K)] (Inria/PLY f_rest order).
    /// @param[in] shDegree SH degree of the rest coefficients (1, 2 or 3).
    /// @return _SUCCESS, _NOT_IMPLEMENTED, or _ERROR_.
    virtual FrameworkReturnCode displayGaussians(const std::vector<float> & centers,
                                                 const std::vector<float> & scales,
                                                 const std::vector<float> & quaternions,
                                                 const std::vector<float> & colors,
                                                 const std::vector<float> & opacities,
                                                 const std::vector<float> & shCoeffsRest,
                                                 int shDegree) = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::display::I3DGSViewer,
                             "cc63d296-3662-480f-a012-b4f10c3527b3",
                             "I3DGSViewer",
                             "SolAR::api::display::I3DGSViewer interface")

#endif // I3DGSVIEWER_H
