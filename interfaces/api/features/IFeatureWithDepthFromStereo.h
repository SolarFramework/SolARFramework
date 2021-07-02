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

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Frame.h"
#include "datastructure/Image.h"
#include "datastructure/StereoCameraDefinitions.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace features {

/** @class IFeatureWithDepthFromStereo
* @brief <B>Perform feature extraction and keypoint depth estimation from each stereo images.</B>
* <TT>UUID: 10853f36-c0c0-4afb-81b8-0b1a06ca4e71</TT>
*/
class  IFeatureWithDepthFromStereo : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IFeatureWithDepthFromStereo constructor
    IFeatureWithDepthFromStereo() = default;

    /// @brief ~IFeatureWithDepthFromStereo
    virtual ~IFeatureWithDepthFromStereo() {};

    /// @brief this method is used to set intrinsic parameters and distorsion of the camera
    /// @param[in] intrinsicParams Camera calibration matrix parameters.
    /// @param[in] distortionParams Camera distorsion parameters.
    virtual void setCameraParameters(const SolAR::datastructure::CamCalibration & intrinsicParams,
                                     const SolAR::datastructure::CamDistortion & distortionParams) = 0;

    /// @brief this method is used to set rectification parameters of the stereo camera
    /// @param[in] rectParams1 Rectification parameters of the first camera.
    /// @param[in] rectParams2 Rectification parameters of the second camera.
    virtual void setRectificationParameters(const SolAR::datastructure::RectificationParameters & rectParams1,
                                            const SolAR::datastructure::RectificationParameters & rectParams2) = 0;

    /// @brief Perform feature extraction and keypoint depth estimation
    /// @param[in] image1 The first image.
    /// @param[in] image2 The second image.
    /// @param[out] frame1 The first frame that contains features and estimated depths of the first image.
    /// @param[out] frame2 The second frame that contains features and estimated depths of the second image.
    virtual FrameworkReturnCode compute(SRef<SolAR::datastructure::Image> image1,
                                        SRef<SolAR::datastructure::Image> image2,
                                        SRef<SolAR::datastructure::Frame> &frame1,
                                        SRef<SolAR::datastructure::Frame> &frame2) = 0;
};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::stereo::IFeatureWithDepthFromStereo,
                            "10853f36-c0c0-4afb-81b8-0b1a06ca4e71",
                            "IFeatureWithDepthFromStereo",
                            "SolAR::api::features::IFeatureWithDepthFromStereo interface");

#endif // SOLAR_IFEATUREWITHDEPTHFROMSTEREO_H
