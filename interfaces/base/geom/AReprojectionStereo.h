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

#ifndef SOLAR_AREPROJECTIONSTEREO_H
#define SOLAR_AREPROJECTIONSTEREO_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "core/SolARFrameworkDefinitions.h"
#include <xpcf/component/ConfigurableBase.h>
#include "api/geom/IReprojectionStereo.h"

namespace SolAR {
namespace base {
namespace geom {

class XPCF_IGNORE SOLARFRAMEWORK_API AReprojectionStereo : public org::bcom::xpcf::ConfigurableBase,
                                            virtual public SolAR::api::geom::IReprojectionStereo {
public:
    /// @brief AReprojectionStereo constructor
    AReprojectionStereo(std::map<std::string,std::string> componentInfosMap);

    virtual ~AReprojectionStereo() override = default;

    /// @brief Reproject depth of rectified keypoints to unrectified keypoints
    /// @param[in] rectifiedKeypoints The rectified keypoints containing depth information.
    /// @param[in] rectParams The rectification parameters.
    /// @param[out] unrectifiedKeypoints The unrectified keypoints for estimating depth information.
    /// @return FrameworkReturnCode::_SUCCESS if reprojecting succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode reprojectToUnrectification(const std::vector<SolAR::datastructure::Keypoint>& /*rectifiedKeypoints*/,
                                                           const SolAR::datastructure::RectificationParameters& /*rectParams*/,
                                                           std::vector<SolAR::datastructure::Keypoint>& /*unrectifiedKeypoints*/) override
    { return FrameworkReturnCode::_NOT_IMPLEMENTED; }

    /// @brief Reproject 2D keypoints with depths to 3D cloud points in the world coordinate system
    /// @param[in] undistortedKeypoints The undistorted keypoints of image.
    /// @param[in] descriptors The descriptors corresponding to the keypoints.
    /// @param[in] pose The pose of image.
    /// @param[in] intrinsicParams The intrinsic parameters of the camera.
    /// @param[out] cloudPoints The output cloud points.
    /// @return FrameworkReturnCode::_SUCCESS if reprojecting succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode reprojectToCloudPoints(const std::vector<SolAR::datastructure::Keypoint>& /*undistortedKeypoints*/,
                                                       const SRef<SolAR::datastructure::DescriptorBuffer> /*descriptors*/,
                                                       const SolAR::datastructure::Transform3Df& /*pose*/,
                                                       const SolAR::datastructure::CamCalibration& /*intrinsicParams*/,
                                                       std::vector<SRef<SolAR::datastructure::CloudPoint>>& /*cloudPoints*/) override
    { return FrameworkReturnCode::_NOT_IMPLEMENTED; }

    /// @brief Reproject 2D keypoints with depths of a frame to 3D cloud points in the world coordinate system
    /// @param[in] frame The frame including keypoints with their depth estimations.
    /// @param[in] intrinsicParams The intrinsic parameters of the camera.
    /// @param[out] cloudPoints The output cloud points.
    /// @return FrameworkReturnCode::_SUCCESS if reprojecting succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode reprojectToCloudPoints(SRef<SolAR::datastructure::Frame> frame,
                                                       const SolAR::datastructure::CamCalibration& intrinsicParams,
                                                       std::vector<SRef<SolAR::datastructure::CloudPoint>>& cloudPoints) override;
};
}
}
}  // end of namespace SolAR


#endif // SOLAR_AREPROJECTIONSTEREO_H
