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

#ifndef SOLAR_IPCSEMANTICFROM2D_H
#define SOLAR_IPCSEMANTICFROM2D_H

#include "core/Messages.h"
#include "datastructure/CameraParametersCollection.h"
#include "datastructure/KeyframeCollection.h"
#include "datastructure/Mask2DCollection.h"
#include "datastructure/PointCloud.h"
#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace pointCloud {

/**
  * @class IPCSemanticFrom2D
  * @brief <B>Estimate semantic Ids of cloud points from 2D information.</B>
  * <TT>UUId: e7f67167-1512-4c1c-808a-adcfb606030e</TT>
  */

class XPCF_IGNORE IPCSemanticFrom2D : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
   /// @brief IPCSemanticFrom2D default constructor
   IPCSemanticFrom2D() = default;

   /// @brief IPCSemanticFrom2D default destructor
   virtual ~IPCSemanticFrom2D() = default;

   /// @brief Estimate point cloud semantic Ids from a keyframe collection and a mask collection
   /// @param[in,out] pointCloud the point cloud for which semantic Ids will be estimated
   /// @param[in] keyframeCollection input list of keyframes
   /// @param[in] cameraParametersCollection input list of camera parameters
   /// @param[in] maskCollection input list of masks
   /// @return FrameworkReturnCode::_SUCCESS (semantic id estimated successfully) otherwise FrameworkReturnCode::_ERROR_ (failure)
   virtual FrameworkReturnCode estimate(SRef<SolAR::datastructure::PointCloud> pointCloud,
                                        SRef<SolAR::datastructure::KeyframeCollection> keyframeCollection,
                                        SRef<SolAR::datastructure::CameraParametersCollection> cameraParametersCollection,
                                        SRef<SolAR::datastructure::Mask2DCollection> maskCollection) const = 0;

};
}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pointCloud::IPCSemanticFrom2D,
                             "e7f67167-1512-4c1c-808a-adcfb606030e",
                             "IPCSemanticFrom2D",
                             "Interface for estimating semantic Ids of cloud points from 2D information");


#endif // SOLAR_IPCSEMANTICFROM2D_H
