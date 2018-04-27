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

#ifndef SOLAR_ISIDEBYSIDEDOVERLAY_H
#define SOLAR_ISIDEBYSIDEDOVERLAY_H

#include "datastructure/MathDefinitions.h"
#include "IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/Pose.h"
#include "datastructure/Keypoint.h"
#include "datastructure/SquaredBinaryPattern.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace display {
/**
 * @class ISideBySideOverlay
 * @brief Drawing interface to overlay matches between two images.
 *
 * This class provides drawing method to overlay matches between two images.
 */
class ISideBySideOverlay : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief ISideBySideOverlay default constructor
    ISideBySideOverlay() = default;

    /// @brief ISideBySideOverlay default destructor
    virtual ~ISideBySideOverlay() = default;

    /// @brief dra Match Lines.
    /// Draw all the lines joining the keypoints that match between two images
    /// @param[in] image1:  The first image on which have been extracted the first vector keypoints
    /// @param[in] image2: The second image on which have been extracted the second vector of keypoints
    /// @param[out] outImage: The resulting image merging image1 and image2 in side-by-side. If outImage has not been initialized, it will be done by this method. If it size is not the good one, it will be resized by this method.
    /// @param[in] points_image1: The keypoints of image1 that match with keypoints of image2. The Nth keypoint of this vector match with the Nth keypoint of the vector points_image2.
    /// @param[in] points_image2: The keypoints of image2 that match with keypoints of image1. The Nth keypoint of this vector match with the Nth keypoint of the vector points_image1.
    /// @param[in] matches_number: number of matches to display. if negative, all matches are displayed.
    virtual void drawMatchesLines(SRef<Image> & image1, SRef<Image> & image2, SRef<Image> & outImage, std::vector <SRef<Point2Df>> & points_image1, std::vector <SRef<Point2Df>> & points_image2, int matches_number = -1)=0;

    static constexpr const char * UUID = "a801354a-3e00-467c-b390-48c76fa8c53a";
};
}
}
}

#endif // SOLAR_ISIDEBYSIDEDOVERLAY_H
