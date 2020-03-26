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

	/// @brief Estimates camera pose from a set of 2D image points of their corresponding 3D  world points.
	/// @param[in] imagePoints, set of 2d_points seen in view_1.
	/// @param[in] worldPoints, set of 3d_points corresponding to view_1.
	/// @param[in] imageLines, set of 2d_lines seen in view_1.
	/// @param[in] worldLines, set of 3d_lines corresponding to view_1.
	/// @param[out] pose, camera pose (pose of the camera defined in world corrdinate system) expressed as a Transform3D.
	/// @param[in] initialPose (Optional), a transform3D to initialize the pose (reducing the convergence time and improving its success).
	virtual FrameworkReturnCode estimate(const std::vector<Point2Df> & imagePoints,
										 const std::vector<Point3Df> & worldPoints,
										 const std::vector<Edge2Df> & imageLines,
										 const std::vector<Edge3Df> & worldLines,
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