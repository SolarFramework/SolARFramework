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

/** @file */

#ifndef SOLAR_GEOMETRYDEFINITIONS_H
#define SOLAR_GEOMETRYDEFINITIONS_H

#include "xpcf/xpcf.h"
#include "datastructure/MathDefinitions.h"
#include "core/SolARFrameworkDefinitions.h"

namespace SolAR {
namespace datastructure {

/**
 * @class Point2Df
 * @brief <B>A 2D point with coordinates defined with floats.</B>
 *
 */
using Point2Df = Vector<float, 2>;

/**
 * @class Point3Df
 * @brief <B>A 3D point with coordinates defined with floats.</B>
 *
 */
using Point3Df = Vector<float, 3>;

/**
 * @class Point2Di
 * @brief <B>A 2D point with coordinates defined with integers.</B>
 *
 */
using Point2Di = Vector<int, 2>;

/**
 * @class Point3Di
 * @brief <B>A 3D point with coordinates defined with integers.</B>
 *
 */
using Point3Di = Vector<int, 3>;

/**
 * @class Edge2Df
 * @brief <B>A 2D edge with coordinates defined with floats.</B>
 *
 */
class Edge2Df {
public:
    Edge2Df() = default;
    Edge2Df(const Point2Df& point1, const Point2Df& point2) : p1(point1), p2(point2){}
    ~Edge2Df() = default;

    Point2Df p1;
    Point2Df p2;
};

/**
 * @class Edge2Di
 * @brief <B>A 2D edge with coordinates defined with integers.</B>
 *
 */
class Edge2Di {
public:
    Edge2Di() = default;
    Edge2Di(const Point2Di& point1, const Point2Di& point2) : p1(point1), p2(point2){}
    ~Edge2Di() = default;

    Point2Di p1;
    Point2Di p2;
};

/**
 * @typedef Contour2Df
 * @brief <B>A contours defined with 2D points with coordinates defined with floats.</B>
 *
 */
// TODO : maintain SRef here ???
using Contour2Df = std::vector<Point2Df>;

/**
 * @typedef Contour2Di
 * @brief <B>A contours defined with 2D points with coordinates defined with integers.</B>
 *
 */
// TODO : maintain SRef here ???
using Contour2Di = std::vector<Point2Di>;

/**
 * @typedef QuadContour2Df
 * @brief <B>A contours defined with 4 2D points with coordinates defined with floats.</B>
 *
 */
using QuadContour2Df = Point2Df[4];

/**
 * @typedef QuadContour2Di
 * @brief <B>A contours defined with 4 2D points with coordinates defined with integers.</B>
 *
 */
using QuadContour2Di = Point2Di[4];

/**
 * @struct Sizei
 * @brief <B>A 2D size defined with integers.</B>
 */
struct Sizei {
    uint32_t width;
    uint32_t height;
};

/**
 * @struct Sizef
 * @brief <B>A 2D size defined with floats.</B>
 */
struct Sizef {
    float width;
    float height;
};

/**
 * @struct Rectanglei
 * @brief <B>A 2D rectangle which size in defined with integers.</B>
 */
struct Rectanglei {
    uint32_t startX;
    uint32_t startY;
    Sizei size;
};

using ProjectionMatrix = Maths::Matrix<float, 3, 4, Eigen::RowMajor>;
using RotationMatrixf = Maths::Matrix<float, 3, 3, Eigen::RowMajor>;

}
}

#endif // SOLAR_GEOMETRYDEFINITIONS_H
