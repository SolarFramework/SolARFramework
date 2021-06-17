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

#ifndef SOLAR_ISTEREORECTIFICATION_H
#define SOLAR_ISTEREORECTIFICATION_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Keypoint.h"
#include "datastructure/StereoCameraDefinitions.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace stereo {

/** @class IStereoRectification
* @brief <B>Rectiy image or 2D points.</B>
* <TT>UUID: 188e9e9c-6d73-4495-9d9f-3bc5d35c4b43</TT>
*/
class  IStereoRectification : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief IStereoRectification constructor
	IStereoRectification() = default;

	/// @brief ~IStereoRectification
	virtual ~IStereoRectification() {};

	/// @brief Rectify image
	/// @param[in] image The input image
	/// @param[out] rectifiedImage The rectified image
	/// @param[in] indexCamera The index of camera
	virtual void rectify(SRef<SolAR::datastructure::Image> image, 
						SRef<SolAR::datastructure::Image>& rectifiedImage,
						int indexCamera) = 0;

	/// @brief Rectify 2D points
	/// @param[in] points2D The input 2D points
	/// @param[out] rectifiedPoints2D The rectified 2D points
	/// @param[in] indexCamera The index of camera
	virtual void rectify(const std::vector<SolAR::datastructure::Point2Df>& points2D,
						std::vector<SolAR::datastructure::Point2Df>& rectifiedPoints2D,
						int indexCamera) = 0;

	/// @brief Rectify 2D keypoints
	/// @param[in] keypoints The input 2D keypoints
	/// @param[out] rectifiedKeypoints The rectified 2D keypoints
	/// @param[in] indexCamera The index of camera
	virtual void rectify(const std::vector<SolAR::datastructure::Keypoint>& keypoints,
						std::vector<SolAR::datastructure::Keypoint>& rectifiedKeypoints,
						int indexCamera) = 0;

	/// @brief Get stereo camera type
	/// @return stereo type
	virtual SolAR::datastructure::StereoType getType() = 0;

	/// @brief Get baseline distance
	/// @return baseline distance
	virtual float getBaseline() = 0;

	/// @brief Get rectification parameters
	/// @param[in] indexCamera Index of camera
	/// @return rectification parameters
	virtual SolAR::datastructure::RectificationParameters getRectificationParamters(int indexCamera) = 0;
};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::stereo::IStereoRectification,
							"188e9e9c-6d73-4495-9d9f-3bc5d35c4b43",
							"IStereoRectification",
							"SolAR::api::stereo::IStereoRectification interface");

#endif // SOLAR_ISTEREORECTIFICATION_H
