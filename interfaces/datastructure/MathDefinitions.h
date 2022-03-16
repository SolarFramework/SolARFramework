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

#ifndef SOLAR_MATHSDEFINITIONS_H
#define SOLAR_MATHSDEFINITIONS_H

#include "xpcf/core/helpers.h"

//#include <boost/serialization/array.hpp>
//#define EIGEN_DENSEBASE_PLUGIN <datastructure/EigenDenseSerializationAddon.h>

//#define EIGEN_DEFAULT_TO_ROW_MAJOR
#include <Eigen/Eigen>

#define SOLAR_PI           3.14159265358979323846
#define SOLAR_RAD2DEG      57.29577951308233
#define SOLAR_DEG2RAD      0.0174532925199433

namespace SolAR {
namespace datastructure {

namespace Maths = Eigen;

/*
template <class T, int Rows, int Cols>
using Matrix = Maths::Matrix<T,Rows,Cols>;

typedef Maths::Matrix<float,3,4> ProjectionMatrix ;
typedef Maths::Matrix<float,3,3> RotationMatrixf;

// Camera Calibration matrix (intrinsic parameters)
//  f_x  0    c_x
//  0    f_y  c_y
//  0    0    1
// Where f_x and f_y are the focal length and c_x and c_y the optical center (based on Opencv implementation).
typedef Maths::Matrix<float,3,3>    CamCalibration;

// Camera Distortion parameters
// (k_1 k_2 p_1 p_2 k_3)
// where x_corrected = x + [2*p_1*x*y + p_2*(r^2 + 2*x^2)]
//       y_corrected = y + [p_1*(r^2+2*y^2)+ 2*p_2*x*y]
//       r^2 = x^2 + y^2
typedef Maths::Matrix<float, 5, 1>  CamDistortion;

//Pose matrix definition               Vector defintion
//
//  R1x1    R1x2    R1x3    Tx         | X |
//  R2x1    R2x2    R2x3    Ty     *   | Y |
//  R3x1    R3x2    R3x3    Tz         | Z |
//  0       0       0       1          | 1 |
//
// This defintion avoids to apply a tranpose...
typedef Maths::Matrix<float,4,4> PoseMatrix ;
*/
template <class T, int Rows, int Cols, int ColOrRowMajor =Eigen::RowMajor>
//using Matrix = Maths::Matrix<T, Rows, Cols, Eigen::RowMajor>;
using Matrix = Maths::Matrix<T,Rows,Cols,ColOrRowMajor>;

template <class T, int Rows>
using Vector = Maths::Matrix<T,Rows,1>;

/**
 * @typedef Vector4f
 * @brief <B>A vector of 4 floats.</B>
 */
typedef Maths::Vector4f Vector4f;

/**
 * @typedef Vector3f
 * @brief <B>A vector of 3 floats.</B>
 */
typedef Maths::Vector3f Vector3f;

/**
 * @typedef Vector3d
 * @brief <B>A vector of 3 doubles.</B>
 */
typedef Maths::Vector3d Vector3d;


template <class T, int Cols>
using RowVector = Maths::Matrix<T,1,Cols>;

template <class T, int Dim, Eigen::TransformTraits TransformType =Maths::Affine, int ColOrRowMajor =Eigen::RowMajor>
using Transform = Maths::Transform<T,Dim,TransformType,ColOrRowMajor>;

using SolARMathIOFormat = Maths::IOFormat;

static SolARMathIOFormat SolARMatrixOctaveFmt(Maths::StreamPrecision, 0, ", ", ";\n", "", "", "[", "]");
static SolARMathIOFormat SolARMatrixHeavyFmt(Maths::FullPrecision, 0, ", ", ";\n", "[", "]", "[", "]");

/**
 * @typedef Transform3Df
 * @brief <B>A transform in 3D space.</B>
 */
typedef Transform<float,3> Transform3Df;

/**
 * @typedef Transform2Df
 * @brief <B>A transform in 2D space.</B>
 */
typedef Transform<float,2> Transform2Df;


template <class T, int Dim>
using Translation = Maths::Translation<T, Dim>;
/**
 * @typedef Translation3Df
 * @brief <B>A translation in 3D space defined with floats.</B>
 */
typedef Translation<float,3> Translation3Df;

/**
 * @typedef Translation2Df
 * @brief <B>A translation in 2D space defined with floats.</B>
 */
typedef Translation<float,2> Translation2Df;


template <class T>
using Quaternion = Maths::Quaternion<T>;

/**
 * @typedef Quaternionf
 * @brief <B>Quaternion defined with floats.</B>
 */
typedef Quaternion<float> Quaternionf;

/**
 * @typedef Rotation
 * @brief <B>A 3x3 matrix defining a 3D rotation.</B>
 */
typedef Maths::Matrix<float, 3, 3, Eigen::RowMajor> Rotation;

/**
 * @typedef Projection
 * @brief <B>A 3x4 matrix defining a projection matrix.</B>
 */
typedef Maths::Matrix<float, 3, 4, Eigen::RowMajor> Projection;

}
}

#include <core/SerializationDefinitions.h>

namespace boost { namespace serialization {

template<   class Archive,
            class S,
            int Rows_,
            int Cols_,
            int Ops_,
            int MaxRows_,
            int MaxCols_>
inline void serialize(Archive & ar,
                      Eigen::Matrix<S, Rows_, Cols_, Ops_, MaxRows_, MaxCols_> & matrix,
                      ATTRIBUTE(maybe_unused) const unsigned int version)
{
  int rows = matrix.rows();
  int cols = matrix.cols();
  ar & make_nvp("rows", rows);
  ar & make_nvp("cols", cols);
  matrix.resize(rows, cols); // no-op if size does not change!

  // always save/load row-major
  for(int r = 0; r < rows; ++r)
    for(int c = 0; c < cols; ++c)
      ar & make_nvp("val", matrix(r,c));
}

template<   class Archive,
            class S,
            int Dim_,
            int Mode_,
            int Options_>
inline void serialize(Archive & ar,
                      Eigen::Transform<S, Dim_, Mode_, Options_> & transform,
                      const unsigned int version)
{
  serialize(ar, transform.matrix(), version);
}
}} // namespace boost::serialization

#endif // SOLAR_MATHSDEFINITIONS_H
