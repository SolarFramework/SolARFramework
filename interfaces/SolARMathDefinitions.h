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

#ifndef SOLARMATHSDEFINITIONS_H
#define SOLARMATHSDEFINITIONS_H

#define EIGEN_DEFAULT_TO_ROW_MAJOR
#include <Eigen>

namespace SolAR {
namespace Maths = Eigen;

template <class T, int Rows, int Cols>
using SolARMatrix = Maths::Matrix<T,Rows,Cols>;

//Pose matrix definition               Vector defintion
//
//  R1x1    R1x2    R1x3    Tx         | X |
//  R2x1    R2x2    R2x3    Ty     *   | Y |
//  R3x1    R3x2    R3x3    Tz         | Z |
//  0       0       0       1          | 1 |
//
// This defintion avoids to apply a tranpose...

typedef Maths::Matrix<float,4,4> SolARPoseMatrixf ;
typedef Maths::Matrix<float,4,1> SolARVector4f ;
typedef Maths::Matrix<double,4,1> SolARVector4d ;

typedef Maths::Matrix<float,4,4> SolARPoseMatrix ;
typedef Maths::Matrix<double,3,3> SolARMatrix33d ;
typedef Maths::Matrix<float,3,3> SolARMatrix33f ;

typedef Maths::Matrix<float,3,3> SolARRotationMatrixf;
typedef Maths::Matrix<float,3,1> SolARVector3f ;
typedef Maths::Matrix<double,3,1>SolARVector3d ;
typedef Maths::Matrix<float,3,1> SolARPoint_3Df;
typedef Maths::Matrix<float,2,1> SolARPoint_2Df;
typedef Maths::Matrix<float,3,1> SolARTranslationVectorf;
typedef Maths::Quaternion<float> SolARQuaternionf;

typedef Maths::Matrix<float,3,4> SolARProjectionMatrix ;


template <class T>
using SolARTranslationVector = Maths::Matrix<T,1,3>;

template <class T, int Cols>
using SolARVector = Maths::Matrix<T,1,Cols>;

template <class T>
using SolARPoint_2D = Maths::Matrix<T,1,2>;


template <class T>
using SolARPoint_3D = Maths::Matrix<T,1,3>;

template <class T>
using SolARQuaternion = Maths::Quaternion<T>;

}

#endif
