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

#ifndef I3DGAUSSIANSPLATTINGDENSIFIER_H
#define I3DGAUSSIANSPLATTINGDENSIFIER_H

#include <api/map/IProcessMap.h>

namespace SolAR {
namespace api {
namespace map {

/**
 * @class I3DGaussianSplattingDensifier
 * @brief <B>Convert a trained 3D Gaussian Splatting map into a dense coloured point cloud map.</B>
 * <TT>UUID: 44f7f040-4d38-4dcc-8e0f-a6580a93b8b0</TT>
 *
 * Mirrors I3DGaussianSplatting: it consumes a map whose point cloud carries one Gaussian
 * per CloudPoint (means/featuresDc/normal/featuresRest/opacity/scale/quat) and produces a
 * new map holding a dense, sampled point cloud (plain xyz + rgb CloudPoints). It does not
 * perform any training: the input Gaussian map is assumed to be already trained.
 *
 */

class XPCF_IGNORE I3DGaussianSplattingDensifier : virtual public IProcessMap
{
public:

    /// @enum class DensifyProcessingStatus
    /// @brief define the different status of 3DGS-to-point-cloud densification.
    /// Values chain on after the base IProcessMap::ProcessingStatus (which ends at 4),
    /// starting at 5, mirroring GSProcessingStatus.
    enum class DensifyProcessingStatus: std::underlying_type_t<ProcessingStatus> {
        RUNNING_LOAD = 5,           ///< reading the Gaussian model from the input map
        IDLE_LOAD_FINISHED,         ///< Gaussian model loaded
        RUNNING_SAMPLING,           ///< sampling dense points from the Gaussians
        IDLE_SAMPLING_FINISHED,     ///< sampling finished
        RUNNING_EXPORT,             ///< building the output map from the dense points
    };

    /// @brief return a string value of a ProcessingStatus value
    std::string toString(ProcessingStatus status) {
        switch (static_cast<DensifyProcessingStatus>(status)) {
            case DensifyProcessingStatus::RUNNING_LOAD:            return "RUNNING_LOAD";
            case DensifyProcessingStatus::IDLE_LOAD_FINISHED:      return "IDLE_LOAD_FINISHED";
            case DensifyProcessingStatus::RUNNING_SAMPLING:        return "RUNNING_SAMPLING";
            case DensifyProcessingStatus::IDLE_SAMPLING_FINISHED:  return "IDLE_SAMPLING_FINISHED";
            case DensifyProcessingStatus::RUNNING_EXPORT:          return "RUNNING_EXPORT";
            default: return IProcessMap::toString(status);
        }
    }

public:
    ///@brief I3DGaussianSplattingDensifier default constructor.
    I3DGaussianSplattingDensifier() = default;

    ///@brief I3DGaussianSplattingDensifier default destructor.
    virtual ~I3DGaussianSplattingDensifier() override = default;

};


} // namespace map
} // namespace api
} // namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::map::I3DGaussianSplattingDensifier,
                             "44f7f040-4d38-4dcc-8e0f-a6580a93b8b0",
                             "I3DGaussianSplattingDensifier",
                             "I3DGaussianSplattingDensifier interface description");

#endif // I3DGAUSSIANSPLATTINGDENSIFIER_H
