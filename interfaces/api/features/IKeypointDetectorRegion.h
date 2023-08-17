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

#ifndef SOLAR_IKEYPOINTDETECTORREGION_H
#define SOLAR_IKEYPOINTDETECTORREGION_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <memory>
#include <vector>

#include "core/Messages.h"
#include "datastructure/Image.h"
#include "datastructure/Keypoint.h"
#include "api/features/IKeypointDetector.h"
#include <xpcf/core/helpers.h>

// Definition of IKeypointDetector Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"

namespace SolAR {
namespace api {
namespace features {

/**
 * @class IKeypointDetectorRegion
 * @brief <B>Detects the keypoints from given region of an image.</B>
 * <TT>UUID: 64ccce51-b445-4ec5-a0fa-44156e8bc370</TT>
 *
 * This class provides a method to detect the keypoint from an given region of an image using different kind of method (SURF, ORB, SIFT, etc.).
 */
class XPCF_CLIENTUUID("984ae965-bc03-42d4-8acd-7dcb4e9ac4aa") XPCF_SERVERUUID("ecce7865-2ae3-4b51-b267-28067beb742c") IKeypointDetectorRegion :
    virtual public org::bcom::xpcf::IComponentIntrospect {

public:
    /// @brief IKeypointDetectorRegion default constructor
    IKeypointDetectorRegion() = default;

    /// @brief IKeypointDetector default destructor
    virtual ~IKeypointDetectorRegion() = default;

    /// @brief Set the type of method used to detect keypoints in the image
    /// @param[in] type The type of method used to detect keypoints.
    virtual void setType(SolAR::api::features::IKeypointDetector::KeypointDetectorType type) = 0;

    /// @brief Get the type of method used to detect keypoints in the image
    /// @return The type of method used to detect keypoints.
    virtual SolAR::api::features::IKeypointDetector::KeypointDetectorType  getType() = 0;

    /// @brief This method detects keypoints in an input Image
    /// @param[in] image input image on which we are extracting keypoints.
    /// @param[in] contours a set of 2D points defining the contour of the region where keypoints will be detected
    /// @param[out] keypoints The keypoints detected from the given region of the image passed as first argument.
    virtual void detect (const SRef<SolAR::datastructure::Image> image,
                         const std::vector<SolAR::datastructure::Point2Df> & contours,
                         std::vector<SolAR::datastructure::Keypoint> & keypoints) = 0;
};

}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IKeypointDetectorRegion,
                             "64ccce51-b445-4ec5-a0fa-44156e8bc370",
                             "IKeypointDetector",
                             "SolAR::api::features::IKeypointDetectorRegion");

#endif // SOLAR_IKEYPOINTDETECTORREGION_H
