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

#ifndef SOLAR_IREPROJECTIONSTEREO_H
#define SOLAR_IREPROJECTIONSTEREO_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Keypoint.h"
#include "datastructure/Frame.h"
#include "datastructure/CloudPoint.h"
#include "datastructure/StereoCameraDefinitions.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace geom {

/** @class IReprojectionStereo
* @brief <B>Reproject keypoints with estimating depth to 3D cloud points.</B>
* <TT>UUID: 166a0aad-8c0a-4cdc-9edf-41ff9e514212</TT>
*/
class  IReprojectionStereo : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IReprojectionStereo constructor
    IReprojectionStereo() = default;

    /// @brief ~IReprojectionStereo
    virtual ~IReprojectionStereo() = default;

    /// @brief Reproject depth of rectified keypoints to unrectified keypoints
    /// @param[in] rectifiedKeypoints The rectified keypoints containing depth information.
    /// @param[in] rectParams The rectification parameters.
    /// @param[out] unrectifiedKeypoints The unrectified keypoints for estimating depth information.
    /// @return FrameworkReturnCode::_SUCCESS if reprojecting succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode reprojectToUnrectification(const std::vector<SolAR::datastructure::Keypoint>& rectifiedKeypoints,
                                                           const SolAR::datastructure::RectificationParameters& rectParams,
                                                           std::vector<SolAR::datastructure::Keypoint>& unrectifiedKeypoints) = 0;

    /// @brief Reproject 2D keypoints with depths of a frame to 3D cloud points in the world coordinate system
    /// @param[in] frame The frame.
    /// @param[in] intrinsicParams The intrinsic parameters of the camera.
    /// @param[out] cloudPoints The output cloud points.
    /// @return FrameworkReturnCode::_SUCCESS if reprojecting succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode reprojectToCloudPoints(SRef<SolAR::datastructure::Frame> frame,
                                                       const SolAR::datastructure::CamCalibration& intrinsicParams,
                                                       std::vector<SRef<SolAR::datastructure::CloudPoint>>& cloudPoints) = 0;
};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::stereo::IReprojectionStereo,
                            "166a0aad-8c0a-4cdc-9edf-41ff9e514212",
                            "IReprojectionStereo",
                            "SolAR::api::stereo::IReprojectionStereo interface");

#endif // SOLAR_IREPROJECTIONSTEREO_H
