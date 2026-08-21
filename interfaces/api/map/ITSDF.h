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

#include "api/map/IProcessMap.h"

namespace SolAR {
namespace api {
namespace map {

/**
 * @class ITSDF
 * @brief <B>Densifies a SolAR map by fusing per-keyframe depth into a TSDF volume.</B>
 * <TT>UUID: 50ff3d84-a327-49da-8a8f-8fcedfe67db9</TT>
 *
 * A map-processing component (see SolAR::api::map::IProcessMap) that takes a SolAR
 * Map carrying posed keyframes (images + poses + camera parameters) together with a
 * sparse point cloud, estimates a dense depth map for each keyframe (typically with an
 * embedded monocular depth estimator such as Depth-Anything, regularized over the
 * keyframe trajectory and scale-aligned to the sparse points), and volumetrically fuses
 * those RGB-D frames into a Truncated Signed Distance Function (TSDF) voxel volume.
 * The isosurface extracted from the volume yields a much denser coloured point cloud,
 * returned as a new SolAR Map through getOutputMap().
 *
 * Like the other IProcessMap specializations, the processing is driven by createMap()
 * and polled through getStatus()/getProgress().
 */
class XPCF_IGNORE ITSDF : virtual public IProcessMap
{
public:
    /// @brief Extends IProcessMap::ProcessingStatus with TSDF-specific steps.
    /// Values continue after the base enum (which ends at 4).
    enum class TSDFProcessingStatus : std::underlying_type_t<ProcessingStatus> {
        RUNNING_LOAD = 5,             ///< Reading keyframes / camera parameters from the input map
        IDLE_LOAD_FINISHED,           ///< Input map loaded
        RUNNING_DEPTH_ESTIMATION,     ///< Estimating + regularizing per-keyframe depth maps
        RUNNING_INTEGRATION,          ///< Integrating RGB-D frames into the TSDF volume
        IDLE_INTEGRATION_FINISHED,    ///< Volume fully integrated
        RUNNING_EXTRACTION,           ///< Extracting the dense point cloud from the volume
        RUNNING_EXPORT                ///< Building / exporting the output map
    };

    /// @brief ITSDF default constructor
    ITSDF() = default;

    /// @brief ITSDF default destructor
    virtual ~ITSDF() override = default;

    /// @brief Human readable text for a processing status, including the TSDF-specific
    /// steps; falls back to IProcessMap::toString for the inherited base statuses.
    std::string toString(ProcessingStatus status) {
        switch (static_cast<TSDFProcessingStatus>(status)) {
        case TSDFProcessingStatus::RUNNING_LOAD:                return "RUNNING_LOAD";
        case TSDFProcessingStatus::IDLE_LOAD_FINISHED:          return "IDLE_LOAD_FINISHED";
        case TSDFProcessingStatus::RUNNING_DEPTH_ESTIMATION:    return "RUNNING_DEPTH_ESTIMATION";
        case TSDFProcessingStatus::RUNNING_INTEGRATION:         return "RUNNING_INTEGRATION";
        case TSDFProcessingStatus::IDLE_INTEGRATION_FINISHED:   return "IDLE_INTEGRATION_FINISHED";
        case TSDFProcessingStatus::RUNNING_EXTRACTION:          return "RUNNING_EXTRACTION";
        case TSDFProcessingStatus::RUNNING_EXPORT:              return "RUNNING_EXPORT";
        default: return IProcessMap::toString(status);
        }
    }
};

} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::ITSDF,
                             "50ff3d84-a327-49da-8a8f-8fcedfe67db9",
                             "ITSDF",
                             "ITSDF interface description");

#endif // ITSDF_H
