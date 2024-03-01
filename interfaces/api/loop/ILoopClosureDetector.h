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

#ifndef ILOOPCLOSUREDETECTOR_H
#define ILOOPCLOSUREDETECTOR_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "datastructure/MathDefinitions.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Keyframe.h"
#include "core/Messages.h"


namespace SolAR {
namespace api {
namespace loop {
/**
  * @class ILoopClosureDetector
  * @brief <B>Detect a loop closure from a given keyframe.</B>
  * <TT>UUID: a267c93a-c1c6-11ea-b3de-0242ac130004</TT>
  */

class XPCF_CLIENTUUID("ee57ff66-30d0-11ec-8d3d-0242ac130003") XPCF_SERVERUUID("fd612992-30d0-11ec-8d3d-0242ac130003") ILoopClosureDetector :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief ILoopClosureDetector default constructor
    ILoopClosureDetector() = default;

    ///@brief ILoopClosureDetector default destructor
    virtual ~ILoopClosureDetector() = default;

    /// @brief Detect a loop closure from a given keyframe.
    /// @param[in] queryKeyframe: the query keyframe.
    /// @param[out] detectedLoopKeyframe: the detected loop keyframe.
    /// @param[out] sim3Transform: 3D similarity transformation (Sim(3)) from
    /// query keyframe to the detected loop keyframe.
    /// @param[out] duplicatedPointsIndices: indices of duplicated cloud points.
    /// The first index is the id of point cloud seen from the detected loop keyframe.
    /// The second one is id of point cloud seen from the query keyframe
    /// @return FrameworkReturnCode::_SUCCESS if detect a loop closure, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode detect(const SRef<SolAR::datastructure::Keyframe> queryKeyframe,
                                       SRef<SolAR::datastructure::Keyframe> & detectedLoopKeyframe,
                                       SolAR::datastructure::Transform3Df & sim3Transform,
                                       std::vector<std::pair<uint32_t, uint32_t>> & duplicatedPointsIndices) const = 0;

    /// @brief Detect loops formed after map fusion
    /// new loops may form when merging a local map into the global one (e.g. half circle in global map and the other half in local map)
    /// the local map is extended from an initial small submap extracted from the global map
    /// the local map is already merged into the global one, and keyframes of both maps can be accessed via the same map manager
    /// @param[in] localMapKeyframeIds: list of keyframe ids of the local map
    /// @param[in] initSubmapKeyframeIds: list of keyframe ids of the initial submap from which are generated the local map
    /// @param[out] detectedLoops: list of detected loops, each loop is represented by a number of keyframe ids describing the path of the loop
    /// for instance, a loop can be defined by 4 keyframe ids
    /// the 1st and 2nd id belong to the keyframes of the original global map
    /// the 3rd and 4th id belong to the keyframes of the newly-acquired local map
    /// the 1st and 2nd keyframes correspond to the first half path of the loop, and the 3rd and 4th correspond to the second half path
    /// from 2nd to 3rd keyframes there is smooth transition because local map is generated from a submap of the original global map
    /// the path of the loop is described by the order 1st, 2nd, 3rd, 4th, and back to the 1st
    /// @param[out] loopTransforms: list of loop closure transforms, each transform is estimated from the 4th to the 1st keyframes as is described above
    virtual FrameworkReturnCode detect(const std::vector<uint32_t>& localMapKeyframeIds,
                                       const std::vector<uint32_t>& initSubmapKeyframeIds,
                                       std::vector<std::vector<uint32_t>>& detectedLoops,
                                       std::vector<SolAR::datastructure::Transform3Df>& loopTransforms) const = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::loop::ILoopClosureDetector,
                             "a267c93a-c1c6-11ea-b3de-0242ac130004",
                             "ILoopClosureDetector",
                             "SolAR::api::loop::ILoopClosureDetector interface for a loop closure detection.");

#endif // ILOOPCLOSUREDETECTOR_H
