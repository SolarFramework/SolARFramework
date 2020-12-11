/**
 * @copyright Copyright (c) 2017 b<>com http://www.b-com.com/
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

#ifndef SOLAR_ISOURCEIMAGE_H
#define SOLAR_ISOURCEIMAGE_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "xpcf/api/IComponentIntrospect.h"
#include "ISourceReturnCode.h"
#include "datastructure/Image.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace source {

/**
 * @class ISourceImage
 * @brief <B>A Source for an image, useful for AR video see-through pipelines.</B>
 * <TT>UUID: 06e2fc5d-39da-4486-b2a6-1d8bd788fa13</TT>
 *
 * This interface allows to link a texture buffer from a third party to our pipeline
 */

class [[xpcf::ignore]] ISourceImage : virtual public org::bcom::xpcf::IComponentIntrospect {
public:

   ISourceImage() = default;

   ///
   /// \brief ~ISourceImage
   ///
   virtual ~ISourceImage() = default;

   /// @brief Set a new image coming from a third party.
   /// @param [in] sourceTexturehandle. Texture buffer from third party like Unity
   /// @param [in] width of the image coming from the third party like Unity
   /// @param [in] height of the image coming from the third party like Unity
   /// @return SourceReturnCode::_SUCCESS if a new pose and image have been updated, otherwise frameworkReturnCode::_ERROR_
   virtual SourceReturnCode setInputTexture(const void* sourceTexturehandle,const int width,const int height) = 0;

   /// @brief Get a pointer to the texture buffer to update it with the new image when required.
   /// @param[in,out] image
   /// @return SourceReturnCode::_SUCCESS if a new pose and image have been updated, otherwise frameworkReturnCode::_ERROR_
   virtual SourceReturnCode getNextImage(SRef<datastructure::Image> & image) = 0;

};

}
}
}  // end of namespace SolAR


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::source::ISourceImage,
                             "06e2fc5d-39da-4486-b2a6-1d8bd788fa13",
                             "ISourceImage",
                             "An interface allowing to store an image from extern source to make it available to the pipeline");

#endif // SOLAR_ISOURCEIMAGE_H
