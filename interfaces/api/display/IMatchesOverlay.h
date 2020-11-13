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

#ifndef SOLAR_IMATCHESOVERLAY_H
#define SOLAR_IMATCHESOVERLAY_H

#include "datastructure/MathDefinitions.h"
#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/Keypoint.h"
#include "datastructure/SquaredBinaryPattern.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace display {
/**
 * @class IMatchesOverlay
 * @brief <B>Draws matches between two images.</B>
 * <TT>UUID: a801354a-3e00-467c-b390-48c76fa8c53a</TT>
 *
 * This class provides drawing method to overlay matches between two images.
 */
class IMatchesOverlay : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IMatchesOverlay default constructor
    IMatchesOverlay() = default;

    /// @brief IMatchesOverlay default destructor
    virtual ~IMatchesOverlay() = default;

    /// @brief draw Match Lines.
    /// Draw all the lines joining the keypoints that match between two images
    /// @param[in] image1:  The first image on which have been extracted the first vector keypoints
    /// @param[in] image2: The second image on which have been extracted the second vector of keypoints
    /// @param[out] outImage: The resulting image merging image1 and image2 in side-by-side. If outImage has not been initialized, it will be done by this method. If its size is not the good one, it will be resized by this method.
    /// @param[in] points_image1: The keypoints of image1 that match with keypoints of image2. The Nth keypoint of this vector match with the Nth keypoint of the vector points_image2.
    /// @param[in] points_image2: The keypoints of image2 that match with keypoints of image1. The Nth keypoint of this vector match with the Nth keypoint of the vector points_image1.
    /// @param[in|out] matches, a vector of matches between the first and second image that will be displayed. If this vector is empty, we consider that the ith point of points_image1 matches with the ith point of points_image2.
    virtual void draw(const SRef<Image> image1, const SRef<Image> image2, SRef<Image> & outImage, const std::vector <Point2Df> & points_image1, const std::vector <Point2Df> & points_image2, const std::vector<DescriptorMatch> matches = std::vector<DescriptorMatch>())=0;

    /// @brief draw Match Lines.
    /// Draw all the lines joining the keypoints that match between two images
    /// @param[in] image1:  The first image on which have been extracted the first vector keypoints
    /// @param[in] image2: The second image on which have been extracted the second vector of keypoints
    /// @param[out] outImage: The resulting image merging image1 and image2 in side-by-side. If outImage has not been initialized, it will be done by this method. If its size is not the good one, it will be resized by this method.
    /// @param[in] keypoints_image1: The keypoints of image1 that match with keypoints of image2. The Nth keypoint of this vector match with the Nth keypoint of the vector points_image2.
    /// @param[in] keypoints_image2: The keypoints of image2 that match with keypoints of image1. The Nth keypoint of this vector match with the Nth keypoint of the vector points_image1.
    /// @param[in|out] matches, a vector of matches between the first and second image that will be displayed. If this vector is empty, we consider that the ith point of points_image1 matches with the ith point of points_image2.
    virtual void draw(const SRef<Image> image1, const SRef<Image> image2, SRef<Image> & outImage, const std::vector <Keypoint> & keypoints_image1, const std::vector <Keypoint> & keypoints_image2, const std::vector<DescriptorMatch> matches = std::vector<DescriptorMatch>())=0;

    /// @brief draw Match Lines.
    /// Draw all the lines joining the keypoints that match between two images
    /// @param[in] image: The image to display for drawing in overlay the matches
    /// @param[out] outImage: The resulting image displaying matches in overlay. If outImage has not been initialized, it will be done by this method. If its size is not the good one, it will be resized by this method.
    /// @param[in] points_image1: The keypoints of image1 that match with keypoints of image2. The Nth keypoint of this vector match with the Nth keypoint of the vector points_image2.
    /// @param[in] points_image2: The keypoints of image2 that match with keypoints of image1. The Nth keypoint of this vector match with the Nth keypoint of the vector points_image1.
    /// @param[in|out] matches, a vector of matches between the first and second image that will be displayed. If this vector is empty, we consider that the ith point of points_image1 matches with the ith point of points_image2.
    virtual void draw(const SRef<Image> image, SRef<Image> & outImage, const std::vector <Point2Df> & points_image1, const std::vector <Point2Df> & points_image2, const std::vector<DescriptorMatch> matches = std::vector<DescriptorMatch>())=0;

    /// @brief draw Match Lines.
    /// Draw all the lines joining the keypoints that match between two images
    /// @param[in] image: The image to display for drawing in overlay the matches
    /// @param[out] outImage: The resulting image displaying matches in overlay. If outImage has not been initialized, it will be done by this method. If its size is not the good one, it will be resized by this method.
    /// @param[in] keypoints_image1: The keypoints of image1 that match with keypoints of image2. The Nth keypoint of this vector match with the Nth keypoint of the vector points_image2.
    /// @param[in] keypoints_image2: The keypoints of image2 that match with keypoints of image1. The Nth keypoint of this vector match with the Nth keypoint of the vector points_image1.
    /// @param[in|out] matches, a vector of matches between the first and second image that will be displayed. If this vector is empty, we consider that the ith point of points_image1 matches with the ith point of points_image2.
    virtual void draw(const SRef<Image> image, SRef<Image> & outImage, const std::vector <Keypoint> & keypoints_image1, const std::vector <Keypoint> & keypoints_image2, const std::vector<DescriptorMatch> matches = std::vector<DescriptorMatch>())=0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::display::IMatchesOverlay,
                             "a801354a-3e00-467c-b390-48c76fa8c53a",
                             "ISideBySideOverlay",
                             "SolAR::ISideBySideOverlay interface")

#endif // SOLAR_IMATCHESOVERLAY_H
