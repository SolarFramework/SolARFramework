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

#ifndef SOLAR_STEREOCAMERADEFINITIONS_H
#define SOLAR_STEREOCAMERADEFINITIONS_H

#include <datastructure/GeometryDefinitions.h>

namespace SolAR {
namespace datastructure {

/**
* @typedef StereoType
* @brief <B>The StereoType enum.</B>
*/
typedef enum {
	Horizontal = 0,
	Vertical = 1
} StereoType;

/**
 * @typedef RectificationParameters
 * @brief <B>Define rectification parameters of a camera.</B>
 * Rectification parameters consists of two elements: rotation matrix and projection matrix.
 * The first one brings points given in the unrectified camera's coordinate system to points in the rectified camera's coordinate system.
 * The second one projects points given in the rectified first camera coordinate system into the rectified first camera's image.
 */
struct RectificationParameters
{
    // This matrix brings points given in the unrectified camera coordinate system to points in the rectified camera coordinate system
    Maths::Matrix3f rotation;
    // Projects points given in the rectified camera coordinate system into the rectified image coordinate system.
    Maths::Matrix<float, 3, 4> projection;
    // Stereo type
    SolAR::datastructure::StereoType type;
    // Stereo baseline in meters
    float baseline;
    // Stereo baseline multiplied by focal
    float fb;
};

}
}


#endif // SOLAR_STEREOCAMERADEFINITIONS_H
