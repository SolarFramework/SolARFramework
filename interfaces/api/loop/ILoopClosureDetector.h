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
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::loop::ILoopClosureDetector,
                             "a267c93a-c1c6-11ea-b3de-0242ac130004",
                             "ILoopClosureDetector",
                             "SolAR::api::loop::ILoopClosureDetector interface for a loop closure detection.");

#endif // ILOOPCLOSUREDETECTOR_H
