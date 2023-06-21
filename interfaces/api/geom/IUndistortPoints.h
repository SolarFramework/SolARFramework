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
#include "datastructure/Keypoint.h"

namespace SolAR {
namespace api {
namespace geom {

/**
 * @class IUndistortPoints
 * @brief <B>Applies an undistorsion to a set of points.</B>
 * <TT>UUID: a345a1d2-c3f3-497f-948b-cd1a199e6657</TT>
 */

class XPCF_CLIENTUUID("9833188d-b7c6-4600-9032-35b0c4119eea") XPCF_SERVERUUID("def64009-6792-4e4f-b467-d17309232147") IUndistortPoints :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IUndistortPoints default constructor
    IUndistortPoints() = default;

    /// @brief IUndistortPoints default destructor
    virtual ~IUndistortPoints() = default;

    /// @brief This method corrects undistortsion to a set of 2D points
    /// @param[in] inputPoints the set of 2D points to correct
    /// @param[in] camParams the camera parameters
    /// @param[out] outputPoints the  undistorted 2D Points
    /// @return FrameworkReturnCode::_SUCCESS_ if 2D transformation succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode undistort(const std::vector<SolAR::datastructure::Point2Df> & inputPoints,
                                          const SolAR::datastructure::CameraParameters & camParams,
                                          std::vector<SolAR::datastructure::Point2Df> & outputPoints) = 0;

	/// @brief This method corrects undistortsion to a set of 2D keypoints
	/// @param[in] inputKeypoints the set of 2D keypoints to correct
    /// @param[in] camParams the camera parameters
	/// @param[out] outputKeypoints the  undistorted 2D keypoints
	/// @return FrameworkReturnCode::_SUCCESS_ if 2D transformation succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode undistort(const std::vector<SolAR::datastructure::Keypoint> & inputKeypoints,
                                          const SolAR::datastructure::CameraParameters & camParams,
                                          std::vector<SolAR::datastructure::Keypoint> & outputKeypoints) = 0;

};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::geom::IUndistortPoints,
                             "a345a1d2-c3f3-497f-948b-cd1a199e6657",
                             "IUndistortPoints",
                             "SolAR::api::geom::IUndistortPoints");


#endif //SOLAR_IUNDISTORT_POINTS_H

