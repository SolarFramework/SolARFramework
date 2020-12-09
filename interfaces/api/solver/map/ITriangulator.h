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

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Keyline.h"
#include "datastructure/Keyframe.h"
#include "datastructure/DescriptorMatch.h"


namespace SolAR {
using namespace datastructure;
namespace api {
namespace solver {
namespace map {

/**
 * @class ITriangulator
 * @brief <B>Triangulates a set of 2D-2D points correspondances with known respective camera poses.</B>
 * <TT>UUID: 3a01b0e9-9a76-43f5-97b3-85bb6979b953</TT>
 */
class  ITriangulator : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief ITriangulator default constructor
    ITriangulator() = default;

    /// @brief ITriangulator default destructor
    virtual ~ITriangulator() = default;

    /// @brief this method is used to set intrinsic parameters and distorsion of the camera
    /// @param[in] intrinsicParams camera calibration matrix parameters.
    /// @param[in] distorsionParams camera distorsion parameters.
    virtual void setCameraParameters(const CamCalibration & intrinsicParams, const CamDistortion & distorsionParams) = 0;

    /// @brief triangulate pairs of points 2d captured from two views with differents poses (with respect to the camera instrinsic parameters).
    /// @param[in] pointsView1 set of 2D points seen in view_1.
    /// @param[in] pointsView2 set of 2D points seen in view_2.
    /// @param[in] matches the matches between the keypoints of the view1 and the keypoints of the view 2.
    /// @param[in] working_views a pair representing the id of the two views
    /// @param[in] poseView1 camera pose in the world coordinates system of the view_1 expressed as a Transform3D.
    /// @param[in] poseView2 camera pose in the world coordinates system of the view_2 expressed as a Transform3D..
    /// @param[out] pcloud set of triangulated 3d_points.
    /// @return the mean re-projection error (mean distance in pixels between the original 2D points and the projection of the reconstructed 3D points)
    virtual double triangulate(const std::vector<Point2Df>& pointsView1,
                               const std::vector<Point2Df>& pointView2,
                               const std::vector<DescriptorMatch>&matches,
                               const std::pair<unsigned int,unsigned int>&working_views,
                               const Transform3Df& poseView1,
                               const Transform3Df& poseView2,
                               std::vector<SRef<CloudPoint>>& pcloud)=0;

    /// @brief triangulate pairs of points 2d captured from two views with differents poses (with respect to the camera instrinsic parameters).
    /// @param[in] keypointsView1 set of keypoints seen in view_1.
    /// @param[in] keypointsView2 set of keypoints seen in view_2.
    /// @param[in] matches the matches between the keypoints of the view1 and the keypoints of the view 2.
    /// @param[in] working_views a pair representing the id of the two views
    /// @param[in] poseView1 camera pose in the world coordinates system of the view_1 expressed as a Transform3D.
    /// @param[in] poseView2 camera pose in the world coordinates system of the view_2 expressed as a Transform3D..
    /// @param[out] pcloud set of triangulated 3d_points.
    /// @return the mean re-projection error (mean distance in pixels between the original 2D points and the projection of the reconstructed 3D points)
    virtual double triangulate(const std::vector<Keypoint>& keypointsView1,
                               const std::vector<Keypoint>& keypointsView2,
                               const std::vector<DescriptorMatch>&matches,
                               const std::pair<unsigned int,unsigned int>&working_views,
                               const Transform3Df& poseView1,
                               const Transform3Df& poseView2,
                               std::vector<SRef<CloudPoint>>& pcloud)=0;

	/// @brief triangulate pairs of points 2d captured from two views with differents poses (with respect to the camera instrinsic parameters).
	/// @param[in] pointsView1 set of keypoints seen in view_1.
	/// @param[in] pointsView2 set of keypoints seen in view_2.
	/// @param[in] descriptor1 set of descriptors in view_1.
	/// @param[in] descriptor2 set of descriptors in view_2.
	/// @param[in] matches the matches between the keypoints of the view1 and the keypoints of the view 2.
	/// @param[in] working_views a pair representing the id of the two views
	/// @param[in] poseView1 Camera pose in the world coordinates system of the view_1 expressed as a Transform3D.
	/// @param[in] poseView2 Camera pose in the world coordinates system of the view_2 expressed as a Transform3D..
	/// @param[out] pcloud Set of triangulated 3d_points.
	/// @return the mean re-projection error (mean distance in pixels between the original 2D points and the projection of the reconstructed 3D points)
	virtual double triangulate(	const std::vector<Keypoint> & keypointsView1,
								const std::vector<Keypoint> & keypointsView2,
								const SRef<DescriptorBuffer> & descriptor1,
								const SRef<DescriptorBuffer> & descriptor2,
								const std::vector<DescriptorMatch> & matches,
								const std::pair<unsigned int, unsigned int> & working_views,
								const Transform3Df & poseView1,
								const Transform3Df & poseView2,
								std::vector<SRef<CloudPoint>> & pcloud) = 0;

	/// @brief triangulate pairs of points 2d captured from current keyframe with its reference keyframe using their poses (with respect to the camera instrinsic parameters).
	/// @param[in] curKeyframe current keyframe.
	/// @param[in] matches the matches between the keypoints of the view1 and the keypoints of the view 2.
	/// @param[out] pcloud Set of triangulated 3d_points.
	/// @return the mean re-projection error (mean distance in pixels between the original 2D points and the projection of the reconstructed 3D points)
	virtual double triangulate( const SRef<Keyframe>& curKeyframe,
							    const std::vector<DescriptorMatch>&matches,
                                std::vector<SRef<CloudPoint>>& pcloud) = 0;

	/// @brief triangulate pairs of 2D keylines captured from two different views with their associated poses
	/// @param[in] keylines1, set of keylines detected in the first view.
	/// @param[in] keylines2, set of keylines detected in the second view.
	/// @param[in] matches, the matches between the keylines detected in each view.
	/// @param[in] pose1, camera pose of the first view.
	/// @param[in] pose2, camera pose of the second view.
	/// @param[out] linecloud, set of triangulated 3D lines.
	/// @return the mean re-projection error
	virtual double triangulate( const std::vector<Keyline> & keylines1,
								const std::vector<Keyline> & keylines2,
								const SRef<DescriptorBuffer>& descriptor1,
								const SRef<DescriptorBuffer>& descriptor2,
								const std::vector<DescriptorMatch> & matches,
								const std::pair<unsigned, unsigned>& working_views,
								const Transform3Df & pose1,
								const Transform3Df & pose2,
								std::vector<CloudLine> & lineCloud) = 0;
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
