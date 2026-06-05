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

#ifndef IPROCESSMAP_H
#define IPROCESSMAP_H

#include <xpcf/api/IComponentIntrospect.h>
#include "core/Messages.h"
#include "datastructure/Map.h"

namespace SolAR {
namespace api {
namespace map {

/**
 * @class IProcessMap
 * @brief <B>Abstract class defining a generic interface for all classes processing a map in order to generate a new one</B>
 * <TT>UUID: 61459738-7733-466d-919a-7d7abfbdc9e3</TT>
 *
 */

class XPCF_IGNORE IProcessMap : virtual public org::bcom::xpcf::IComponentIntrospect
{

public:

    /// @enum class ProcessingStatus
    /// @brief define the different status of processing
    /// @note this class should be extended in each derived class to define its own processing status
    enum class ProcessingStatus {
        NOT_DEFINED = 0,
        NOT_INITIALIZED,
        IDLE_INITIALIZED,
        IDLE_COMPLETED,
        IDLE_ABORTED, // To be extended in derived classes
    };

    /// @brief return a string value of a ProcessingStatus value
    virtual std::string toString(ProcessingStatus status) = 0;

public:

    ///@brief IProcessMap default destructor.
    virtual ~IProcessMap() override = default;

    /// @brief Create a new map resulting from the processing of the original map
    /// @param[in] map the original map
    /// @return FrameworkReturnCode::_SUCCESS if the processing succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode createMap(const SRef<SolAR::datastructure::Map>& map) = 0;

    /// @brief Get output map resulting from processing
    /// @param[out] map the output map
    /// @return FrameworkReturnCode::_SUCCESS if map was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getOutputMap(SRef<SolAR::datastructure::Map>& map) = 0;

    /// @brief Get current processing status
    /// @return status the current status
    virtual ProcessingStatus getStatus() = 0;

    /// @brief Get current processing progress percentage
    /// @return progress percentage between 0 and 1
    virtual float getProgress() = 0;

    /// @brief Get current cloud points
    /// @param[out] cloudPoints current point cloud consisting of a number of 3D points
    /// @return FrameworkReturnCode::_SUCCESS if points was successfully retrieved, otherwise FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getCurrentCloudPoints(std::vector<SRef<SolAR::datastructure::CloudPoint>>& cloudPoints) = 0;

    /// @brief force stop
    virtual void forceStop() = 0;

    /// @brief release memory usage
    virtual void releaseMemoryUsage() = 0;

};

} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::IProcessMap,
                             "61459738-7733-466d-919a-7d7abfbdc9e3",
                             "IProcessMap",
                             "IProcessMap interface description");

#endif // IPROCESSMAP_H
