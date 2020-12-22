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

#ifndef SOLAR_ISINKPOSETEXTUREBUFFER_H
#define SOLAR_ISINKPOSETEXTUREBUFFER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "xpcf/api/IComponentIntrospect.h"
#include "ISinkReturnCode.h"
#include "datastructure/Image.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace sink {

/**
 * @class ISinkPoseTextureBuffer
 * @brief <B>A Sink for a synchronized pose and texture buffer useful for AR video see-through pipelines.</B>
 * <TT>UUID: 8b220946-34ab-4fba-9aa7-ea8da807a2cf</TT>
 *
 * This interface allows to make available a pose to a third party application and to update a texture buffer with a new image.
 */

class /*[[xpcf::ignore]]*/ ISinkPoseTextureBuffer : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
   ISinkPoseTextureBuffer() = default;

   ///
   /// @brief ~ISinkPoseTextureBuffer
   ///
   virtual ~ISinkPoseTextureBuffer() = default;

   /// @brief Set a new image and pose coming from the pipeline.
   /// @param[in] pose: The new pose to be made available to a third party application.
   /// @param[in] image: The new image to update a buffer texture when required.
   virtual void set(const datastructure::Transform3Df & pose, const SRef<datastructure::Image> image) = 0;

   /// @brief Set a new image without pose.
   /// @param[in] image: The new image to update a buffer texture when required.
   virtual void set(const SRef<datastructure::Image> image) = 0;

   /// @brief Set a pointer to the texture buffer to update it with the new image when required.
   /// @param[in] textureBufferPointer: the pointer on texture buffer
   /// @return FrameworkReturnCode::_SUCCESS_ if the texture buffer pointer is well set.
   virtual FrameworkReturnCode setTextureBuffer(void* textureBufferPointer) = 0;

   /// @brief ???
   virtual void updateFrameDataOGL(int enventID) = 0;

   /// @brief Provide an access to the new pose and update the texture buffer with the new image.
   /// The implementation of this interface must be thread safe
   /// @param[in,out] pose: the new pose made available by the pipeline.
   /// @return return FrameworkReturnCode::_SUCCESS if a new pose and image have been updated, otherwise frameworkReturnCode::_ERROR_.
   virtual SinkReturnCode udpate(datastructure::Transform3Df & pose) = 0;

   /// @brief Provide an access to the new pose and update the texture buffer with the new image only if the image and the pose have been updated by the pipeline.
   /// The implementation of this interface must be thread safe
   /// @param[in,out] pose: the new pose made available by the pipeline.
   /// @return return FrameworkReturnCode::_SUCCESS if a new pose and image are available, otherwise frameworkReturnCode::_ERROR_.
   virtual SinkReturnCode tryUpdate(datastructure::Transform3Df & pose) = 0;

};

}
}
}  // end of namespace SolAR


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::sink::ISinkPoseTextureBuffer,
                             "8b220946-34ab-4fba-9aa7-ea8da807a2cf",
                             "ISinkPoseTextureBuffer",
                             "An interface allowing to to make available a pose to a third party application and to update a texture buffer with a new image");

#endif // SOLAR_ISINKPOSETEXTUREBUFFER_H
