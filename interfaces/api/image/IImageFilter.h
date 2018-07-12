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

#ifndef SOLAR_IIMAGEFILTER_H
#define SOLAR_IIMAGEFILTER_H

#include "IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/Image.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace image {

class IImageFilter : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    IImageFilter() = default;
    virtual ~IImageFilter() = default;

    virtual FrameworkReturnCode filter(const SRef<Image>input, SRef<Image>& output) = 0;

};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::image::IImageFilter,
                             "f7948ae2-e994-416f-be40-dd404ca03a83",
                             "SolAR::api::image::IImageFilter");


#endif // SOLAR_IIMAGEFILTER_H
