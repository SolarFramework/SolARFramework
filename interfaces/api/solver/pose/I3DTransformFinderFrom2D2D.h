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

#include "datastructure/CameraDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/Keypoint.h"

namespace SolAR {
namespace api {
namespace solver {
namespace pose {
/**
 * @class I3DTransformFinderFrom2D2D
 * @brief <B>Finds the 3D transform between two cameras knowing the keypoints that match between them.</B>
 * <TT>UUID: 6063a606-9d30-11e8-98d0-529269fb1459</TT>
 */
class [[xpcf::clientUUID("62f0a994-3ad4-4322-8059-7513153d074a")]] [[xpcf::serverUUID("84c693c0-3301-453f-9fca-f0e6208b89bc")]] I3DTransformFinderFrom2D2D :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief I3DTransformFinderFrom2D2D default constructor.
    I3DTransformFinderFrom2D2D() = default;

    ///@brief I3DTransformFinderFrom2D2D default destructor.
    virtual ~I3DTransformFinderFrom2D2D() = default;

    /// @brief Estimates camera pose from a set of 2D points of the first image which match with a set of 2D points of the second image.
    /// @param[in] pointsView1 Set of 2D points seen in view 1.
    /// @param[in] pointsView2 Set of 2D points seen in view 2 and matching with the 2D points of the view 1.
    /// @param[in] camParams the camera parameters.
    /// @param[in] poseView1 Camera pose (3D transform of the camera of the view1 defined in world corrdinate system).
    /// @param[out] poseView2 Camera pose (3D transform of the camera of the view2 defined in world corrdinate system).
    /// @param[in,out] inlierMatches a vector of matches that will be used for the pose estimation. This vector wll be updates as some input matches will be considered as outliers. If this vector is empty, we consider that the ith point of pointsView1 matches with the ith point of pointsView2.
    /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode estimate(const std::vector<SolAR::datastructure::Point2Df> & pointsView1,
                                         const std::vector<SolAR::datastructure::Point2Df> & pointsView2,
                                         const SolAR::datastructure::CameraParameters & camParams,
                                         const SolAR::datastructure::Transform3Df & poseView1,
                                         SolAR::datastructure::Transform3Df & poseView2,
                                         std::vector<SolAR::datastructure::DescriptorMatch> & inlierMatches) =0;

    /// @brief Estimates camera pose from a set of keypoints of the first image which match with a set of keypoints of the second image.
    /// @param[in] pointsView1 Set of keypoints seen in view 1.
    /// @param[in] pointsView2 Set of keypoints seen in view 2 and matching with the 2D points of the view 1.
    /// @param[in] camParams the camera parameters.
    /// @param[in] poseView1 Camera pose (3D transform of the camera of the view1 defined in world corrdinate system).
    /// @param[out] poseView2 Camera pose (3D transform of the camera of the view2 defined in world corrdinate system).
    /// @param[in,out] inlierMatches a vector of matches that will be used for the pose estimation. This vector wll be updates as some input matches will be considered as outliers. If this vector is empty, we consider that the ith point of pointsView1 matches with the ith point of pointsView2.
    /// @return FrameworkReturnCode::_SUCCESS if succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode estimate(const std::vector<SolAR::datastructure::Keypoint> & pointsView1,
                                         const std::vector<SolAR::datastructure::Keypoint> & pointsView2,
                                         const SolAR::datastructure::CameraParameters & camParams,
                                         const SolAR::datastructure::Transform3Df& poseView1,
                                         SolAR::datastructure::Transform3Df & poseView2,
                                         std::vector<SolAR::datastructure::DescriptorMatch>& inlierMatches) =0;
};

}
}
}
}


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::I3DTransformFinderFrom2D2D,
                             "6063a606-9d30-11e8-98d0-529269fb1459",
                             "I3DTransformFinderFrom2D2D",
                             "SolAR::api::solver::pose::I3DTransformFinderFrom2D2D");


#endif // SOLAR_I3DTRANSFORMFINDERFROM2D2D_H


