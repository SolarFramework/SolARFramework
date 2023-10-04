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

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/Image.h"

namespace SolAR {
namespace api {
namespace image {

/**
  * @class IImageConvertor
  * @brief <B>Converts image with a specific layout.</B>
  * <TT>UUID: 9c982719-6cb4-4831-aa88-9e01afacbd16</TT>
  */
class XPCF_CLIENTUUID("1977563c-c43f-4e5f-8df2-464d162889c3") XPCF_SERVERUUID("36458944-2986-49be-8ebf-55f2d12cc9dc") IImageConvertor :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	IImageConvertor() = default;
	///
	/// \brief ~IImageConvertor
	///
	virtual ~IImageConvertor() {};
     
	/// @brief This method converts an image source to image destination according to a given channel and color representation  layout
    /// @param[in] imgSrc: input image to convert
    /// @param[out] imgDst: output image converted
	/// @return FrameworkReturnCode::_SUCCESS_ id conversion succeed, else FrameworkReturnCode::_ERROR.   
	virtual FrameworkReturnCode convert(const SRef<SolAR::datastructure::Image> imgSrc, SRef<SolAR::datastructure::Image> & imgDst) = 0;

	/// @brief This method converts an image source to image destination according to a given channel and color representation  layout
    /// @param[in] imgSrc: input image to convert
    /// @param[out] imgDst: output image converted
    /// @param[in] destLayout: output image converted
	/// @return FrameworkReturnCode::_SUCCESS_ id conversion succeed, else FrameworkReturnCode::_ERROR.   
	virtual FrameworkReturnCode convert(const SRef<SolAR::datastructure::Image> imgSrc, SRef<SolAR::datastructure::Image> & imgDst, SolAR::datastructure::Image::ImageLayout destLayout) = 0;

	/// @brief This method converts an image source to image destination according to a look up table attribute defined in the component
    /// @param[in] imgSrc: input image to convert
    /// @param[out] imgDst: output image  with a look up table
	/// @return FrameworkReturnCode::_SUCCESS_ id color mapping succeed, else FrameworkReturnCode::_ERROR.   
	virtual FrameworkReturnCode convertLookUpTable(const SRef<SolAR::datastructure::Image> imgSrc, SRef<SolAR::datastructure::Image> & imgDst) = 0;

};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::image::IImageConvertor,
                             "9c982719-6cb4-4831-aa88-9e01afacbd16",
                             "IImageConvertor",
                             "SolAR::api::image::IImageConvertor");

#endif //SOLAR_IIMAGECONVERTOR_H
