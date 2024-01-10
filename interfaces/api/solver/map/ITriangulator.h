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

#ifndef ITRIANGULATOR_H
#define ITRIANGULATOR_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Keyframe.h"
#include "datastructure/DescriptorMatch.h"


namespace SolAR {
namespace api {
namespace solver {
namespace map {

/**
 * @class ITriangulator
 * @brief <B>Triangulates a set of 2D-2D undistorted points correspondances with known respective camera poses.</B>
 * <TT>UUID: 3a01b0e9-9a76-43f5-97b3-85bb6979b953</TT>
 */
class XPCF_CLIENTUUID("1b6be40f-030c-4436-a920-913d6e4421f4") XPCF_SERVERUUID("9cb53cc2-2887-4606-8d07-d9d4ae3108b2") ITriangulator :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief ITriangulator default constructor
    ITriangulator() = default;

    /// @brief ITriangulator default destructor
    virtual ~ITriangulator() = default;

    /// @brief triangulate pairs of points 2d captured from two views with differents poses (with respect to the camera instrinsic parameters).
    /// @param[in] pointsView1 set of 2D points seen in view_1.
    /// @param[in] pointsView2 set of 2D points seen in view_2.
    /// @param[in] matches the matches between the keypoints of the view1 and the keypoints of the view 2.
    /// @param[in] working_views a pair representing the id of the two views
    /// @param[in] poseView1 camera pose in the world coordinates system of the view_1 expressed as a Transform3D.
    /// @param[in] poseView2 camera pose in the world coordinates system of the view_2 expressed as a Transform3D.
    /// @param[in] camParams1 the parameters of the camera 1.
    /// @param[in] camParams1 the parameters of the camera 2.
    /// @param[out] pcloud set of triangulated 3d_points.
    /// @return the mean re-projection error (mean distance in pixels between the original 2D points and the projection of the reconstructed 3D points)
    virtual double triangulate(const std::vector<SolAR::datastructure::Point2Df> & pointsView1,
                               const std::vector<SolAR::datastructure::Point2Df> & pointView2,
                               const std::vector<SolAR::datastructure::DescriptorMatch> & matches,
                               const std::pair<uint32_t, uint32_t> & working_views,
                               const SolAR::datastructure::Transform3Df & poseView1,
                               const SolAR::datastructure::Transform3Df & poseView2,
                               const SolAR::datastructure::CameraParameters & camParams1,
                               const SolAR::datastructure::CameraParameters & camParams2,
                               std::vector<SRef<SolAR::datastructure::CloudPoint>> & pcloud)=0;

    /// @brief triangulate pairs of points 2d captured from two views with differents poses (with respect to the camera instrinsic parameters).
    /// @param[in] keypointsView1 set of keypoints seen in view_1.
    /// @param[in] keypointsView2 set of keypoints seen in view_2.
    /// @param[in] matches the matches between the keypoints of the view1 and the keypoints of the view 2.
    /// @param[in] working_views a pair representing the id of the two views
    /// @param[in] poseView1 camera pose in the world coordinates system of the view_1 expressed as a Transform3D.
    /// @param[in] poseView2 camera pose in the world coordinates system of the view_2 expressed as a Transform3D.
    /// @param[in] camParams1 the parameters of the camera 1.
    /// @param[in] camParams1 the parameters of the camera 2.
    /// @param[out] pcloud set of triangulated 3d_points.
    /// @return the mean re-projection error (mean distance in pixels between the original 2D points and the projection of the reconstructed 3D points)
    virtual double triangulate(const std::vector<SolAR::datastructure::Keypoint> & keypointsView1,
                               const std::vector<SolAR::datastructure::Keypoint> & keypointsView2,
                               const std::vector<SolAR::datastructure::DescriptorMatch> &matches,
                               const std::pair<uint32_t, uint32_t> & working_views,
                               const SolAR::datastructure::Transform3Df & poseView1,
                               const SolAR::datastructure::Transform3Df & poseView2,
                               const SolAR::datastructure::CameraParameters & camParams1,
                               const SolAR::datastructure::CameraParameters & camParams2,
                               std::vector<SRef<SolAR::datastructure::CloudPoint>> & pcloud)=0;

	/// @brief triangulate pairs of points 2d captured from two views with differents poses (with respect to the camera instrinsic parameters).
	/// @param[in] pointsView1 set of keypoints seen in view_1.
	/// @param[in] pointsView2 set of keypoints seen in view_2.
	/// @param[in] descriptor1 set of descriptors in view_1.
	/// @param[in] descriptor2 set of descriptors in view_2.
	/// @param[in] matches the matches between the keypoints of the view1 and the keypoints of the view 2.
	/// @param[in] working_views a pair representing the id of the two views
	/// @param[in] poseView1 Camera pose in the world coordinates system of the view_1 expressed as a Transform3D.
    /// @param[in] poseView2 Camera pose in the world coordinates system of the view_2 expressed as a Transform3D.
    /// @param[in] camParams1 the parameters of the camera 1.
    /// @param[in] camParams1 the parameters of the camera 2.
	/// @param[out] pcloud Set of triangulated 3d_points.
	/// @return the mean re-projection error (mean distance in pixels between the original 2D points and the projection of the reconstructed 3D points)
	virtual double triangulate(	const std::vector<SolAR::datastructure::Keypoint> & keypointsView1,
								const std::vector<SolAR::datastructure::Keypoint> & keypointsView2,
								const SRef<SolAR::datastructure::DescriptorBuffer> & descriptor1,
								const SRef<SolAR::datastructure::DescriptorBuffer> & descriptor2,
								const std::vector<SolAR::datastructure::DescriptorMatch> & matches,
								const std::pair<uint32_t, uint32_t> & working_views,
								const SolAR::datastructure::Transform3Df & poseView1,
								const SolAR::datastructure::Transform3Df & poseView2,
                                const SolAR::datastructure::CameraParameters & camParams1,
                                const SolAR::datastructure::CameraParameters & camParams2,
								std::vector<SRef<SolAR::datastructure::CloudPoint>> & pcloud) =0;

	/// @brief calculating 3D cloud points by triangulating pairs of matched features or using depth information of keypoints.
	/// @param[in] frame1 the first frame.
	/// @param[in] frame2 the second frame.
	/// @param[in] matches the matches between these two frames.
	/// @param[in] working_views a pair representing the id of the two views
    /// @param[in] camParams1 the parameters of the camera 1.
    /// @param[in] camParams1 the parameters of the camera 2
	/// @param[out] pcloud Set of triangulated 3d_points.
	/// @param[in] onlyDepth if it is true, using only depth information of keypoints for computing 3D cloud points.
	/// @return the mean re-projection error (mean distance in pixels between the original 2D points and the projection of the reconstructed 3D points)
    virtual double triangulate(SRef<SolAR::datastructure::Frame> frame1,
							   SRef<SolAR::datastructure::Frame> frame2,
                               const std::vector<SolAR::datastructure::DescriptorMatch> &matches,
							   const std::pair<uint32_t, uint32_t> & working_views,
                               const SolAR::datastructure::CameraParameters & camParams1,
                               const SolAR::datastructure::CameraParameters & camParams2,
                               std::vector<SRef<SolAR::datastructure::CloudPoint>> & pcloud,
							   const bool& onlyDepth = false) = 0;
};

}
}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::ITriangulator,
                             "3a01b0e9-9a76-43f5-97b3-85bb6979b953",
                             "ITriangulator",
                             "SolAR::api::solver::map::ITriangulator defines triangulation interface between 2 frames and 2D correspondences.");

#endif // ITRIANGULATOR_H
