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

class XPCF_IGNORE ILoopClosureDetector :
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

    /// @brief Detect loops formed after map fusion.
    /// New loops may form when merging a local map into the global map.
    /// For example, the 1st half of a circular mapping path exists in the global map and the 2nd half in local map. A loop is formed when combining these two maps.
    /// In SolAR, usually the local map is extended from a small submap extracted from the original global map. As a result, local and global maps may share some common keyframes
    /// Sometimes in specific cases, local mapping is done independently, e.g., from relocalizing a fiducial marker. No common keyframes exist between local and global maps.
    /// A unique map manager is used to access the local and global map keyframes
    /// @param[in] localMapKeyframeIds IDs of the keyframes belonging to the local map
    /// @param[in] initSubmapKeyframeIds IDs of the keyframes belonging to the initial submap extracted from the original global map
    /// if initSubmapKeyframeIds is empty list, it means no common keyframes between local and global maps (e.g. local map is generated by relocalizing a fiducial marker)
    /// @param[out] localMapFirstKeyframeId ID of the first keyframe of the local map
    /// @param[out] globalMapClosestKeyframeId ID of the keyframe of the original global map which is closest to the first keyframe of the local map
    /// @param[out] loopKeyframeIds list of pair of keyframe IDs (local map query keyframe and the detected global map loop keyframe)
    /// from these outputs, the loop path is defined as follows:
    /// detected global map loop keyframe -> globalMapClosestKeyframeId -> localMapFirstKeyframeId -> local map query keyframe -> detected global map loop keyframe
    /// @param[out] loopTransforms list of loop closure transforms
    /// @param[out] matchedPointIds list of matched cloud point IDs between the local map query keyframe and the detected global map loop keyframe
    /// @return FrameworkReturnCode::_SUCCESS if detect loop closures, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode detect(const std::vector<uint32_t>& localMapKeyframeIds,
                                       const std::vector<uint32_t>& initSubmapKeyframeIds,
                                       uint32_t& localMapFirstKeyframeId,
                                       uint32_t& globalMapClosestKeyframeId,
                                       std::vector<std::pair<uint32_t, uint32_t>>& loopKeyframeIds,
                                       std::vector<SolAR::datastructure::Transform3Df>& loopTransforms,
                                       std::vector<std::vector<std::pair<uint32_t, uint32_t>>>& matchedPointIds) const = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::loop::ILoopClosureDetector,
                             "a267c93a-c1c6-11ea-b3de-0242ac130004",
                             "ILoopClosureDetector",
                             "SolAR::api::loop::ILoopClosureDetector interface for a loop closure detection.");

#endif // ILOOPCLOSUREDETECTOR_H
