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

#ifndef SOLAR_ISTEREOCAMERACALIBRATION_H
#define SOLAR_ISTEREOCAMERACALIBRATION_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/CameraDefinitions.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace input {
namespace devices {

/** @class IStereoCameraCalibration
* @brief <B>Calibrate and rectify a stereo camera.</B>
* <TT>UUID: b4fad0ff-c636-492e-ba12-710927a760c7</TT>
*/
class XPCF_CLIENTUUID("f2cec917-6793-4aef-90cb-fd3f843fb43e") XPCF_SERVERUUID("d8ac896d-772d-4ce1-b7be-a8f08020eeb6") IStereoCameraCalibration :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief IStereoCameraCalibration constructor
	IStereoCameraCalibration() = default;

	/// @brief ~IStereoCameraCalibration
    virtual ~IStereoCameraCalibration() = default;

	/// @brief Calibrate a stereo camera from a set of captured images and output the result in the given file
	/// @param[in] images1 Set of images from the first camera
	/// @param[in] images2 Set of images from the second camera
	/// @param[in] camParams1 Camera parameters of the first camera
	/// @param[in] camParams2 Camera parameters of the second camera
	/// @param[out] transformation Transformation matrix from the frist camera to the second camera
	/// @param[out] rectParams1 Rectification parameters of the first camera
	/// @param[out] rectParams2 Rectification parameters of the second camera
	/// @return FrameworkReturnCode::_SUCCESS if calibration succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode calibrate(const std::vector<SRef<SolAR::datastructure::Image>>& images1,
                                          const std::vector<SRef<SolAR::datastructure::Image>>& images2,
                                          const SolAR::datastructure::CameraParameters & camParams1,
                                          const SolAR::datastructure::CameraParameters & camParams2,
                                          SolAR::datastructure::Transform3Df & transformation,
                                          SolAR::datastructure::RectificationParameters & rectParams1,
                                          SolAR::datastructure::RectificationParameters & rectParams2) = 0;
};

}
}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::devices::IStereoCameraCalibration,
                             "b4fad0ff-c636-492e-ba12-710927a760c7",
                             "IStereoCameraCalibration",
                             "SolAR::api::input::devices::IStereoCameraCalibration interface");

#endif // SOLAR_ISTEREOCAMERACALIBRATION_H
