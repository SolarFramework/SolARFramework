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

#ifndef SOLAR_IMAPPING_H
#define SOLAR_IMAPPING_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Keyframe.h"

namespace SolAR {
namespace api {
namespace slam {

/**
* @class IMapping
* @brief <B> SLAM mapping.</B>
* <TT>UUID: 33db5a56-9be2-4e5a-8fdc-de25e1633cf6</TT>
*/

class IMapping : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief IMapping default constructor
	IMapping() = default;

	/// @brief IMapping default destructor
	virtual ~IMapping() = default;

	/// @brief this method is used to set intrinsic parameters and distorsion of the camera
	/// @param[in] Camera calibration matrix parameters.
	/// @param[in] Camera distorsion parameters.
	virtual void setCameraParameters(const datastructure::CamCalibration & intrinsicParams, const datastructure::CamDistortion & distorsionParams) = 0;

	/// @brief this method is used to process mapping task.
	/// @param[in] frame: the input frame.
    /// @param[out] keyframe: new keyframe or new reference keyframe found.
    virtual FrameworkReturnCode process(const SRef<datastructure::Frame> frame, SRef<datastructure::Keyframe> & keyframe) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::slam::IMapping,
	"33db5a56-9be2-4e5a-8fdc-de25e1633cf6",
	"IMapping",
	"SolAR::api::slam::IMapping");


#endif //SOLAR_IMAPPING_H

