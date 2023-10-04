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


#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/Frame.h"

namespace SolAR {
namespace api {
namespace slam {

/**
* @class IBootstrapper
* @brief <B>Initialization SLAM using an image stream of a camera.</B>
* <TT>UUID: b0515c62-cc81-4600-835c-8acdfedf39b5</TT>
*/

class XPCF_CLIENTUUID("d593b615-efcf-4b4c-82eb-148065f85008") XPCF_SERVERUUID("a7509f5c-f214-408d-be3a-acb38dd8512b") IBootstrapper :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief IBootstrapper default constructor
	IBootstrapper() = default;

	/// @brief IBootstrapper default destructor
	virtual ~IBootstrapper() = default;

    /// @brief This method uses images to boostrap mapping
    /// @param[in] frame input image to process
    /// @param[out] view output image to visualize
    /// @return FrameworkReturnCode::_SUCCESS_ if initialization succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode process(const SRef<SolAR::datastructure::Frame>& frame,
                                        SRef<SolAR::datastructure::Image> & view) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::slam::IBootstrapper,
	"b0515c62-cc81-4600-835c-8acdfedf39b5",
	"IBootstrapper",
	"SolAR::api::slam::IBootstrapper");


#endif //SOLAR_IBOOTSTRAPPER_H

