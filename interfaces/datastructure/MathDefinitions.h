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
using Matrix = Maths::Matrix<T, Rows, Cols, Eigen::RowMajor>;

typedef Maths::Matrix<float, 3, 4, Eigen::RowMajor> ProjectionMatrix ;
typedef Maths::Matrix<float, 3, 3, Eigen::RowMajor> RotationMatrixf;

// Camera intrinsic parameters defined with a 3x3 matrix
// f_x  0  c_x
//  0  f_y c_y
//  0   0   1
// Where c_x and c_y define the optical center, f_x and f_y the focal.
typedef Maths::Matrix<float, 3, 3, Eigen::RowMajor> CamCalibration;


// Camera distortion parameter (K1, K2, P1, P2, K3)
// see openCV Camera Calibration reference for more details.
typedef Maths::Matrix<float, 5, 1> CamDistortion;

//Pose matrix definition               Vector defintion
//
//  R1x1    R1x2    R1x3    Tx         | X |
//  R2x1    R2x2    R2x3    Ty     *   | Y |
//  R3x1    R3x2    R3x3    Tz         | Z |
//  0       0       0       1          | 1 |
//
// This defintion avoids to apply a tranpose...

typedef Maths::Matrix<float, 4, 4> PoseMatrix ;


template <class T, int Rows>
using Vector = Maths::Matrix<T,Rows,1>;

typedef Vector<float,4> Vector4f ;
//typedef Vector<float,3> Vector3f ;
//typedef Vector<double,3>Vector3d ;

typedef Maths::Vector4f Vector4f ;
typedef Maths::Vector3f Vector3f;
typedef Maths::Vector3d Vector3d;


template <class T, int Cols>
using RowVector = Maths::Matrix<T,1,Cols>;

template <class T, int Dim, Eigen::TransformTraits TransformType =Maths::Projective, int ColOrRowMajor =Eigen::RowMajor>
using Transform = Maths::Transform<T,Dim,Maths::Projective,Eigen::RowMajor>;
typedef Transform<float,3> Transform3Df;
typedef Transform<float,2> Transform2Df;


template <class T, int Dim>
using Translation = Maths::Translation<T, Dim>;
typedef Translation<float,3> Translation3Df;
typedef Translation<float,2> Translation2Df;


template <class T>
using Quaternion = Maths::Quaternion<T>;
typedef Quaternion<float> Quaternionf;

}
}

#endif // SOLAR_MATHSDEFINITIONS_H
