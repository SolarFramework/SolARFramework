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

#ifndef SOLAR_I3DTRANSFORMFINDER_H
#define SOLAR_I3DTRANSFORMFINDER_H

#include "IComponentIntrospect.h"

#include "core/Messages.h"

#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Pose.h"
#include "datastructure/Image.h"

namespace SolAR {
    using namespace datastructure;
    namespace api {
        namespace solver {
            namespace pose {
            /**
             * @class I3DransformFinder
             * @brief Finds the 3D transform of 2D-3D points correspondaces.
             */
                class I3DTransformFinder : public virtual org::bcom::xpcf::IComponentIntrospect {
                public:
                    ///@brief I3DTransformFinder default constructor.
                    I3DTransformFinder() = default;
                    ///@brief I3DTransformFinder default destructor.
                    virtual ~I3DTransformFinder() = default;


                    /// @brief Estimates camera pose from a set of 2D image points of their corresponding 3D  world points.
                    /// @param[in] Set of 2d_points seen in view_1.
                    /// @param[in]  Set of 3d_points corresponding to view_1.
                    /// @param[out] Camera pose in the world coordinates system of the view_1 expressed as Transsform3D.
                    virtual FrameworkReturnCode estimate(const std::vector<SRef<Point2Df>> & imagePoints,
                                                         const std::vector<SRef<Point3Df>> & worldPoints,
                                                         std::vector<SRef<Point2Df>>&imagePoints_inlier,
                                                         std::vector<SRef<Point3Df>>&worldPoints_inlier,
                                                         Transform3Df & pose,
                                                         bool verbose) =0;    ///


                    /// @brief this method is used to set intrinsic parameters and distorsion of the camera
                    /// @param[in] Camera calibration matrix parameters.
                    /// @param[in] Camera distorsion parameters.
                    virtual void setCameraParameters(const CamCalibration & intrinsicParams, const CamDistortion & distorsionParams) = 0;
                    static constexpr const char * UUID = "77281cda-47c2-4bb7-bde6-5b0d02e75dae";
                };

            }
        }
    }
}

#endif // SOLAR_IPOSEESTIMATION_H

