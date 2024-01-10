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

#ifndef SOLAR_I2DPOINTSRECTIFICATION_H
#define SOLAR_I2DPOINTSRECTIFICATION_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "datastructure/Image.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Keypoint.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace geom {

/** @class I2DPointsRectification
* @brief <B>Rectify 2D points.</B>
* <TT>UUID: 188e9e9c-6d73-4495-9d9f-3bc5d35c4b43</TT>
* Just implement the first interface, the second interface is implemented in A2DPointsRectification.
*/
class XPCF_CLIENTUUID("7ec39cd6-c0e1-4b4d-a064-e42e56fc258b") XPCF_SERVERUUID("e02ef0d2-b3b1-4a2d-b088-f236b9447fed") I2DPointsRectification :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief I2DPointsRectification constructor
    I2DPointsRectification() = default;

    /// @brief ~I2DPointsRectification
    virtual ~I2DPointsRectification() = default;

	/// @brief Rectify 2D points
	/// @param[in] points2D The input 2D points
    /// @param[in] camParams The camera parameters of camera
	/// @param[in] rectParams The rectification parameters of camera
	/// @param[out] rectifiedPoints2D The rectified 2D points
	/// @return FrameworkReturnCode::_SUCCESS if rectifying succeed, else FrameworkReturnCode::_ERROR_
	virtual FrameworkReturnCode rectify(const std::vector<SolAR::datastructure::Point2Df>& points2D,
                                        const SolAR::datastructure::CameraParameters& camParams,
										const SolAR::datastructure::RectificationParameters& rectParams,
										std::vector<SolAR::datastructure::Point2Df>& rectifiedPoints2D) = 0;

	/// @brief Rectify 2D keypoints
	/// @param[in] keypoints The input 2D keypoints
    /// @param[in] camParams The camera parameters of camera
	/// @param[in] rectParams The rectification parameters of camera
	/// @param[out] rectifiedKeypoints The rectified 2D keypoints
	/// @return FrameworkReturnCode::_SUCCESS if rectifying succeed, else FrameworkReturnCode::_ERROR_
	virtual FrameworkReturnCode rectify(const std::vector<SolAR::datastructure::Keypoint>& keypoints,
                                        const SolAR::datastructure::CameraParameters& camParams,
										const SolAR::datastructure::RectificationParameters& rectParams,
										std::vector<SolAR::datastructure::Keypoint>& rectifiedKeypoints) = 0;
};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::geom::I2DPointsRectification,
							"188e9e9c-6d73-4495-9d9f-3bc5d35c4b43",
                            "I2DPointsRectification",
                            "SolAR::api::geom::I2DPointsRectification interface");

#endif // SOLAR_I2DPOINTSRECTIFICATION_H
