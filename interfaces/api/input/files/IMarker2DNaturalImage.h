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

#ifndef IMARKER2DNATURALIMAGE_H
#define IMARKER2DNATURALIMAGE_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "core/Messages.h"
#include "datastructure/Image.h"

#include "IMarker2DSquared.h"
#include "xpcf/api/IComponentIntrospect.h"


namespace SolAR {
using namespace datastructure;
namespace api {
namespace input {
namespace files {

//!  The abstract class defining all 2D Natural Image markers representing any image
/*!
  The origin of the marker is positionned at its center. The x-axis points to the right of the marker, the y-axis points to the top of the marker, and the z-axis points frontward.
*/
/**
 * @class IMarker2DNaturalImage
 * @brief Specifies the IMarker2DNaturalImage interface class.
 */
class IMarker2DNaturalImage : public virtual IMarker2DSquared {

public:

    IMarker2DNaturalImage() = default;
     virtual ~IMarker2DNaturalImage() = default;

    ///
    /// \brief get access to the image of the 2D natural marker
    /// \param img: a shared reference to the image
    virtual FrameworkReturnCode getImage(SRef<Image> & img) = 0;


};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::files::IMarker2DNaturalImage,
                             "8fed06f8-c54d-11e7-abc4-cec278b6b50a",
                             "IMarker2DNaturalImage",
                             "SolAR::api::input::files::IMarker2DNaturalImage interface");

#endif

