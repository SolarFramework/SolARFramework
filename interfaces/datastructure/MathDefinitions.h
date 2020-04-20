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
