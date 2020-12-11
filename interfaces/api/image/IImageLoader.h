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

#ifndef SOLAR_IIMAGELOADER_H
#define SOLAR_IIMAGELOADER_H

#include "xpcf/api/IComponentIntrospect.h"

#include "core/Messages.h"
#include "datastructure/Image.h"

namespace SolAR {
namespace api {
namespace image {

/**
  * @class IImageLoader
  * @brief <B>Loads an image.</B>
  * <TT>UUID: 6fcdaa8d-6ea9-4c3f-97b0-46cd11b67a9b</TT>
  *
  */
class IImageLoader : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    virtual ~IImageLoader() = default;
    ///
    /// \brief getImage method returns the image previously loaded
    ///
    virtual FrameworkReturnCode getImage(SRef<datastructure::Image> & img) = 0;

    ///
    /// \brief reloadImage method load a image if its path (set as a configuration parameter of the implemented component) has changed
    ///
    virtual FrameworkReturnCode reloadImage() = 0;

};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::image::IImageLoader,
                             "6fcdaa8d-6ea9-4c3f-97b0-46cd11b67a9b",
                             "IImageLoader",
                             "SolAR::IImageLoader interface");

#endif // SOLAR_IIMAGELOADER_H
