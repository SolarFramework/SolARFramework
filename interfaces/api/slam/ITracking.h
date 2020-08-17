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

#ifndef SOLAR_ITRACKING_H
#define SOLAR_ITRACKING_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Keyframe.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace slam {

/**
* @class ITracking
* @brief <B> SLAM tracking task.</B>
* <TT>UUID: c2182b8e-03e9-43a3-a5b9-326e80554cf8</TT>
*/

class ITracking : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief ITracking default constructor
	ITracking() = default;

	/// @brief IBootstrapper default destructor
	virtual ~ITracking() = default;

	/// @brief this method is used to set intrinsic parameters and distorsion of the camera
	/// @param[in] Camera calibration matrix parameters.
	/// @param[in] Camera distorsion parameters.
	virtual void setCameraParameters(const CamCalibration & intrinsicParams, const CamDistortion & distorsionParams) = 0;

	/// @brief this method is used to update reference keyframe to track
	/// @param[in] refKeyframe: the new reference keyframe.
	virtual void updateReferenceKeyframe(const SRef<Keyframe> & refKeyframe) = 0;
	
	/// @brief this method is used to process tracking
	/// @param[in] frame: the input frame.
	/// @param[out] displayImage: the image to display.
	/// @return FrameworkReturnCode::_SUCCESS if tracking succeed, else FrameworkReturnCode::_ERROR_
	virtual FrameworkReturnCode process(const SRef<Frame> & frame, SRef<Image> &displayImage) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::slam::ITracking,
	"c2182b8e-03e9-43a3-a5b9-326e80554cf8",
	"ITracking",
	"SolAR::api::slam::ITracking");


#endif //SOLAR_ITRACKING_H

