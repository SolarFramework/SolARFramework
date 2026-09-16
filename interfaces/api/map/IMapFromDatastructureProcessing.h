/**
 * @copyright Copyright (c) 2026 B-com http://www.b-com.com/
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

#ifndef IMAPFROMDATASTRUCTUREPROCESSING_H
#define IMAPFROMDATASTRUCTUREPROCESSING_H

#include "api/datastructure/IDatastructureFromDatastructureProcessing.h"
#include "datastructure/Map.h"

namespace SolAR {
namespace api {
namespace map {

/**
 * @class IMapFromDatastructureProcessing
 * @brief <B>Abstract class defining a generic base interface for interfaces that specify processing on SolAR datastructure in order to generate a new SolAR map.</B>
 * <TT>UUID: 09186a13-ba08-4a93-9e79-2c9116fb2377</TT>
 *
 */

class XPCF_IGNORE IMapFromDatastructureProcessing : virtual public SolAR::api::datastructure::IDatastructureFromDatastructureProcessing
{

public:

    ///@brief IMapFromDatastructureProcessing default destructor.
    virtual ~IMapFromDatastructureProcessing() override = default;

    /// @brief Get current cloud points
    /// @param[out] cloudPoints current point cloud consisting of a number of 3D points
    /// @return FrameworkReturnCode::_SUCCESS if points was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCurrentCloudPoints(std::vector<SRef<SolAR::datastructure::CloudPoint>>& cloudPoints) const = 0;

    /// @brief Get current keyframe poses
    /// @param[out] keyframePoses current keyframes' poses
    /// @return FrameworkReturnCode::_SUCCESS if keyframe was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCurrentKeyframePoses(std::vector<SolAR::datastructure::Transform3Df>& keyframePoses) const = 0;

    /// @brief Get output map resulting from processing
    /// @param[out] map the output map
    /// @return FrameworkReturnCode::_SUCCESS if map was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getOutputMap(SRef<SolAR::datastructure::Map>& map) const = 0;

};

} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::IMapFromDatastructureProcessing,
                             "09186a13-ba08-4a93-9e79-2c9116fb2377",
                             "IMapFromDatastructureProcessing",
                             "IMapFromDatastructureProcessing interface description");

#endif // IMAPFROMDATASTRUCTUREPROCESSING_H
