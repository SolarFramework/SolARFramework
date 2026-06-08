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

#ifndef I3DGAUSSIANSPLATTING_H
#define I3DGAUSSIANSPLATTING_H

#include <api/map/IProcessMap.h>

namespace SolAR {
namespace api {
namespace map {

/**
 * @class I3DGaussianSplatting
 * @brief <B>Create and add 3D Gaussian Splatting data from/to a sparse map.</B>
 * <TT>UUID: e796c53f-41b5-4392-8027-9261086e4662</TT>
 *
 */

class XPCF_IGNORE I3DGaussianSplatting : virtual public IProcessMap
{
public:

    /// @enum class GSProcessingStatus
    /// @brief define the different status of processing
    enum class GSProcessingStatus: std::underlying_type_t<ProcessingStatus> {
    };

    /// @brief return a string value of a ProcessingStatus value
    std::string toString(ProcessingStatus status) override {
        switch ((ProcessingStatus)status) {
        case ProcessingStatus::NOT_DEFINED: return "NOT_DEFINED";
        case ProcessingStatus::NOT_INITIALIZED: return "NOT_INITIALIZED";
        case ProcessingStatus::IDLE_INITIALIZED: return "IDLE_INITIALIZED";
        case ProcessingStatus::IDLE_COMPLETED: return "IDLE_COMPLETED";
        case ProcessingStatus::IDLE_ABORTED: return "IDLE_ABORTED";
        default: return "NOT_DEFINED";
        }
    }

public:
    ///@brief I3DGaussianSplatting default constructor.
    I3DGaussianSplatting() = default;

    ///@brief I3DGaussianSplatting default destructor.
    virtual ~I3DGaussianSplatting() override = default;

};


} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::I3DGaussianSplatting,
                             "e796c53f-41b5-4392-8027-9261086e4662",
                             "I3DGaussianSplatting",
                             "I3DGaussianSplatting interface description");

#endif // I3DGAUSSIANSPLATTING_H
