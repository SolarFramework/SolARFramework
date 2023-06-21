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

#ifndef SOLAR_A2DPOINTSRECTIFICATION_H
#define SOLAR_A2DPOINTSRECTIFICATION_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "core/SolARFrameworkDefinitions.h"
#include <xpcf/component/ConfigurableBase.h>
#include "api/geom/I2DPointsRectification.h"

namespace SolAR {
namespace base {
namespace geom {

class XPCF_IGNORE SOLARFRAMEWORK_API A2DPointsRectification : public org::bcom::xpcf::ConfigurableBase,
                                            virtual public SolAR::api::geom::I2DPointsRectification {
public:
    /// @brief A2DPointsRectification constructor
    A2DPointsRectification(std::map<std::string,std::string> componentInfosMap);

    virtual ~A2DPointsRectification() override = default;

    /// @brief Rectify 2D points
    /// @param[in] points2D The input 2D points
    /// @param[in] camParams The camera parameters of camera
    /// @param[in] rectParams The rectification parameters of camera
    /// @param[out] rectifiedPoints2D The rectified 2D points
    /// @return FrameworkReturnCode::_SUCCESS if rectifying succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode rectify(const std::vector<SolAR::datastructure::Point2Df>& /*points2D*/,
                                        const SolAR::datastructure::CameraParameters& /*camParams*/,
                                        const SolAR::datastructure::RectificationParameters& /*rectParams*/,
                                        std::vector<SolAR::datastructure::Point2Df>& /*rectifiedPoints2D*/) override
    { return FrameworkReturnCode::_NOT_IMPLEMENTED; }

    /// @brief Rectify 2D keypoints
    /// @param[in] keypoints The input 2D keypoints
    /// @param[in] camParams The camera parameters of camera
    /// @param[in] rectParams The rectification parameters of camera
    /// @param[out] rectifiedKeypoints The rectified 2D keypoints
    /// @return FrameworkReturnCode::_SUCCESS if rectifying succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode rectify(const std::vector<SolAR::datastructure::Keypoint>& keypoints,
                                        const SolAR::datastructure::CameraParameters& camParams,
                                        const SolAR::datastructure::RectificationParameters& rectParams,
                                        std::vector<SolAR::datastructure::Keypoint>& rectifiedKeypoints) override;
};
}
}
}  // end of namespace SolAR


#endif // SOLAR_A2DPOINTSRECTIFICATION_H
