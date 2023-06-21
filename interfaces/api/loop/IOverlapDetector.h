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

#ifndef IOVERLAPDETECTOR_H
#define IOVERLAPDETECTOR_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Map.h"
#include "core/Messages.h"


namespace SolAR {
namespace api {
namespace loop {
/**
  * @class IOverlapDetector
  * @brief <B>Detects an overlap between different maps.</B>
  * <TT>UUID: fe6a40ca-137c-11eb-adc1-0242ac120002</TT>
  */

class XPCF_CLIENTUUID("ccc5e7f8-2f9c-4b2f-a7f1-f151a9aa2191") XPCF_SERVERUUID("1befd83d-c1b4-4bee-acab-5b63e371c788") IOverlapDetector :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief IOverlapDetector default constructor
    IOverlapDetector() = default;

    ///@brief IOverlapDetector default destructor
    virtual ~IOverlapDetector() = default;

    /// @brief Detect overlap between two floating maps with different refences.
    /// @param[in] globalMap global map as reference.
    /// @param[in] floatingMap floating map as the map to merge.
    /// @param[out] sim3Transform 3D similarity transformation (Sim(3)) from the floating map to the global map.
    /// @param[out] cpOverlapIndices pairs of detected overlap cloud points indices of floating map and global map.
    /// @return FrameworkReturnCode::_SUCCESS if detect a loop closure, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode detect(const SRef<SolAR::datastructure::Map> globalMap,
                                        const SRef<SolAR::datastructure::Map> floatingMap,
                                        SolAR::datastructure::Transform3Df & sim3Transform,
                                        std::vector<std::pair<uint32_t, uint32_t>> & cpOverlapIndices) const = 0;

    /// @brief Detect overlap between two floating maps with different refences.
    /// @param[in] globalMap global map as reference.
    /// @param[in] floatingMap floating map as the map to merge.
    /// @param[out] sim3Transform 3D similarity transformation (Sim(3)) from query keyframe from the floating map to the detected overlaped keyframe in global map.
    /// @param[out] overlapIndices pairs of detected overlap keyframe indices of floating map and global map.
    /// @param[out] scores : represent scores of overlap candidates.
    /// @return FrameworkReturnCode::_SUCCESS if detect a loop closure, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode detect(const SRef<SolAR::datastructure::Map> globalMap,
                                        const SRef<SolAR::datastructure::Map> floatingMap,
                                        std::vector<SolAR::datastructure::Transform3Df> & sim3Transform,
                                        std::vector<std::pair<uint32_t, uint32_t>> & overlapIndices,
                                        std::vector<double>&scores) const = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::loop::IOverlapDetector,
                             "fe6a40ca-137c-11eb-adc1-0242ac120002",
                             "IOverlapDetector",
                             "SolAR::api::loop::IOverlapDetector interface for different maps overlap detection.");

#endif // IOVERLAPDETECTOR_H
