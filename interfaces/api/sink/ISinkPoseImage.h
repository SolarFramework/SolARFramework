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

#ifndef SOLAR_ISINKPOSEIMAGE_H
#define SOLAR_ISINKPOSEIMAGE_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "ISinkReturnCode.h"
#include "datastructure/Image.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace sink {

/**
 * @class ISinkPoseImage
 * @brief <B>A Sink for a synchronized pose and image useful for AR video see-through pipelines.</B>
 * <TT>UUID: c0d9fee4-d7d7-4866-a6cd-3bacac23316a</TT>
 *
 * This interface allows to store a synchronized pose and image from the pipeline to make it available to a third party application.
 */

class XPCF_IGNORE ISinkPoseImage : virtual public org::bcom::xpcf::IComponentIntrospect {
public:

   ISinkPoseImage() = default;

   ///
   /// \brief ~ISinkPoseImage
   ///
   virtual ~ISinkPoseImage() = default;

   /// @brief Set a new image and pose coming from the pipeline.
   /// @param[in] pose: The new pose to be made available to a third party application.
   /// @param[in] image: The new image to be made available to a third party application.
   virtual void set(const SolAR::datastructure::Transform3Df & pose, const SRef<SolAR::datastructure::Image> image) = 0;

   /// @brief Set a new image without pose.
   /// @param[in] image: The new image to update a buffer texture when required.
   virtual void set(const SRef<SolAR::datastructure::Image> image) = 0;

   /// @brief Set a pointer to the texture buffer to update it with the new image when required.
   /// @param[in] imageBuffer: the texture buffer uses to contain the new image
   /// @return FrameworkReturnCode::_SUCCESS_ if the texture buffer pointer is well set.
   virtual FrameworkReturnCode setImageBuffer(unsigned char* imageBufferPointer) = 0;


   /// @brief Provide an access to the new image and pose  made available by the pipeline.
   /// The implementation of this interface must be thread safe
   /// @param[in,out] pose: the new pose made available by the pipeline.
   /// @return return FrameworkReturnCode::_SUCCESS if a new pose and image have been updated,
   /// otherwise frameworkReturnCode::_ERROR_.
   virtual SinkReturnCode get(SolAR::datastructure::Transform3Df & pose) = 0;

   /// @brief Provide an access to the new image and pose made available by the pipeline
   /// only if they have been updated by the pipeline.
   /// The implementation of this interface must be thread safe
   /// @param[in,out] pose: the new pose made available by the pipeline.
   /// @return return FrameworkReturnCode::_SUCCESS if a new pose and image are available, otherwise frameworkReturnCode::_ERROR_.
   virtual SinkReturnCode tryGet(SolAR::datastructure::Transform3Df& pose ) = 0;

};

}
}
}  // end of namespace SolAR


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::sink::ISinkPoseImage,
                             "c0d9fee4-d7d7-4866-a6cd-3bacac23316a",
                             "ISinkPoseImage",
                             "An interface allowing to store a synchronized pose and image from the pipeline to make it available to a third party application");

#endif // SOLAR_ISINKPOSEIMAGE_H
