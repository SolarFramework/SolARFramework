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

#include <api/map/IMapFromMapProcessing.h>

namespace SolAR {
namespace api {
namespace map {

/**
 * @class I3DGaussianSplatting
 * @brief <B>Create and add 3D Gaussian Splatting data from/to a sparse map.</B>
 * <TT>UUID: e796c53f-41b5-4392-8027-9261086e4662</TT>
 *
 */

class XPCF_IGNORE I3DGaussianSplatting : virtual public IMapFromMapProcessing
{
public:

    /// @enum class GSProcessingStatus
    /// @brief define the different status of 3D Gaussian Splatting processing.
    enum class GSProcessingStatus {
        NOT_DEFINED = 0,
        NOT_INITIALIZED,
        IDLE_INITIALIZED,
        IDLE_COMPLETED,
        IDLE_ABORTED,
        RUNNING_INITIALIZATION,     ///< seeding the Gaussian model from the input map
        IDLE_INITIALIZATION_FINISHED,   ///< Gaussian model initialized
        RUNNING_TRAINING,               ///< optimizing the Gaussians (forward/backward/densify)
        IDLE_TRAINING_FINISHED,         ///< optimization finished
        RUNNING_EXPORT,                 ///< building the output map from the trained Gaussians
    };

    /// @brief return a string value of a GSProcessingStatus value
    std::string toString(GSProcessingStatus status) {
        switch (status) {
            case GSProcessingStatus::NOT_DEFINED: return "NOT_DEFINED";
            case GSProcessingStatus::NOT_INITIALIZED: return "NOT_INITIALIZED";
            case GSProcessingStatus::IDLE_INITIALIZED: return "IDLE_INITIALIZED";
            case GSProcessingStatus::IDLE_COMPLETED: return "IDLE_COMPLETED";
            case GSProcessingStatus::IDLE_ABORTED: return "IDLE_ABORTED";
            case GSProcessingStatus::RUNNING_INITIALIZATION: return "RUNNING_INITIALIZATION";
            case GSProcessingStatus::IDLE_INITIALIZATION_FINISHED: return "IDLE_INITIALIZATION_FINISHED";
            case GSProcessingStatus::RUNNING_TRAINING: return "RUNNING_TRAINING";
            case GSProcessingStatus::IDLE_TRAINING_FINISHED: return "IDLE_TRAINING_FINISHED";
            case GSProcessingStatus::RUNNING_EXPORT: return "RUNNING_EXPORT";
            default: throw std::invalid_argument("GSProcessingStatus value is unknown");
        }
    }

public:

    ///@brief I3DGaussianSplatting default constructor.
    I3DGaussianSplatting() = default;

    ///@brief I3DGaussianSplatting default destructor.
    virtual ~I3DGaussianSplatting() override = default;

    /// @brief Get current processing status
    /// @return status the current status
    virtual GSProcessingStatus getStatus() const = 0;

};


} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::I3DGaussianSplatting,
                             "e796c53f-41b5-4392-8027-9261086e4662",
                             "I3DGaussianSplatting",
                             "I3DGaussianSplatting interface description");

#endif // I3DGAUSSIANSPLATTING_H
