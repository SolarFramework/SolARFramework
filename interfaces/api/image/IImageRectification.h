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

#ifndef SOLAR_IIMAGERECTIFICATION_H
#define SOLAR_IIMAGERECTIFICATION_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "datastructure/Image.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Keypoint.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace image {

/** @class IImageRectification
* @brief <B>Rectify image.</B>
* <TT>UUID: f3e2cdb3-1818-4316-b536-a35650c59811</TT>
*/
class XPCF_IGNORE IImageRectification :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IImageRectification constructor
    IImageRectification() = default;

    /// @brief ~IImageRectification
    virtual ~IImageRectification() = default;

	/// @brief Rectify image
	/// @param[in] image The input image
	/// @param[in] camParams The camera parameters of camera
	/// @param[in] rectParams The rectification parameters of camera
	/// @param[out] rectifiedImage The rectified image	
	/// @return FrameworkReturnCode::_SUCCESS if rectifying succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode rectify(SRef<SolAR::datastructure::Image> image,
                                        const SolAR::datastructure::CameraParameters& camParams,
										const SolAR::datastructure::RectificationParameters& rectParams,
										SRef<SolAR::datastructure::Image>& rectifiedImage) = 0;	
};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::image::IImageRectification,
                            "f3e2cdb3-1818-4316-b536-a35650c59811",
                            "IImageRectification",
                            "SolAR::api::image::IImageRectification interface");

#endif // SOLAR_IIMAGERECTIFICATION_H
