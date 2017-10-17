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

#ifndef ISOLARIMAGECONVERTOR_H
#define ISOLARIMAGECONVERTOR_H

// Definition of ISolARImageConvertor Class //
// part of Solar namespace //

#include "IComponentIntrospect.h"
#include "SolARImage.h"


namespace SolAR {


///
/// \brief The ISolARImageConvertor class
///
class  ISolARImageConvertor : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
   ISolARImageConvertor() = default;

   ///
   /// \brief ~ISolARImageConvertor
   ///
   virtual ~ISolARImageConvertor() {};
   virtual int convert(SRef<SolARImage> imgSrc, SRef<SolARImage> imgDst) = 0;
   virtual int convert(SRef<SolARImage> imgSrc, SRef<SolARImage> imgDst, SolARImage::ImageLayout destLayout) = 0;

   XPCF_DECLARE_UUID("9c982719-6cb4-4831-aa88-9e01afacbd16");
};

}

#endif
