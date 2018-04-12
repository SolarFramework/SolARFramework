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

#ifndef SOLAR_IPOSEESTIMATION_H
#define SOLAR_IPOSEESTIMATION_H

#include "IComponentIntrospect.h"

#include "core/Messages.h"

#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Pose.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace solver {
namespace pose {

/**
 * @class IPoseEstimation
 * @brief Specifies the IPoseEstimation interface class.
 */
class IPoseEstimation : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    IPoseEstimation() = default;
    virtual ~IPoseEstimation() = default;

    ///
    /// @brief poseFromSolvePNP method provides an estimation of the camera pose from a set of 2D image points of their corresponding 3D  world points.
    /// @param[out] Camera pose in the world coordinates system of the view_1.
    /// @param[in] Set of 2d_points seen in view_1.
    /// @param[in]  Set of 3d_points corresponding to view_1.
    virtual FrameworkReturnCode poseFromSolvePNP( Pose & pose, const std::vector<SRef<Point2Df>> & imagePoints,
                                                  const std::vector<SRef<Point3Df>> & worldPoints) =0;    ///
    /// @brief this method is used to set intrinsic parameters and distorsion of the camera
    /// @param[in] Camera calibration matrix parameters.
    /// @param[in] Camera calibration distorsion parameters..
    virtual void setCameraParameters(const CamCalibration & intrinsicParams, const CamDistortion & distorsionParams) = 0;

    static constexpr const char * UUID = "a1c982ff-dbc4-4b67-b1d5-6a8cb0531a5d";
};

}
}
}
}

#endif // SOLAR_IPOSEESTIMATION_H
