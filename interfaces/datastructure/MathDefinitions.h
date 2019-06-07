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

//#define EIGEN_DEFAULT_TO_ROW_MAJOR
#include <Eigen/Eigen>

#define SOLAR_PI           3.14159265358979323846
#define SOLAR_RAD2DEG      57.29577951308233
#define SOLAR_DEG2RAD      0.0174532925199433

namespace SolAR {
namespace datastructure {

namespace Maths = Eigen;

template <class T, int Rows, int Cols, int ColOrRowMajor =Eigen::RowMajor>
//using Matrix = Maths::Matrix<T, Rows, Cols, Eigen::RowMajor>;
using Matrix = Maths::Matrix<T,Rows,Cols,ColOrRowMajor>;

typedef Maths::Matrix<float, 3, 4, Eigen::RowMajor> ProjectionMatrix ;
typedef Maths::Matrix<float, 3, 3, Eigen::RowMajor> RotationMatrixf;

/**
 * @typedef CamCalibration
 * @brief <B>A camera calibration matrix defining the intrinsic parameters of a camera.</B>
 *
 *  Camera intrinsic parameters defined with a 3x3 matrix with the following format:
 *  \f[ \begin{matrix} f_x & 0 & c_x \\ 0 & f_y & c_y \\ 0  & 0  & 1  \end{matrix}\f]
 *  Where \f$c_x\f$ and \f$c_y\f$ define the optical center, \f$f_x\f$ and \f$f_y\f$ the focal.
 */
typedef Maths::Matrix<float, 3, 3, Eigen::RowMajor> CamCalibration;

/**
 * @typedef CamDistortion
 * @brief <B>A camera distortion matrix defining the distortion parameters of a camera.</B>
 *
 *  Camera distortion parameters defined with a vector with 5 floats with the following format:
 *  \f$ \left( K_1, K_2, P_1, P_2, K_3 \right) \f$ <BR>
 *  Look at <a href="https://docs.opencv.org/2.4/doc/tutorials/calib3d/camera_calibration/camera_calibration.html">OpenCV</a>  documentation for more information.
 */
typedef Maths::Matrix<float, 5, 1> CamDistortion;

//Pose matrix definition               Vector defintion
//
//  R1x1    R1x2    R1x3    Tx         | X |
//  R2x1    R2x2    R2x3    Ty     *   | Y |
//  R3x1    R3x2    R3x3    Tz         | Z |
//  0       0       0       1          | 1 |
//
// This defintion avoids to apply a tranpose...
/**
 * @typedef PoseMatrix
 * @brief <B>A pose defining both position and orientation thanks to a 4x4 homogenous matrix.</B>
 *
 *  A pose defined with a 4x4 matrix with the following format:
 *  \f[ \begin{matrix} R_{11} & R_{12} & R_{13} & T_x \\ R_{21} & R_{22} & R_{23} & T_y \\ R_{31} & R_{32} & R_{33} & T_z \\ 0 & 0 & 0  & 1  \end{matrix}\f]
 *  Where \f$R\f$ is the 3x3 rotation matrix and \f$T\f$ is the translation vector.
 */
typedef Maths::Matrix<float, 4, 4> PoseMatrix ;


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

template <class T, int Dim, Eigen::TransformTraits TransformType =Maths::Projective, int ColOrRowMajor =Eigen::RowMajor>
using Transform = Maths::Transform<T,Dim,TransformType,ColOrRowMajor>;

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

}
}

#endif // SOLAR_MATHSDEFINITIONS_H
