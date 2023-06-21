/**
 * @copyright Copyright (c) 2017 B-com http://www.b-com.com/
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

#ifndef SOLAR_ITrackablePose_H
#define SOLAR_ITrackablePose_H

#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Trackable.h"
#include "core/Messages.h"

#include "datastructure/CameraDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Image.h"

namespace SolAR {
namespace api {
namespace solver {
namespace pose {
/**
 * @class ITrackablePose
 * @brief <B>Estimate camera pose based on a given trackable.</B>
 * <TT>UUID: d5247968-b74e-4afb-9abd-546021441ad4</TT>
 */
class XPCF_CLIENTUUID("ad79b898-f2b0-446f-835e-7daf3458fe50") XPCF_SERVERUUID("cd7858b0-0bfa-4ece-b16a-3e02fa309495") ITrackablePose :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief ITrackablePose default constructor.
    ITrackablePose() = default;

    ///@brief ITrackablePose default destructor.
    virtual ~ITrackablePose() = default;

    /// @brief this method is used to set the trackable used to estimate the pose.
    /// @param[in] the trackable used to estimate the pose.
    virtual FrameworkReturnCode setTrackable(const SRef<SolAR::datastructure::Trackable> trackable) =0;

    /// @brief Estimates camera pose based on a fiducial marker.
    /// @param[in] image input image.
    /// @param[in] camParams the camera parameters.
    /// @param[out] pose camera pose.
    /// @return FrameworkReturnCode::_SUCCESS if the estimation succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode estimate(const SRef<SolAR::datastructure::Image> image,
                                         const SolAR::datastructure::CameraParameters & camParams,
                                         SolAR::datastructure::Transform3Df & pose) =0;

};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::ITrackablePose,
                             "d5247968-b74e-4afb-9abd-546021441ad4",
                             "ITrackablePose",
                             "SolAR::api::solver::pose::ITrackablePose");
                            
#endif // SOLAR_ITrackablePose_H
