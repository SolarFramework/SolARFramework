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

#include "xpcf/api/IComponentIntrospect.h"
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

class XPCF_CLIENTUUID("51f449f8-c9df-4c3a-ac57-7ca95debfdbc") XPCF_SERVERUUID("7dc30f5b-c61f-4eea-81d9-265a2a2b3b93") ILoopCorrector :
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
    virtual FrameworkReturnCode correct(const SRef<SolAR::datastructure::Keyframe> queryKeyframe,
                                        const SRef<SolAR::datastructure::Keyframe> detectedLoopKeyframe,
                                        const SolAR::datastructure::Transform3Df & S_wl_wc,
                                        const std::vector<std::pair<uint32_t, uint32_t>> & duplicatedPointsIndices) = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::loop::ILoopCorrector,
                             "8f05eea8-c1c6-11ea-b3de-0242ac130004",
                             "ILoopCorrector",
                             "SolAR::api::loop::ILoopCorrector interface for loop closure correction.");

#endif // ILOOPCORRECTOR_H
