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

#ifndef SOLAR_IBOOTSTRAPPER_H
#define SOLAR_IBOOTSTRAPPER_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"

namespace SolAR {
namespace api {
namespace slam {

/**
* @class IBootstrapper
* @brief <B>Initialization SLAM using an image stream of a camera.</B>
* <TT>UUID: b0515c62-cc81-4600-835c-8acdfedf39b5</TT>
*/

class IBootstrapper : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief IBootstrapper default constructor
	IBootstrapper() = default;

	/// @brief IBootstrapper default destructor
	virtual ~IBootstrapper() = default;

	/// @brief this method is used to set intrinsic parameters and distorsion of the camera
	/// @param[in] intrinsicParams camera calibration matrix parameters.
	/// @param[in] distortionParams camera distorsion parameters.
	virtual void setCameraParameters(const SolAR::datastructure::CamCalibration & intrinsicParams, const SolAR::datastructure::CamDistortion & distortionParams) = 0;

	/// @brief This method uses images to boostrap
	/// @param[in] image: input image to process
	/// @param[out] view: output image to visualize
	/// @param[in] pose: the pose of the input image
	/// @return FrameworkReturnCode::_SUCCESS_ if initialization succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode process(const SRef<SolAR::datastructure::Image> image, SRef<SolAR::datastructure::Image> & view, const SolAR::datastructure::Transform3Df & pose = SolAR::datastructure::Transform3Df::Identity()) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::slam::IBootstrapper,
	"b0515c62-cc81-4600-835c-8acdfedf39b5",
	"IBootstrapper",
	"SolAR::api::slam::IBootstrapper");


#endif //SOLAR_IBOOTSTRAPPER_H

