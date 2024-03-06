/**
 * @copyright Copyright (c) 2024 B-com http://www.b-com.com/
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

#ifndef SOLAR_IIMAGEMERGER_H
#define SOLAR_IIMAGEMERGER_H

// Definition of IImageMerger Class //
// part of Solar namespace //

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/Image.h"

namespace SolAR {
namespace api {
namespace image {

/**
  * @class IImageMerger
  * @brief <B>Merges a set of images in a single one.</B>
  * <TT>UUID: c4de4c55-a71d-4a04-afac-4e601c6e9b9a</TT>
  */
class XPCF_IGNORE IImageMerger :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    IImageMerger() = default;
	///
    /// \brief ~IImageMerger
	///
    virtual ~IImageMerger() {};
     
    /// @brief This method merge a set og images into a single one
    /// @param[in] imgSrc: the set of images
    /// @param[out] imgDst: the image resulting of the merge of the input images.
    /// @return FrameworkReturnCode::_SUCCESS_ id merge succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode merge(const std::vector<SRef<SolAR::datastructure::Image>>& imgSrc, SRef<SolAR::datastructure::Image>& imgDst) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::image::IImageMerger,
                             "c4de4c55-a71d-4a04-afac-4e601c6e9b9a",
                             "IImageMerger",
                             "SolAR::api::image::IImageMerger");

#endif //SOLAR_IIMAGECONVERTOR_H
