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

#ifndef SOLAR_IKEYPOINTDETECTOR_H
#define SOLAR_IKEYPOINTDETECTOR_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <memory>
#include <vector>

#include "core/Messages.h"
#include "datastructure/Image.h"
#include "datastructure/Keypoint.h"

// Definition of IKeypointDetector Class //
// part of SolAR namespace //

#include "IComponentIntrospect.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace features {
///
/// \brief KeypointDetectorType enum
/// This enum is used to define the type of an IKeypointDetector object
///
    enum class KeypointDetectorType {
		SURF,
		ORB,
		SIFT,
		DAISY,
		LATCH,
		AKAZE,
		AKAZE2,
		AKAZEUP,
		BRISK,
		BRIEF,
	};


/**
 * @class IKeypointDetector
 * @brief detects the keypoints from an image
 *
 * This class provides a method to detect the keypoint from an image using different kind of method (SURF, ORB, SIFT, etc.).
 */
class  IKeypointDetector : public virtual org::bcom::xpcf::IComponentIntrospect {

public:
    /// @brief IKeypointDetector default constructor
    IKeypointDetector() = default;

    /// @brief IKeypointDetector default destructor
    virtual ~IKeypointDetector() {};

    /// @brief Set the type of method used to detect keypoints in the image
    /// @param[in] type The type of method used to detect keypoints.
    virtual void setType(KeypointDetectorType type) = 0;

    /// @brief Get the type of method used to detect keypoints in the image
    /// @return The type of method used to detect keypoints.
    virtual KeypointDetectorType  getType() = 0;

    /// @brief This method detects keypoints in an input Image
    /// @param[in] image input image on which we are extracting keypoints.
    /// @param[out] keypoints The keypoints detected from the image passed as first argument.
    virtual void detect (const SRef<Image> &image, std::vector<SRef<Keypoint>> &keypoints) = 0;

    XPCF_DECLARE_UUID("0eadc8b7-1265-434c-a4c6-6da8a028e06e");
};

}
}
}  // end of namespace SolAR

#endif // SOLAR_IKEYPOINTDETECTOR_H
