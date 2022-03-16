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

#ifndef SOLAR_IRGBDCAMERA_H
#define SOLAR_IRGBDCAMERA_H

#include "api/input/devices/IDevice.h"
#include "api/input/devices/ICamera.h"
#include "api/input/devices/IDepthCamera.h"
#include "core/Messages.h"
#include "datastructure/MathDefinitions.h"

namespace SolAR {
namespace api {
namespace input {
namespace devices {

/**
 * @class IRGBDCamera
 * @brief Specify the IRGBDCamera interface class.
 *
 * This class describes the interface of a RGBD camera capture device.
 */
class [[xpcf::clientUUID("1c8df185-f8d9-4899-8206-74d1f64a7ad9")]] [[xpcf::serverUUID("01bb552a-9e6c-47fe-8b57-bce2a4c0ce42")]] IRGBDCamera :
    virtual public ICamera, virtual public IDepthCamera {
public:
    /// @brief Specify the IRGBDCamera constructor class
    IRGBDCamera() = default;

    /// @brief Specify the IRGBDCamera destructor class
    virtual ~IRGBDCamera() = default;

    /// @brief Provides the last color image, depth image, corresponding 3D point cloud, and aligned images (RGB on depth and depth on RGB).
    /// If output parameters are null (nullptr), it means that the implementation, or the requested mode does not provide this feature.
    /// @param[in,out] colorImg the RGB image captured by the RGBD camera
    /// @param[in,out] depthImg the depth image captured by the RGBD camera
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode getNextRGBDFrame(SRef<SolAR::datastructure::Image> & colorImg,
                                                 SRef<SolAR::datastructure::Image> & depthImg) = 0;

    /// @brief Provides a depth image alingned on the color image
    /// @param[in,out] alignedDepthImg the depth image captured by the RGBD camera and aligned on the color image
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode alignDepthToColor (SRef<SolAR::datastructure::Image> & alignedDepthImg) const = 0;

    /// @brief Provides a color image alingned on the depth image
    /// @param[in,out] alignedColorImg the RGB image captured by the RGBD camera and aligned on the depth image
    /// @return FrameworkReturnCode to track sucessful or failing event.
    virtual FrameworkReturnCode alignColorToDepth (SRef<SolAR::datastructure::Image> & alignedColorImg) const = 0;

    /// @brief Provides the 3D point in the depth sensor coordinate system corresponding to a given pixel of the color image
    /// @param[in] inPixel The pixel for which we want the 3 position
    /// @return a 3D point corresponding to the input pixel
    virtual SolAR::datastructure::Point3Df getPixelToWorld (const SolAR::datastructure::Point2Di & inPixel) const = 0;

    /// @brief Provides the pixel of the color image to the projection of a given 3D point
    /// @param[in] in3DPoint The 3D point we want to project on the color image
    /// @return a 2D point representing a pixel of the color image on which the 3D point in projected
    virtual SolAR::datastructure::Point2Di getWorldToPixel (const SolAR::datastructure::CloudPoint & in3DPoint) const = 0;

    /// @brief Provides the pixels of the color image to the projection of given 3D points
    /// @param[in] in3DPoints The 3D points we want to project on the color image
    /// @return a 2D points vector representing the pixels of the color image on which the 3D points are projected
    virtual std::vector<SolAR::datastructure::Point2Df> getWorldToPixels (const std::vector<SRef<SolAR::datastructure::CloudPoint>>& in3DPoints) const = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::devices::IRGBDCamera,
                             "5bf56174-94fd-4256-8eb7-b653ea3b8c34",
                             "IRGBDCamera",
                             "Interface for RGBD camera");


#endif // SOLAR_IRGBDCAMERA_H
