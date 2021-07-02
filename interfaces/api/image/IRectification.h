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

#ifndef SOLAR_IRECTIFICATION_H
#define SOLAR_IRECTIFICATION_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Keypoint.h"
#include "datastructure/StereoCameraDefinitions.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace image {

/** @class IRectification
* @brief <B>Rectiy image or 2D points.</B>
* <TT>UUID: 188e9e9c-6d73-4495-9d9f-3bc5d35c4b43</TT>
*/
class  IRectification : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief IRectification constructor
	IRectification() = default;

	/// @brief ~IRectification
    virtual ~IRectification() = default;

	/// @brief Rectify image
	/// @param[in] image The input image
	/// @param[in] rectParams The rectification parameters of camera
	/// @param[out] rectifiedImage The rectified image	
	/// @return FrameworkReturnCode::_SUCCESS if rectifying succeed, else FrameworkReturnCode::_ERROR_
	virtual FrameworkReturnCode rectify(SRef<SolAR::datastructure::Image> image, 
										const SolAR::datastructure::RectificationParameters& rectParams,
										SRef<SolAR::datastructure::Image>& rectifiedImage) = 0;

	/// @brief Rectify 2D points
	/// @param[in] points2D The input 2D points
	/// @param[in] rectParams The rectification parameters of camera
	/// @param[out] rectifiedPoints2D The rectified 2D points
	/// @return FrameworkReturnCode::_SUCCESS if rectifying succeed, else FrameworkReturnCode::_ERROR_
	virtual FrameworkReturnCode rectify(const std::vector<SolAR::datastructure::Point2Df>& points2D,
										const SolAR::datastructure::RectificationParameters& rectParams,
										std::vector<SolAR::datastructure::Point2Df>& rectifiedPoints2D) = 0;

	/// @brief Rectify 2D keypoints
	/// @param[in] keypoints The input 2D keypoints
	/// @param[in] rectParams The rectification parameters of camera
	/// @param[out] rectifiedKeypoints The rectified 2D keypoints
	/// @return FrameworkReturnCode::_SUCCESS if rectifying succeed, else FrameworkReturnCode::_ERROR_
	virtual FrameworkReturnCode rectify(const std::vector<SolAR::datastructure::Keypoint>& keypoints,
										const SolAR::datastructure::RectificationParameters& rectParams,
										std::vector<SolAR::datastructure::Keypoint>& rectifiedKeypoints) = 0;
};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::stereo::IRectification,
							"188e9e9c-6d73-4495-9d9f-3bc5d35c4b43",
							"IRectification",
                            "SolAR::api::image::IRectification interface");

#endif // SOLAR_IRECTIFICATION_H
