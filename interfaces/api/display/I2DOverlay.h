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

#ifndef SOLAR_I2DOVERLAY_H
#define SOLAR_I2DOVERLAY_H

#include "datastructure/MathDefinitions.h"
#include "xpcf/api/IComponentIntrospect.h"
#include "datastructure/Image.h"
#include "datastructure/Keypoint.h"
#include "datastructure/Keyline.h"
#include "datastructure/SquaredBinaryPattern.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
namespace api {
namespace display {

/**
 * @class I2DOverlay
 * @brief <B>Draws 2D information on top of an image.</B>
 * <TT>UUID: 62b8b0b5-9344-40e6-a288-e609eb3ff0f1</TT>
 *
 * This class provides drawing methods to overlay 2D debug informations on top of an image.
 */

class I2DOverlay : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief I2DOverlay default constructor
    I2DOverlay() = default;

    /// @brief I2DOverlay default destructor
    virtual ~I2DOverlay() = default;

     /// @brief Draw one Circle.
    /// Draw a circle on the image displayImage center on the point with specified radius and thickness.
    /// @param[in] point The position of the circle to draw
    /// @param[in,out] displayImage The image on which the the circles will be drawn.
    virtual void drawCircle(const datastructure::Point2Df & point, SRef<datastructure::Image> displayImage) = 0;

    /// @brief Draw Circles.
    /// Draw all the circles stored in the vector std::vector <Point2Df> & points on image displayImage with specified radius, thickness and colors (defined in the configuration file).
    /// @param[in] point The positions of the circles to draw
    /// @param[in,out] displayImage The image on which the circles will be drawn.
    virtual void drawCircles(const std::vector<datastructure::Point2Df> & points, SRef<datastructure::Image> displayImage) = 0;

    /// @brief Draw Circles.
    /// Draw all the circles stored in the vector std::vector <Keypoint> & keypoints on image displayImage with specified radius, thickness and colors (defined in the configuration file).
    /// @param[in] keypoint The positions of the circles to draw
    /// @param[in,out] displayImage The image on which the circles will be drawn.
    virtual void drawCircles(const std::vector<datastructure::Keypoint> & keypoints, SRef<datastructure::Image> displayImage) = 0;

	/// @brief Draw Lines.
	/// Draw all the lines stored in the vector std::vector <Keyline> & keylines on image displayImage with specified thickness and colors (defined in the configuration file).
	/// @param[in] keylines The line descriptors to draw
	/// @param[in,out] displayImage The image on which the lines will be drawn.
	virtual void drawLines(const std::vector<Keyline> & keylines, SRef<Image> displayImage) = 0;

	/// @brief Draw Lines.
	/// Draw all the lines stored in the vector std::vector <Edge2Df> & 2D lines on image displayImage with specified thickness and colors (defined in the configuration file).
	/// @param[in] ln2d The 2D lines to draw
	/// @param[in,out] displayImage The image on which the lines will be drawn.
	virtual void drawLines(const std::vector<Edge2Df> & ln2d, SRef<Image> displayImage) = 0;

    /// @brief Draw a Contour.
    /// Draw a contour on image displayImage
    /// @param[in] contour The contour in 2D to draw with specified radius, thickness and colors (defined in the configuration file).
    /// @param[in,out] displayImage The image on which the contours will be drawn.
    virtual void drawContour (const datastructure::Contour2Df& contours, SRef<datastructure::Image> displayImage) = 0;

    /// @brief Draw Contours.
    /// Draw all the contours stored in the vector  std::vector <Contour2Df> & contours on image displayImage
    /// @param[in] contours The vector of contours in 2D to draw with specified radius, thickness and colors (defined in the configuration file).
    /// @param[in,out] displayImage The image on which the contours will be drawn.
    virtual void drawContours (const std::vector <datastructure::Contour2Df> & contours, SRef<datastructure::Image> displayImage) = 0;

    /// @brief Draw a Squared Binary Pattern.
    /// @param[in] pattern The squared binary pattern to display.
    /// @param[in,out] displayImage The image on which the squared binary pattern will be drawn (on the whole image).
    virtual void drawSBPattern (const datastructure::SquaredBinaryPattern & pattern, SRef<datastructure::Image> displayImage) = 0;
	
	/// @brief Writes text on the image.
	/// @param[in] text, bottom-left point as origin, fontSize and color
	/// @param[in,out]  displayImage The image on which the text will be written.
	virtual void putText(const std::string & text, datastructure::Point2Df origin, double fontSize, const std::vector<int> & color, SRef<datastructure::Image> displayImage) = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::display::I2DOverlay,
                             "62b8b0b5-9344-40e6-a288-e609eb3ff0f1",
                             "I2DOverlay",
                             "SolAR::I2DOverlay interface")

#endif // SOLAR_I2DOVERLAY_H
