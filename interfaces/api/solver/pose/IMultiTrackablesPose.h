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

#ifndef SOLAR_IMULTITRACKABLESPOSE_H
#define SOLAR_IMULTITRACKABLESPOSE_H

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
 * @class IMultiTrackablesPose
 * @brief <B>Estimate camera pose based on a set of given trackables.</B>
 * <TT>UUID: f22cede0-e638-403f-9dfc-d2c1bd15cf83</TT>
 */
class [[xpcf::clientUUID("cf2959b3-cc73-46fa-8082-0809a3a2dcd3")]] [[xpcf::serverUUID("85daed2c-bd7d-4636-8321-b5f22e22ae11")]] IMultiTrackablesPose :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief IMultiTrackablesPose default constructor.
    IMultiTrackablesPose() = default;

    ///@brief IMultiTrackablesPose default destructor.
    virtual ~IMultiTrackablesPose() = default;

    /// @brief this method is used to set the set of trackables used to estimate the pose.
    /// @param[in] trackables the set of trackables used to estimate the pose.
    virtual FrameworkReturnCode setTrackables(const std::vector<SRef<SolAR::datastructure::Trackable>> trackables) =0;

    /// @brief Estimates camera pose based on a set of trackables.
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

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::IMultiTrackablesPose,
                             "f22cede0-e638-403f-9dfc-d2c1bd15cf83",
                             "IMultiTrackablesPose",
                             "SolAR::api::solver::pose::IMultiTrackablesPose");
                            
#endif // SOLAR_IMULTITRACKABLESPOSE_H
