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

#ifndef SOLAR_ICAMERACALIBRATION_H
#define SOLAR_ICAMERACALIBRATION_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/CameraDefinitions.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace input {
namespace devices {

/** @class ICameraCalibration
  * @brief <B>Calibrates a camera.</B>
  * <TT>UUID: 0e83b228-b9ca-413d-9dc2-db45c427428b</TT>
  */
class  ICameraCalibration : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief ~ICameraCalibration
    /// ICameraCalibration() = default;

	/// @brief ~ICameraCalibration
	virtual ~ICameraCalibration() {};

    /// @brief Calibrate the camera device from a sequence of images
    /// @param[in] images The set of images for calibration
    /// @param[out] camParams The camera paramters
    /// @return FrameworkReturnCode::_SUCCESS if calibration succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode calibrate(const std::vector<SRef<SolAR::datastructure::Image>>& images,
                                          SolAR::datastructure::CameraParameters & camParams) = 0;
};

}
}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::devices::ICameraCalibration,
                             "0e83b228-b9ca-413d-9dc2-db45c427428b",
                             "ICameraCalibration",
                             "SolAR::api::input::devices::ICameraCalibration interface");

#endif // SOLAR_ICAMERACALIBRATION_H
