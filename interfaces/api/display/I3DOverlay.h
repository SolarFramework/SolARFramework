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

#include "datastructure/MathDefinitions.h"
#include "IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/Pose.h"
#include "datastructure/Keypoint.h"
#include "datastructure/SquaredBinaryPattern.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace display {
/**
 * @class I3DOverlay
 * @brief Drawing interface to overlay 3D information on top of an image.
 *
 * This class provides drawing method to overlay 3D debug informations on top of an image.
 */
class I3DOverlay : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief I3DOverlay default constructor
    I3DOverlay() = default;

    /// @brief I3DOverlay default destructor
    virtual ~I3DOverlay() = default;

    /// @brief Set the intrinsic parameters and distorsion of the camera
    virtual void setCameraParameters(const CamCalibration & intrinsic_parameters, const CamDistortion & distorsion_parameters) = 0;

    /// @brief Draw a box on the given Image
    /// The box is displayed according to the pose given in parameter. The reference of the box is positionned on the center of its bottom face.
    /// @param[in] Transfomr3Df The pose of the camera from which the box is viewed.
    /// @param[in] sizeX The size of the box along the X axis in world unit.
    /// @param[in] sizeY The size of the box along the Y axis in world unit.
    /// @param[in] sizeZ The size of the box along the Z axis in world unit.
    /// @param[in] transform The transform (position and ortation) of the box according to the world coordinate system
    /// @param[in,out] displayImage The image on which the box will be drawn
    virtual void drawBox (Transform3Df & pose, const  float sizeX, const float sizeY, const float sizeZ, const Transform3Df transform, SRef<Image> displayImage) = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::display::I3DOverlay,
                             "81a20f52-6bf9-4949-b914-df2f614bc945",
                             "SolAR::I3DOverlay interface");

#endif // SOLAR_I3DOVERLAY_H
