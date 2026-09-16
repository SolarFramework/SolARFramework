/**
 * @copyright Copyright (c) 2024 B-com http://www.b-com.com/
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

#ifndef IRECTIFYMAP_H
#define IRECTIFYMAP_H

#include "core/Messages.h"
#include "datastructure/Map.h"
#include "api/map/IProcessMap.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace map {

/**
 * @class IRectifyMap
 * @brief <B>Create a sparse point cloud and estimate camera poses from a set of images or a set of descriptors stored inside the keyframes.</B>
 * <TT>UUID: 3681e09b-1704-4a08-b1cd-42d5a7c961b4</TT>
 *
 */

class XPCF_IGNORE IRectifyMap : virtual public IProcessMap
{
public:

    /// @enum class RectifyMapProcessingStatus
    /// @brief define the different status of processing
    enum class RectifyMapProcessingStatus: std::underlying_type_t<ProcessingStatus> {
        NOT_DEFINED,
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

    /// @brief return a string value of a ProcessingStatus value
    std::string toString(ProcessingStatus status) final {
        switch (static_cast<RectifyMapProcessingStatus>(status)) {
            case RectifyMapProcessingStatus::NOT_DEFINED: return "NOT_DEFINED";
            case RectifyMapProcessingStatus::NOT_INITIALIZED: return "NOT_INITIALIZED";
            case RectifyMapProcessingStatus::IDLE_INITIALIZED: return "IDLE_INITIALIZED";
            case RectifyMapProcessingStatus::IDLE_COMPLETED: return "IDLE_COMPLETED";
            case RectifyMapProcessingStatus::IDLE_ABORTED: return "IDLE_ABORTED";
            case RectifyMapProcessingStatus::RUNNING_DESCRIPTOR_MATCHING: return "RUNNING_DESCRIPTOR_MATCHING";
            case RectifyMapProcessingStatus::IDLE_DESCRIPTOR_MATCHING_FINISHED: return "IDLE_DESCRIPTOR_MATCHING_FINISHED";
            case RectifyMapProcessingStatus::RUNNING_INITIAL_MAPPING: return "RUNNING_INITIAL_MAPPING";
            case RectifyMapProcessingStatus::IDLE_INITIAL_MAPPING_FINISHED: return "IDLE_INITIAL_MAPPING_FINISHED";
            case RectifyMapProcessingStatus::RUNNING_INCREMENTAL_MAPPING: return "RUNNING_INCREMENTAL_MAPPINGRUNNING_INCREMENTAL_MAPPING";
            case RectifyMapProcessingStatus::IDLE_INCREMENTAL_MAPPING_FINISHED: return "IDLE_INCREMENTAL_MAPPING_FINISHED";
            case RectifyMapProcessingStatus::RUNNING_POST_PROCESSING: return "RUNNING_POST_PROCESSING";
            default: return IProcessMap::toString(status);
        }
    }

    ///@brief IRectifyMap default constructor.
    IRectifyMap() = default;

    ///@brief IRectifyMap default destructor.
    virtual ~IRectifyMap() override = default;

    /// @brief use the covisibility graph of input map during the map rectification
    void useCovisibilityGraphOn();

    /// @brief do not use the covisibility graph of input map during the map rectification
    void useCovisibilityGraphOff();

protected:
    bool m_useCovisibilityGraph = false;

};

} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::IRectifyMap,
                             "3681e09b-1704-4a08-b1cd-42d5a7c961b4",
                             "IRectifyMap",
                             "IRectifyMap interface description");

#endif // IRECTIFYMAP_H
