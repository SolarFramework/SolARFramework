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

#ifndef SOLAR_I3DTRANSFORMFINDERFROM2D2D_H
#define SOLAR_I3DTRANSFORMFINDERFROM2D2D_H

#include "xpcf/api/IComponentIntrospect.h"

#include "core/Messages.h"

#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/Keypoint.h"

namespace SolAR {
    using namespace datastructure;
    namespace api {
        namespace solver {
            namespace pose {
            /**
             * @class I3DTransformFinderFrom2D2D
             * @brief Finds the 3D transform between é cameras knowing the keypoints that match between them.
             */
                class I3DTransformFinderFrom2D2D : public virtual org::bcom::xpcf::IComponentIntrospect {
                public:
                    ///@brief I3DTransformFinderFrom2D2D default constructor.
                    I3DTransformFinderFrom2D2D() = default;
                    ///@brief I3DTransformFinderFrom2D2D default destructor.
                    virtual ~I3DTransformFinderFrom2D2D() = default;

                    /// @brief this method is used to set intrinsic parameters and distorsion of the camera
                    /// @param[in] Camera calibration matrix parameters.
                    /// @param[in] Camera distorsion parameters.
                    virtual void setCameraParameters(const CamCalibration & intrinsicParams, const CamDistortion & distorsionParams) = 0;

                    /// @brief Estimates camera pose from a set of 2D points of the first image which match with a set of 2D points of the second image.
                    /// @param[in] pointsView1, Set of 2D points seen in view 1.
                    /// @param[in] pointsView2, Set of 2D points seen in view 2 and matching with the 2D points of the view 1.
                    /// @param[in] poseView1, Camera pose (Transform3D from the world coordinates system to the camera coordinate system of the view 1).
                    /// @param[out] poseView2, Camera pose (Transform3D from the world coordinates system to the camera coordinate system of the view 2).
                    /// @param[in|out] inlierMatches, a vector of matches that will be used for the pose estimation. This vector wll be updates as some input matches will be considered as outliers. If this vector is empty, we consider that the ith point of pointsView1 matches with the ith point of pointsView2.
                    virtual FrameworkReturnCode estimate(const std::vector<SRef<Point2Df>> & pointsView1,
                                                         const std::vector<SRef<Point2Df>> & pointsView2,
                                                         const Transform3Df& poseView1,
                                                         Transform3Df & poseView2,
                                                         std::vector<DescriptorMatch>& inlierMatches) =0;

                    /// @brief Estimates camera pose from a set of keypoints of the first image which match with a set of keypoints of the second image.
                    /// @param[in] pointsView1, Set of keypoints seen in view 1.
                    /// @param[in] pointsView2, Set of keypoints seen in view 2 and matching with the 2D points of the view 1.
                    /// @param[in] poseView1, Camera pose (Transform3D from the world coordinates system to the camera coordinate system of the view 1).
                    /// @param[out] poseView2, Camera pose (Transform3D from the world coordinates system to the camera coordinate system of the view 2).
                    /// @param[in|out] inlierMatches, a vector of matches that will be used for the pose estimation. This vector wll be updates as some input matches will be considered as outliers. If this vector is empty, we consider that the ith point of pointsView1 matches with the ith point of pointsView2.
                    virtual FrameworkReturnCode estimate(const std::vector<SRef<Keypoint>> & pointsView1,
                                                         const std::vector<SRef<Keypoint>> & pointsView2,
                                                         const Transform3Df& poseView1,
                                                         Transform3Df & poseView2,
                                                         std::vector<DescriptorMatch>& inlierMatches) =0;
                };

            }
        }
    }
}


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::I3DTransformFinderFrom2D2D,
                             "6063a606-9d30-11e8-98d0-529269fb1459",
                             "SolAR::api::solver::pose::I3DTransformFinderFrom2D2D");


#endif // SOLAR_I3DTRANSFORMFINDERFROM2D2D_H


