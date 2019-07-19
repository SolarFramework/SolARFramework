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
using namespace datastructure;
namespace api {
namespace source {

/**
 * @class ISourceImage
 * @brief <B>A Source for an image, useful for AR video see-through pipelines.</B>
 * <TT>UUID: 06e2fc5d-39da-4486-b2a6-1d8bd788fa13</TT>
 *
 * This interface allows to store a synchronized pose and image from the pipeline to make it available to a third party application.
 */

class  ISourceImage : public virtual org::bcom::xpcf::IComponentIntrospect {
public:

   ISourceImage() = default;

   ///
   /// \brief ~ISourceImage
   ///
   virtual ~ISourceImage() = default;

   /// @brief Set a new image without pose.
   /// @param[in,out] image The new image , source of the pipeline.
   virtual SourceReturnCode setInputTexture( void* sourceTextureHandle, int with, int height ) = 0;

   /// @brief Provide an access to the new image and pose  made available by t the pipeline.
   /// The implementation of this interface must be thread safe
   /// @param[in] pose the new pose made available by the pipeline.
   /// @param[in,out] image The new image made available by the pipeline.
   /// @return return FrameworkReturnCode::_SUCCESS if a new pose and image have been updated, otherwise frameworkReturnCode::_ERROR_.
   virtual SourceReturnCode getNextImage(SRef<Image> & image ) = 0;

};

}
}
}  // end of namespace SolAR


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::source::ISourceImage,
                             "06e2fc5d-39da-4486-b2a6-1d8bd788fa13",
                             "ISourceImage",
                             "An interface allowing to store an image from extern source to make it available to the pipeline");

#endif // SOLAR_ISOURCEIMAGE_H
