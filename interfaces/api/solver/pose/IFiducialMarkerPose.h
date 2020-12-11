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

#ifndef SOLAR_IFIDUCIALMARKERPOSE_H
#define SOLAR_IFIDUCIALMARKERPOSE_H

#include "xpcf/api/IComponentIntrospect.h"
#include "api/input/files/IMarker2DSquaredBinary.h"
#include "datastructure/FiducialMarker.h"
#include "core/Messages.h"

#include "datastructure/CameraDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Image.h"

namespace SolAR {
namespace api {
namespace solver {
namespace pose {
/**
 * @class IFiducialMarkerPose
 * @brief <B>Estimate camera pose based on a fiducial marker.</B>
 * <TT>UUID: d5247968-b74e-4afb-9abd-546021441ad4</TT>
 */
    class IFiducialMarkerPose : virtual public org::bcom::xpcf::IComponentIntrospect {
    public:
        ///@brief IFiducialMarkerPose default constructor.
        IFiducialMarkerPose() = default;

        ///@brief IFiducialMarkerPose default destructor.
        virtual ~IFiducialMarkerPose() = default;

        /// @brief this method is used to set intrinsic parameters and distorsion of the camera
        /// @param[in] intrinsicParams camera calibration matrix parameters.
        /// @param[in] distorsionParams camera distorsion parameters.
        virtual void setCameraParameters(const datastructure::CamCalibration & intrinsicParams, const datastructure::CamDistortion & distorsionParams) = 0;

        /// @brief this method is used to set the fiducial marker
        /// @param[in] Fiducial marker.
        virtual void setMarker(const SRef<api::input::files::IMarker2DSquaredBinary> & marker) =0;

        /// @brief this method is used to set the fiducial marker
        /// @param[in] Fiducial marker.
        virtual void setMarker(const SRef<datastructure::FiducialMarker> & marker) =0;

        /// @brief Estimates camera pose based on a fiducial marker.
        /// @param[in] image: input image.
        /// @param[out] pose: camera pose.
		/// @return FrameworkReturnCode::_SUCCESS if the estimation succeed, else FrameworkReturnCode::_ERROR_
        virtual FrameworkReturnCode estimate(const SRef<datastructure::Image> &image,
                                             datastructure::Transform3Df & pose) =0;

    };

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::IFiducialMarkerPose,
                             "d5247968-b74e-4afb-9abd-546021441ad4",
                             "IFiducialMarkerPose",
                             "SolAR::api::solver::pose::IFiducialMarkerPose");
                            
#endif // SOLAR_IFIDUCIALMARKERPOSE_H
