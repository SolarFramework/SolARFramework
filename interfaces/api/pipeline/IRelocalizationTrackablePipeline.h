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

#ifndef SOLAR_RELOCALIZATIONTRACKABLEPIPELINE_H
#define SOLAR_RELOCALIZATIONTRACKABLEPIPELINE_H


#include "api/pipeline/IRelocalizationPipeline.h"
#include <xpcf/core/helpers.h>

namespace SolAR {
using namespace datastructure;
namespace api {
namespace pipeline {

/**
 * @class IRelocalizationTrackablePipeline
 * @brief <B>Defines a relocalization pipeline based on trackable objects.</B>
 * <TT>UUID: c80e2716-e78d-42c3-ae94-a57ac517bc50</TT>
 *
 * This class provides the interface to define a relocalization processing pipeline based on trackable objects.
 */

class XPCF_CLIENTUUID("76636689-a511-4fee-8c51-bf951147d513") XPCF_SERVERUUID("7dbb07bb-afe0-4ed0-add8-653d46243466")
    XPCF_GRPC_CLIENT_RECV_SIZE("-1") XPCF_GRPC_CLIENT_SEND_SIZE("-1")
    IRelocalizationTrackablePipeline : virtual public IRelocalizationPipeline {
public:
    /// @brief IRelocalizationTrackablePipeline default constructor
    IRelocalizationTrackablePipeline() = default;

    /// @brief IRelocalizationTrackablePipeline default destructor
    virtual ~IRelocalizationTrackablePipeline() = default;

    using IPipeline::init;

    using IPipeline::start;

    using IPipeline::stop;

    using IRelocalizationPipeline::init;

    using IRelocalizationPipeline::start;

    using IRelocalizationPipeline::stop;

    using IRelocalizationPipeline::setCameraParameters;

    using IRelocalizationPipeline::getCameraParameters;

    using IRelocalizationPipeline::relocalizeProcessRequest;

    /// @brief Initialization of the pipeline with the list of trackable objects to use for localization
    /// @param[in] clientUUID the UUID of the current client
    /// @param[in] trackableObjects the list of the trackable objects to detect in images
    /// @return FrameworkReturnCode::_SUCCESS if the init succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode init(const std::string & clientUUID,
                                     const std::vector<SRef<Trackable>> & trackableObjects) = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IRelocalizationTrackablePipeline,
                             "c80e2716-e78d-42c3-ae94-a57ac517bc50",
                             "IRelocalizationTrackablePipeline",
                             "The interface to define a relocalization processing pipeline based on trackable objects")

#endif // SOLAR_RELOCALIZATIONTRACKABLEPIPELINE_H
