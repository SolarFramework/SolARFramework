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

#ifndef SOLAR_IUNDISTORT_POINTS_H
#define SOLAR_IUNDISTORT_POINTS_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace geom {

/**
 * @class IUndistortPoints
 * @brief <B>Applies an undistorsion to a set of points.</B>
 * <TT>UUID: a345a1d2-c3f3-497f-948b-cd1a199e6657</TT>
 */

class IUndistortPoints : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IUndistortPoints default constructor
    IUndistortPoints() = default;

    /// @brief IUndistortPoints default destructor
    virtual ~IUndistortPoints() = default;

    /// @brief This method corrects undistortsion to a set of 2D points
    /// @param[in] inputPoints the set of 2D points to correct
    /// @param[out] outputPoints the  undistorted 2D Points
    /// @return FrameworkReturnCode::_SUCCESS_ if 2D transformation succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode undistort(const std::vector<Point2Df> & inputPoints,
                                          std::vector<Point2Df> & outputPoints) = 0;

    /// @brief Set the intrinsic camera parameters
    virtual void setIntrinsicParameters(const CamCalibration & intrinsic_parameters) = 0;
    
    /// @brief Set the distorsion intrinsic camera parameters
    virtual void setDistorsionParameters(const CamDistortion & distorsion_parameters) = 0;

};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::geom::IUndistortPoints,
                             "a345a1d2-c3f3-497f-948b-cd1a199e6657",
                             "IUndistortPoints",
                             "SolAR::api::geom::IUndistortPoints");


#endif //SOLAR_IUNDISTORT_POINTS_H

