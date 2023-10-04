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

#ifndef SOLAR_IFEATUREWITHDEPTHFROMSTEREO_H
#define SOLAR_IFEATUREWITHDEPTHFROMSTEREO_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Frame.h"
#include "datastructure/Image.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace features {

/** @class IFeatureWithDepthFromStereo
* @brief <B>Perform feature extraction and keypoint depth estimation from each stereo images.</B>
* <TT>UUID: 10853f36-c0c0-4afb-81b8-0b1a06ca4e71</TT>
*/
class XPCF_CLIENTUUID("23c6b83f-d6a2-415b-a7ba-21556d28cad9") XPCF_SERVERUUID("a5a81922-7bac-44b1-a561-9c7b83a07589") IFeatureWithDepthFromStereo :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IFeatureWithDepthFromStereo constructor
    IFeatureWithDepthFromStereo() = default;

    /// @brief ~IFeatureWithDepthFromStereo
    virtual ~IFeatureWithDepthFromStereo() {};

    /// @brief this method is used to set rectification parameters of the stereo camera
    /// @param[in] camParams1 Camera parameters of the first camera.
    /// @param[in] camParams2 Camera parameters of the second camera.
    /// @param[in] rectParams1 Rectification parameters of the first camera.
    /// @param[in] rectParams2 Rectification parameters of the second camera.
    virtual void setRectificationParameters(const SolAR::datastructure::CameraParameters& camParams1,
                                            const SolAR::datastructure::CameraParameters& camParams2,
                                            const SolAR::datastructure::RectificationParameters & rectParams1,
                                            const SolAR::datastructure::RectificationParameters & rectParams2) = 0;

    /// @brief Perform feature extraction and keypoint depth estimation
    /// @param[in] image1 The first image.
    /// @param[in] image2 The second image.
    /// @param[out] frame1 The first frame that contains features and estimated depths of the first image.
    /// @param[out] frame2 The second frame that contains features and estimated depths of the second image.
    /// /// @return FrameworkReturnCode::_SUCCESS if computing succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode compute(SRef<SolAR::datastructure::Image> image1,
                                        SRef<SolAR::datastructure::Image> image2,
                                        SRef<SolAR::datastructure::Frame> &frame1,
                                        SRef<SolAR::datastructure::Frame> &frame2) = 0;
};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IFeatureWithDepthFromStereo,
                            "10853f36-c0c0-4afb-81b8-0b1a06ca4e71",
                            "IFeatureWithDepthFromStereo",
                            "SolAR::api::features::IFeatureWithDepthFromStereo interface");

#endif // SOLAR_IFEATUREWITHDEPTHFROMSTEREO_H
