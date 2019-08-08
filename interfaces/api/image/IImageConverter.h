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

#ifndef SOLAR_IIMAGECONVERTER_H
#define SOLAR_IIMAGECONVERTER_H

// Definition of IImageConverter Class //
// part of Solar namespace //

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/Image.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace image {

/**
  * @class IImageConverter
  * @brief <B>Converts image with a specific layout.</B>
  * <TT>UUID: 9c982719-6cb4-4831-aa88-9e01afacbd16</TT>
  */
class  IImageConverter : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
   IImageConverter() = default;

   ///
   /// \brief ~IImageConverter
   ///
   virtual ~IImageConverter() {}
   /// @brief This method converts an image source to image destination according to image destination channel, color and depth representation  
   /// @param[in] imgSrc input image to convert
   /// @param[out] imgDst output image converted
   /// @return FrameworkReturnCode::_SUCCESS_ id conversion succeed, else FrameworkReturnCode::_ERROR.   
   virtual FrameworkReturnCode convert(const SRef<Image> imgSrc, SRef<Image> & imgDst) = 0;

   /// @brief This method converts an image source to image destination according to a given channel and color representation  layout
   /// @param[in] imgSrc input image to convert
   /// @param[out] imgDst output image converted
   /// @return FrameworkReturnCode::_SUCCESS_ id conversion succeed, else FrameworkReturnCode::_ERROR.   
   virtual FrameworkReturnCode convert(const SRef<Image> imgSrc, SRef<Image> & imgDst, Image::ImageLayout destLayout) = 0;

};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::image::IImageConverter,
                             "9c982719-6cb4-4831-aa88-9e01afacbd16",
                             "IImageConverter",
                             "SolAR::api::image::IImageConverter");

#endif //SOLAR_IIMAGECONVERTER_H
