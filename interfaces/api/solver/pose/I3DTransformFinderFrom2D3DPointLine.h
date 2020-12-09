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

#ifndef SOLAR_I3DTRANSFORMFINDERFROM2D3DPOINTLINE_H
#define SOLAR_I3DTRANSFORMFINDERFROM2D3DPOINTLINE_H

#include "xpcf/api/IComponentIntrospect.h"

#include "core/Messages.h"

#include "datastructure/CameraDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/Keyline.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace solver {
namespace pose {

/**
* @class I3DTransformFinderFrom2D3DPointLine
* @brief <B>Finds the 3D transform of 2D-3D points and lines correspondences.</B>
* <TT>UUID: c6e82ced-2e26-4e64-b70d-a77f9961e9af</TT>
*/

class I3DTransformFinderFrom2D3DPointLine : virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
	///@brief I3DTransformFinderFrom2D3D default constructor.
	I3DTransformFinderFrom2D3DPointLine() = default;
	///@brief I3DTransformFinderFrom2D3D default destructor.
	virtual ~I3DTransformFinderFrom2D3DPointLine() = default;

	/// @brief this method is used to set intrinsic parameters and distorsion of the camera
	/// @param[in] Camera calibration matrix parameters.
	/// @param[in] Camera distorsion parameters.
	virtual void setCameraParameters(const CamCalibration & intrinsicParams, const CamDistortion & distorsionParams) = 0;

	/// @brief Estimates camera pose from a set of 2D image points and 2D lines and their corresponding 3D world points and lines.
	/// @param[in] imagePoints: set of 2D points.
	/// @param[in] worldPoints: set of 3D points.
	/// @param[in] imageLines: set of 2D lines.
	/// @param[in] worldLines: set of 3D lines.
	/// @param[out] pose: camera pose (pose of the camera defined in world coordinate system) expressed as a <Transform3Df>.
	/// @param[in] initialPose: (optional) a <Transform3Df> to initialize the pose (reducing convergence time and improving success rate).
	virtual FrameworkReturnCode estimate(const std::vector<Point2Df> & imagePoints,
										 const std::vector<Point3Df> & worldPoints,
										 const std::vector<Edge2Df> & imageLines,
										 const std::vector<Edge3Df> & worldLines,
										 Transform3Df & pose,
										 const Transform3Df initialPose = Transform3Df::Identity()) = 0;

	/// @brief Estimates camera pose from a set of 2D image points and 2D lines and their corresponding 3D world points and lines,
	/// and performing RANSAC estimation iteratively to deduce inliers.
	/// @param[in] imagePoints: set of 2D points.
	/// @param[in] worldPoints: set of 3D points.
	/// @param[in] imageLines: set of 2D lines.
	/// @param[in] worldLines: set of 3D lines.
	/// @param[out] imagePoints_inliers: set of 2D points suspected as inliers by RANSAC.
	/// @param[out] worldPoints_inliers: set of 3D points suspected as inliers by RANSAC.
	/// @param[out] imageLines_inliers: set of 2D lines suspected as inliers by RANSAC.
	/// @param[out] worldLines_inliers: set of 3D lines suspected as inliers by RANSAC.
	/// @param[out] pointInliers: boolean vector to store whether a point is considered as an inlier or as an outlier.
	/// @param[out] lineInliers: boolean vector to store whether a line is considered as an inlier or as an outlier.
	/// @param[out] pose: camera pose (pose of the camera defined in world coordinate system) expressed as a <Transform3Df>.
	/// @param[in] initialPose: (optional) a <Transform3Df> to initialize the pose (reducing convergence time and improving success rate).
	virtual FrameworkReturnCode estimateRansac(	const std::vector<Point2Df> & imagePoints,
												const std::vector<Point3Df> & worldPoints,
												const std::vector<Edge2Df> & imageLines,
												const std::vector<Edge3Df> & worldLines,
												std::vector<Point2Df> & imagePoints_inliers,
												std::vector<Point3Df> & worldPoints_inliers,
												std::vector<Edge2Df> & imageLines_inliers,
												std::vector<Edge3Df> & worldLines_inliers,
												std::vector<bool> & pointInliers,
												std::vector<bool> & lineInliers,
												Transform3Df & pose,
												const Transform3Df initialPose = Transform3Df::Identity()) = 0;
};
}
}
}
}


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::I3DTransformFinderFrom2D3DPointLine,
							 "c6e82ced-2e26-4e64-b70d-a77f9961e9af",
							 "I3DTransformFinderFrom2D3DPointLine",
							 "SolAR::api::solver::pose::I3DTransformFinderFrom2D3DPointLine");


#endif // SOLAR_I3DTRANSFORMFINDERFROM2D3DPOINTLINE_H