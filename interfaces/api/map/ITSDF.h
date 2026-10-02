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

#ifndef ITSDF_H
#define ITSDF_H

#include "api/map/IMapFromMapProcessing.h"
#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include <stdexcept>
#include <string>

namespace SolAR {
namespace api {
namespace map {

/**
 * @class ITSDF
 * @brief <B>Densifies a map by fusing per-keyframe depth into a TSDF volume.</B>
 * <TT>UUID: 50ff3d84-a327-49da-8a8f-8fcedfe67db9</TT>
 */
class XPCF_IGNORE ITSDF : virtual public IMapFromMapProcessing, virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
    /// @enum class TSDFProcessingStatus
    /// @brief define the different status of TSDF processing.
    enum class TSDFProcessingStatus {
        NOT_DEFINED = 0,
        NOT_INITIALIZED,
        IDLE_INITIALIZED,
        IDLE_COMPLETED,
        IDLE_ABORTED,
        RUNNING_LOAD,                 ///< Reading keyframes / camera parameters from the input map
        IDLE_LOAD_FINISHED,           ///< Input map loaded
        RUNNING_DEPTH_ESTIMATION,     ///< Estimating per-keyframe depth maps
        RUNNING_INTEGRATION,          ///< Integrating RGB-D frames into the TSDF volume
        IDLE_INTEGRATION_FINISHED,    ///< Volume fully integrated
        RUNNING_EXTRACTION,           ///< Extracting the dense point cloud from the volume
        RUNNING_EXPORT                ///< Building the output map
    };

    /// @brief return a string value of a TSDFProcessingStatus value
    std::string toString(TSDFProcessingStatus status) {
        switch (status) {
            case TSDFProcessingStatus::NOT_DEFINED: return "NOT_DEFINED";
            case TSDFProcessingStatus::NOT_INITIALIZED: return "NOT_INITIALIZED";
            case TSDFProcessingStatus::IDLE_INITIALIZED: return "IDLE_INITIALIZED";
            case TSDFProcessingStatus::IDLE_COMPLETED: return "IDLE_COMPLETED";
            case TSDFProcessingStatus::IDLE_ABORTED: return "IDLE_ABORTED";
            case TSDFProcessingStatus::RUNNING_LOAD: return "RUNNING_LOAD";
            case TSDFProcessingStatus::IDLE_LOAD_FINISHED: return "IDLE_LOAD_FINISHED";
            case TSDFProcessingStatus::RUNNING_DEPTH_ESTIMATION: return "RUNNING_DEPTH_ESTIMATION";
            case TSDFProcessingStatus::RUNNING_INTEGRATION: return "RUNNING_INTEGRATION";
            case TSDFProcessingStatus::IDLE_INTEGRATION_FINISHED: return "IDLE_INTEGRATION_FINISHED";
            case TSDFProcessingStatus::RUNNING_EXTRACTION: return "RUNNING_EXTRACTION";
            case TSDFProcessingStatus::RUNNING_EXPORT: return "RUNNING_EXPORT";
            default: throw std::invalid_argument("TSDFProcessingStatus value is unknown");
        }
    }

public:

    /// @brief ITSDF default constructor
    ITSDF() = default;

    /// @brief ITSDF default destructor
    virtual ~ITSDF() override = default;

    /// @brief Get current processing status
    /// @return status the current status
    virtual TSDFProcessingStatus getStatus() const = 0;
};

} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::ITSDF,
                             "50ff3d84-a327-49da-8a8f-8fcedfe67db9",
                             "ITSDF",
                             "ITSDF interface description");

#endif // ITSDF_H
