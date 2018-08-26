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

#ifndef I3DPOINTSVIEWER_H
#define I3DPOINTSVIEWER_H

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/CloudPoint.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace display {
/**
 * @class I3DPointsViewer
 * @brief Viewer interface to display points cloud in a window.
 *
 * This class provides a viewer to display points cloud in a window.
 */
class I3DPointsViewer : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief I3DPointsViewer default constructor
    I3DPointsViewer() = default;

    /// @brief I3DPointsViewer default destructor
    virtual ~I3DPointsViewer() = default;

    /// @brief Display in a windows the 3D point cloud as well as the current camera, and optionnally, the previous frames and keyframes.
    /// The points are displayed according to the pose of a given viewpoint managed by the implementation of the component.
    /// @param[in] points, Set of 3D points to display in the 3D viewer.
    /// @param[in] pose, poses of the current camera (transform from the world corrdinate system to the camera coordinate system).
    /// @param[in] keyframesPoses (optional), poses of a set of keyframes (transform from the world corrdinate system to the keyframes coordinate system).
    /// @param[in] framePoses (optional), poses of a set of frames (transform from the world corrdinate system to the frames coordinate system).
    /// @return FrameworkReturnCode::_SUCCESS if the window is created, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode display (const std::vector<SRef<CloudPoint>>& points,
                                         const Transform3Df & pose,
                                         const std::vector<Transform3Df> keyframePoses = {},
                                         const std::vector<Transform3Df> framePoses = {}) = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::display::I3DPointsViewer,
                             "575d365a-9a27-11e8-9eb6-529269fb1459",
                             "SolAR::I3DPointsViewer interface")

#endif // I3DPOINTSVIEWER_H
