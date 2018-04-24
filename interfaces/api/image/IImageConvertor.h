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

#ifndef SOLAR_IIMAGECONVERTOR_H
#define SOLAR_IIMAGECONVERTOR_H

// Definition of IImageConvertor Class //
// part of Solar namespace //

#include "IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/Image.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace image {

///
/// \brief The IImageConvertor class
///
class  IImageConvertor : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
   IImageConvertor() = default;

   ///
   /// \brief ~IImageConvertor
   ///
   virtual ~IImageConvertor() {};
   virtual FrameworkReturnCode convert(SRef<Image> imgSrc, SRef<Image>& imgDst) = 0;
   virtual FrameworkReturnCode convert(SRef<Image> imgSrc, SRef<Image>& imgDst, Image::ImageLayout destLayout) = 0;

};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::image::IImageConvertor,
                             "9c982719-6cb4-4831-aa88-9e01afacbd16",
                             "SolAR::api::image::IImageConvertor");

#endif //SOLAR_IIMAGECONVERTOR_H
