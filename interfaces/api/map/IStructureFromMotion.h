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

#ifndef ISTRUCTUREFROMMOTION_H
#define ISTRUCTUREFROMMOTION_H

#include "api/map/IMapFromImageProcessing.h"

namespace SolAR {
namespace api {
namespace map {

/**
 * @class IStructureFromMotion
 * @brief <B>Create a sparse point cloud and estimate camera poses from a set of images (Structure From Motion processing).</B>
 * <TT>UUID: 9e698509-dd26-4306-a093-173061b21d7f</TT>
 *
 */

class XPCF_IGNORE IStructureFromMotion : virtual public IMapFromImageProcessing
{
public:

    /// @enum class SFMProcessingStatus
    /// @brief define the different status of Structure From Motion processing
    enum class SFMProcessingStatus {
        NOT_DEFINED = 0,
        NOT_INITIALIZED,
        IDLE_INITIALIZED,
        IDLE_COMPLETED,
        IDLE_ABORTED,
        RUNNING_DESCRIPTOR_MATCHING,
        IDLE_DESCRIPTOR_MATCHING_FINISHED,
        RUNNING_INITIAL_MAPPING,
        IDLE_INITIAL_MAPPING_FINISHED,
        RUNNING_INCREMENTAL_MAPPING,
        IDLE_INCREMENTAL_MAPPING_FINISHED,
        RUNNING_POST_PROCESSING,
    };

    /// @brief return a string value of a SFMProcessingStatus value
    std::string toString(SFMProcessingStatus status) {
        switch (status) {
            case SFMProcessingStatus::NOT_DEFINED: return "NOT_DEFINED";
            case SFMProcessingStatus::NOT_INITIALIZED: return "NOT_INITIALIZED";
            case SFMProcessingStatus::IDLE_INITIALIZED: return "IDLE_INITIALIZED";
            case SFMProcessingStatus::IDLE_COMPLETED: return "IDLE_COMPLETED";
            case SFMProcessingStatus::IDLE_ABORTED: return "IDLE_ABORTED";
            case SFMProcessingStatus::RUNNING_DESCRIPTOR_MATCHING: return "RUNNING_DESCRIPTOR_MATCHING";
            case SFMProcessingStatus::IDLE_DESCRIPTOR_MATCHING_FINISHED: return "IDLE_DESCRIPTOR_MATCHING_FINISHED";
            case SFMProcessingStatus::RUNNING_INITIAL_MAPPING: return "RUNNING_INITIAL_MAPPING";
            case SFMProcessingStatus::IDLE_INITIAL_MAPPING_FINISHED: return "IDLE_INITIAL_MAPPING_FINISHED";
            case SFMProcessingStatus::RUNNING_INCREMENTAL_MAPPING: return "RUNNING_INCREMENTAL_MAPPINGRUNNING_INCREMENTAL_MAPPING";
            case SFMProcessingStatus::IDLE_INCREMENTAL_MAPPING_FINISHED: return "IDLE_INCREMENTAL_MAPPING_FINISHED";
            case SFMProcessingStatus::RUNNING_POST_PROCESSING: return "RUNNING_POST_PROCESSING";
            default: throw std::invalid_argument("SFMProcessingStatus value is unknown");
        }
    }

public:

    ///@brief IStructureFromMotion default constructor.
    IStructureFromMotion() = default;

    ///@brief IStructureFromMotion default destructor.
    virtual ~IStructureFromMotion() override = default;

    /// @brief Get current processing status
    /// @return status the current status
    virtual SFMProcessingStatus getStatus() const = 0;

};

} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::IStructureFromMotion,
                             "9e698509-dd26-4306-a093-173061b21d7f",
                             "IStructureFromMotion",
                             "IStructureFromMotion interface description");

#endif // ISTRUCTUREFROMMOTION_H
