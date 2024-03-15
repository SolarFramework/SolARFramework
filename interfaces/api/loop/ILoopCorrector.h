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

#ifndef ILOOPCORRECTOR_H
#define ILOOPCORRECTOR_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "datastructure/MathDefinitions.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Keyframe.h"
#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace loop{

/**
  * @class ILoopCorrector
  * @brief <B>Optimizes a system of 3D points and keyframes from a loop closing detection. </B>
  * <TT>UUID: 8f05eea8-c1c6-11ea-b3de-0242ac130004</TT>
  */

class XPCF_IGNORE ILoopCorrector :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief ILoopCorrector default constructor
    ILoopCorrector() = default;

    ///@brief ILoopCorrector default destructor
    virtual ~ILoopCorrector() = default;

    /// @brief corrects a loop of keyframes and their associated point clouds from a loop detection result.
    /// @param[in] queryKeyframe: the query keyframe.
    /// @param[in] detectedLoopKeyframe: the detected loop keyframe.
    /// @param[in] S_wl_wc: 3D similarity transformation (Sim(3)) from world c.s of the query
    /// keyframe to world c.s of the loop detected keyframe
    /// @param[in] duplicatedPointsIndices: indices of duplicated cloud points.
    /// The first index is the id of point cloud seen from the detected loop keyframe.
    /// The second one is id of point cloud seen from the query keyframe
    /// @return FrameworkReturnCode::_SUCCESS if loop closure is correctly corrected, else FrameworkReturnCode::_ERROR_
    [[deprecated]]
    virtual FrameworkReturnCode correct(const SRef<SolAR::datastructure::Keyframe> queryKeyframe,
                                        const SRef<SolAR::datastructure::Keyframe> detectedLoopKeyframe,
                                        const SolAR::datastructure::Transform3Df & S_wl_wc,
                                        const std::vector<std::pair<uint32_t, uint32_t>> & duplicatedPointsIndices) = 0;

    /// @brief corrects a loop of keyframes and their associated point clouds from a loop detection result.
    /// @param[in] queryKeyframe: the query keyframe.
    /// @param[in] detectedLoopKeyframe: the detected loop keyframe.
    /// @param[in] S_wl_wc: 3D similarity transformation (Sim(3)) from world c.s of the query
    /// keyframe to world c.s of the loop detected keyframe
    /// @param[in] duplicatedPointsIndices: indices of duplicated cloud points.
    /// The first index is the id of point cloud seen from the detected loop keyframe.
    /// The second one is id of point cloud seen from the query keyframe
    /// @param[out] correctedKeyframeIds: list of corrected keyframes' IDs (of which pose has been modified in the method)
    /// @param[out] correctedCloudpointIds: list of corrected cloud points' IDs (of which spatial coordinates has been modified in the method) 
    /// @return FrameworkReturnCode::_SUCCESS if loop closure is correctly corrected, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode correct(const SRef<SolAR::datastructure::Keyframe> queryKeyframe,
                                        const SRef<SolAR::datastructure::Keyframe> detectedLoopKeyframe,
                                        const SolAR::datastructure::Transform3Df & S_wl_wc,
                                        const std::vector<std::pair<uint32_t, uint32_t>> & duplicatedPointsIndices,
                                        std::vector<uint32_t>& correctedKeyframeIds, 
                                        std::vector<uint32_t>& correctedCloudpointIds) = 0;

    /// @brief corrects keyframes and their associated cloud points from loops detected after map fusion.
    /// @param[in] loopKeyframeIds: list of pairs of keyframe IDs (local map and global map keyframes between which loop is detected)
    /// @param[in] loopTransforms: list of estimated loop transform from local map keyframe to global map keyframe
    /// @param[in] matchedPointIds: list of matched cloud point IDs between local map and global map keyframes 
    /// @param[in] localMapFirstKeyframeId: ID of the first keyframe from local map (all other local map keyframes' IDs are greater than this value)
    virtual FrameworkReturnCode correct(const std::vector<std::pair<uint32_t, uint32_t>>& loopKeyframeIds,
                                        const std::vector<SolAR::datastructure::Transform3Df>& loopTransforms,
                                        const std::vector<std::vector<std::pair<uint32_t, uint32_t>>>& matchedPointIds,
                                        const uint32_t& localMapFirstKeyframeId) = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::loop::ILoopCorrector,
                             "8f05eea8-c1c6-11ea-b3de-0242ac130004",
                             "ILoopCorrector",
                             "SolAR::api::loop::ILoopCorrector interface for loop closure correction.");

#endif // ILOOPCORRECTOR_H
