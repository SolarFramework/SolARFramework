/**
 * @copyright Copyright (c) 2026 B-com http://www.b-com.com/
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

#ifndef SOLAR_IPCPROJECTONTOIMAGE_H
#define SOLAR_IPCPROJECTONTOIMAGE_H

#include "datastructure/CameraDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/PointCloud.h"
#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace pointCloud {

/**
  * @class IPCProjectOntoImage
  * @brief <B>Project a point cloud onto image.</B>
  * <TT>UUId: 3700812e-0af5-4968-b972-4fdc6d3d7371</TT>
  */

class XPCF_IGNORE IPCProjectOntoImage : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
   /// @brief IPCProjectOntoImage default constructor
   IPCProjectOntoImage() = default;

   /// @brief IPCProjectOntoImage default destructor
   virtual ~IPCProjectOntoImage() = default;

   /// @brief Project a point cloud onto an image plane
   /// @param[in] pointCloud the point cloud
   /// @param[in] cameraParameters the camera parameters
   /// @param[in] pose the camera pose
   /// @param[out] image output image created from the point cloud
   /// @return FrameworkReturnCode::_SUCCESS (pointcloud projected onto image successfully) otherwise FrameworkReturnCode::_ERROR_ (failure)
   virtual FrameworkReturnCode project(SRef<SolAR::datastructure::PointCloud> pointCloud,
                                       SRef<SolAR::datastructure::CameraParameters> cameraParameters,
                                       const SolAR::datastructure::Transform3Df& pose,
                                       SRef<SolAR::datastructure::Image>& image) const = 0;

};
}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pointCloud::IPCProjectOntoImage,
                             "3700812e-0af5-4968-b972-4fdc6d3d7371",
                             "IPCProjectOntoImage",
                             "Interface for projecting a point cloud onto image");


#endif // SOLAR_IPCPROJECTONTOIMAGE_H
