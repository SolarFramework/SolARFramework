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
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/CloudPoint.h"
#include "datastructure/PointCloud.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
namespace api {
namespace display {
/**
 * @class I3DPointsViewer
 * @brief <B>Displays point clouds in a window.</B>
 * <TT>UUID: 575d365a-9a27-11e8-9eb6-529269fb1459</TT>
 *
 * This class provides a viewer to display points cloud in a window.
 */
class XPCF_CLIENTUUID("423cd9a6-f93a-4e1b-88f0-0762c1db5db3") XPCF_SERVERUUID("15e7a40b-9269-40a1-b95d-7139cff7ee4c") I3DPointsViewer :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief I3DPointsViewer default constructor
    I3DPointsViewer() = default;

    /// @brief I3DPointsViewer default destructor
    virtual ~I3DPointsViewer() = default;

	/// @brief Display in a windows the 3D point cloud as well as the current camera, and optionnally, the previous frames and keyframes.
	/// @param[in] points set of 3D points to display in the 3D viewer.
	/// @param[in] pose poses of the current camera (transform of the camera defined in world coordinate system).
	/// @param[in] keyframesPoses (optional), poses of a set of keyframes (transform of the camera defined in world corrdinate system).
	/// @param[in] framePoses (optional), poses of a set of frames (transform of the camera defined in world corrdinate system).
	/// @param[in] points2 (optional), a second set of 3D points to display in the 3D viewer (useful to visualize result of a bundle adjustment).
	/// @param[in] keyframesPoses2 (optional), a second set of keyframes poses (transform of the camera defined in world corrdinate system, useful to visualize result of a bundle adjustment).
	/// @return FrameworkReturnCode::_SUCCESS if the window is created, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode display(const std::vector<SRef<SolAR::datastructure::CloudPoint>> & points,
										const SolAR::datastructure::Transform3Df & pose,
                                        const std::vector<SolAR::datastructure::Transform3Df> & keyframePoses = {},
                                        const std::vector<SolAR::datastructure::Transform3Df> & framePoses = {},
                                        const std::vector<SRef<SolAR::datastructure::CloudPoint>> & points2 = {},
                                        const std::vector<SolAR::datastructure::Transform3Df> & keyframePoses2 = {}) = 0;


    /// @brief Display in a windows the 3D point cloud as well as the current camera, and optionnally, the previous frames and keyframes.
    /// @param[in] points set of 3D points to display in the 3D viewer.
    /// @param[in] pose poses of the current camera (transform of the camera defined in world coordinate system).
    /// @param[in] keyframesPoses (optional), poses of a set of keyframes (transform of the camera defined in world corrdinate system).
    /// @param[in] framePoses (optional), poses of a set of frames (transform of the camera defined in world corrdinate system).
    /// @param[in] points2 (optional), a second set of 3D points to display in the 3D viewer (useful to visualize result of a bundle adjustment).
    /// @param[in] keyframesPoses2 (optional), a second set of keyframes poses (transform of the camera defined in world corrdinate system, useful to visualize result of a bundle adjustment).
    /// @return FrameworkReturnCode::_SUCCESS if the window is created, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode display(const SRef<SolAR::datastructure::PointCloud> points,
                                        const SolAR::datastructure::Transform3Df & pose,
                                        const std::vector<SolAR::datastructure::Transform3Df> & keyframePoses = {},
                                        const std::vector<SolAR::datastructure::Transform3Df> & framePoses = {},
                                        const SRef<SolAR::datastructure::PointCloud> points2 = nullptr,
                                        const std::vector<SolAR::datastructure::Transform3Df> & keyframePoses2 = {}) = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::display::I3DPointsViewer,
                             "575d365a-9a27-11e8-9eb6-529269fb1459",
                             "I3DPointsViewer",
                             "SolAR::I3DPointsViewer interface")

#endif // I3DPOINTSVIEWER_H
