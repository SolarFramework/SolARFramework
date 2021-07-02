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

#ifndef SOLAR_IBOOTSTRAPPERSTEREO_H
#define SOLAR_IBOOTSTRAPPERSTEREO_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Frame.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace slam {

/** @class IBootstrapperStereo
* @brief <B>Perform mapping bootstrapper using stereo camera.</B>
* <TT>UUID: 4d868108-795f-4bc4-90d2-a9bea24ed6c5</TT>
*/
class  IBootstrapperStereo : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IBootstrapperStereo constructor
    IBootstrapperStereo() = default;

    /// @brief ~IBootstrapperStereo
    virtual ~IBootstrapperStereo() = default;

	/// @brief this method is used to set intrinsic parameters of the camera
	/// @param[in] intrinsicParams camera calibration matrix parameters.
	virtual void setCameraParameters(const SolAR::datastructure::CamCalibration & intrinsicParams) = 0;

    /// @brief This method uses images to boostrap mapping using a stereo camera
	/// @param[in] frame input image to process
	/// @param[out] view output image to visualize
	/// @return FrameworkReturnCode::_SUCCESS_ if initialization succeed, else FrameworkReturnCode::_ERROR.
	virtual FrameworkReturnCode process(const SRef<SolAR::datastructure::Frame>& frame, 
										SRef<SolAR::datastructure::Image> & view) = 0;
};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::stereo::IBootstrapperStereo,
							"4d868108-795f-4bc4-90d2-a9bea24ed6c5",
                            "IBootstrapperStereo",
                            "SolAR::api::slam::IBootstrapperStereo interface");

#endif // SOLAR_IBOOTSTRAPPERSTEREO_H
