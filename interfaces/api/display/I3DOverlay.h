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

#ifndef SOLAR_I3DOVERLAY_H
#define SOLAR_I3DOVERLAY_H

#include "datastructure/CameraDefinitions.h"
#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/Keypoint.h"
#include "datastructure/SquaredBinaryPattern.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
namespace api {
namespace display {
/**
 * @class I3DOverlay
 * @brief <B>Draws 3D content on top of an image.</B>
 * <TT>UUID: 81a20f52-6bf9-4949-b914-df2f614bc945</TT>
 *
 * This class provides drawing method to overlay 3D debug informations on top of an image.
 */
class XPCF_CLIENTUUID("ce48f688-bb48-4d61-800c-e504c0d060a8") XPCF_SERVERUUID("cb391967-f407-4a67-b092-26d44de001ce") I3DOverlay :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief I3DOverlay default constructor
    I3DOverlay() = default;

    /// @brief I3DOverlay default destructor
    virtual ~I3DOverlay() = default;

    /// @brief Draw a box on the given Image
    /// The box is displayed according to the pose given in parameter. The reference of the box is positionned on the center of its bottom face.
    /// @param[in] Transfomr3Df The pose of the camera from which the box is viewed.
    /// @param[in] camParams The camera parameters.
    /// @param[in,out] displayImage The image on which the box will be drawn
    virtual void draw (const SolAR::datastructure::Transform3Df & pose,
                      const SolAR::datastructure::CameraParameters & camParams,
                      SRef<SolAR::datastructure::Image> displayImage) = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::display::I3DOverlay,
                             "81a20f52-6bf9-4949-b914-df2f614bc945",
                             "I3DOverlay",
                             "SolAR::I3DOverlay interface")

#endif // SOLAR_I3DOVERLAY_H
