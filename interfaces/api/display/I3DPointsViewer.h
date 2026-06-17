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

#include <xpcf/api/IComponentIntrospect.h>
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
class XPCF_IGNORE I3DPointsViewer :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief I3DPointsViewer default constructor
    I3DPointsViewer() = default;

    /// @brief I3DPointsViewer default destructor
    virtual ~I3DPointsViewer() = default;

    /// @brief Display in a windows the 3D point cloud as well as the current camera, and optionnally, the previous frames and keyframes.
    /// @param[in] pointCloud a point cloud to display in the 3D viewer.
    /// @param[in] pose poses of the current camera (transform of the camera defined in world coordinate system).
    /// @param[in] keyframesPoses (optional), poses of a set of keyframes (transform of the camera defined in world corrdinate system).
    /// @param[in] framePoses (optional), poses of a set of frames (transform of the camera defined in world corrdinate system).
    /// @param[in] pointCloud2 (optional), a second point cloud to display in the 3D viewer (useful to visualize result of a bundle adjustment).
    /// @param[in] keyframesPoses2 (optional), a second set of keyframes poses (transform of the camera defined in world corrdinate system, useful to visualize result of a bundle adjustment).
    /// @return FrameworkReturnCode::_SUCCESS if the window is created, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode display(const SRef<SolAR::datastructure::PointCloud> pointCloud,
                                        const SolAR::datastructure::Transform3Df & pose,
                                        const std::vector<SolAR::datastructure::Transform3Df> & keyframePoses = {},
                                        const std::vector<SolAR::datastructure::Transform3Df> & framePoses = {},
                                        const SRef<SolAR::datastructure::PointCloud> pointCloud2 = nullptr,
                                        const std::vector<SolAR::datastructure::Transform3Df> & keyframePoses2 = {}) = 0;

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

    /// @brief Display in a windows the 3D point cloud pre-loaded in a buffer as well as the current camera, and optionnally, the previous frames and keyframes.
    /// @param[in] pose poses of the current camera (transform of the camera defined in world coordinate system).
    /// @param[in] keyframesPoses (optional), poses of a set of keyframes (transform of the camera defined in world corrdinate system).
    /// @param[in] framePoses (optional), poses of a set of frames (transform of the camera defined in world corrdinate system).
    /// @param[in] keyframesPoses2 (optional), a second set of keyframes poses (transform of the camera defined in world corrdinate system, useful to visualize result of a bundle adjustment).
    /// @return FrameworkReturnCode::_SUCCESS if the window is created, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode display(const SolAR::datastructure::Transform3Df & pose,
                                        const std::vector<SolAR::datastructure::Transform3Df> & keyframePoses = {},
                                        const std::vector<SolAR::datastructure::Transform3Df> & framePoses = {},
                                        const std::vector<SolAR::datastructure::Transform3Df> & keyframePoses2 = {}) = 0;

    /// @brief Add in the GPU buffer one, or optionnally two 3D point clouds. Required when these point clouds are huge and static.
    /// @param[in] points set of static 3D points to display in the 3D viewer.
    /// @param[in] points2 (optional), a second set of static 3D points to display in the 3D viewer (useful to visualize result of a bundle adjustment).
    /// @return FrameworkReturnCode::_SUCCESS if the window is created, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode buffer(const std::vector<SRef<SolAR::datastructure::CloudPoint>> & points,
                                        const std::vector<SRef<SolAR::datastructure::CloudPoint>> & points2 = {}) = 0;


    /// @brief Add in the GPU buffer one, or optionnally two, 3D point clouds. Required when these point clouds are huge and static.
    /// @param[in] pointCloud a static point cloud to display in the 3D viewer.
    /// @param[in] pointCloud2 (optional), a second static point cloud to display in the 3D viewer (useful to visualize result of a bundle adjustment).
    /// @return FrameworkReturnCode::_SUCCESS if the window is created, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode buffer(const SRef<SolAR::datastructure::PointCloud> pointCloud,
                                       const SRef<SolAR::datastructure::PointCloud> pointCloud2 = nullptr) = 0;

    /// @brief Display a set of 3D Gaussians rendered as ellipsoid splats in a window.
    /// The data is passed as flat, contiguous, libtorch-free float buffers so that
    /// implementers (e.g. an OpenGL viewer) need no tensor library dependency.
    /// The viewer is expected to own its interactive (orbit) camera, hence no pose is required.
    /// @param[in] centers flat array of Gaussian centers, size 3*N (x,y,z per Gaussian).
    /// @param[in] scales flat array of per-axis scales, size 3*N (sx,sy,sz per Gaussian).
    /// @param[in] quaternions flat array of rotation quaternions, size 4*N (w,x,y,z per Gaussian).
    /// @param[in] colors flat array of RGB colors in [0,1], size 3*N (r,g,b per Gaussian).
    /// @param[in] opacities array of opacities in [0,1], size N.
    /// @return FrameworkReturnCode::_SUCCESS if displayed, FrameworkReturnCode::_NOT_IMPLEMENTED
    /// if the implementer does not support Gaussian display, else FrameworkReturnCode::_ERROR_.
    virtual FrameworkReturnCode displayGaussians(const std::vector<float> & centers,
                                                 const std::vector<float> & scales,
                                                 const std::vector<float> & quaternions,
                                                 const std::vector<float> & colors,
                                                 const std::vector<float> & opacities)
    {
        (void)centers; (void)scales; (void)quaternions; (void)colors; (void)opacities;
        return FrameworkReturnCode::_NOT_IMPLEMENTED;
    }
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::display::I3DPointsViewer,
                             "575d365a-9a27-11e8-9eb6-529269fb1459",
                             "I3DPointsViewer",
                             "SolAR::I3DPointsViewer interface")

#endif // I3DPOINTSVIEWER_H
