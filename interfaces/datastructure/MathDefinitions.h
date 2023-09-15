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

#include <xpcf/core/helpers.h>

//#include <boost/serialization/array.hpp>
//#define EIGEN_DENSEBASE_PLUGIN <datastructure/EigenDenseSerializationAddon.h>

//#define EIGEN_DEFAULT_TO_ROW_MAJOR
#include <Eigen/Eigen>
#include <math.h>

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
 * @typedef Vector3b
 * @brief <B>A vector of 3 unsigned char.</B>
 */
typedef Vector<uint8_t, 3> Vector3b;

/**
 * @typedef Vector3ui
 * @brief <B>A vector of 3 unsigned int</B>
 */
typedef Vector<unsigned int, 3> Vector3ui;

/**
 * @typedef Vector3d
 * @brief <B>A vector of 3 doubles.</B>
 */
typedef Maths::Vector3d Vector3d;

/**
 * @typedef Vector2f
 * @brief <B>A vector of 2 floats.</B>
 */
typedef Maths::Vector2f Vector2f;

/**
 * @typedef Vector2b
 * @brief <B>A vector of 2 unsigned char.</B>
 */
typedef Vector<uint8_t, 2> Vector2b;

/**
 * @typedef Vector2ui
 * @brief <B>A vector of 2 unsigned int</B>
 */
typedef Vector<unsigned int, 2> Vector2ui;

/**
 * @typedef Vector2d
 * @brief <B>A vector of 2 doubles.</B>
 */
typedef Maths::Vector2d Vector2d;


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

/**
 * @typedef Rotation
 * @brief <B>A 3x3 matrix defining a 3D rotation.</B>
 */
typedef Maths::Matrix<float, 3, 3, Eigen::RowMajor> Rotation;

/**
 * @typedef Rotation
 * @brief <B>A 3x3 matrix defining a 3D rotation.</B>
 */
typedef Maths::Matrix<double, 3, 3, Eigen::RowMajor> Rotationd;

/**
 * @typedef Projection
 * @brief <B>A 3x4 matrix defining a projection matrix.</B>
 */
typedef Maths::Matrix<float, 3, 4, Eigen::RowMajor> Projection;

/**
 * @brief <B> Compute average quaternion from a list of input quaternions.</B>
 *  The algorithm used is described here:
 *  https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/20070017872.pdf
 * @param[in] quaternions vector of Vector4f quaternions
 * @return average quaternion Vector4f
 */
static Vector4f quaternionAverage(const std::vector<Vector4f>& quaternions) {
    if (quaternions.size() == 0)
        return Vector4f::Zero();
    else if (quaternions.size() == 1)
        return quaternions.front();

    // first build a 4x4 matrix which is the elementwise sum of the product of each quaternion with itself
    Maths::Matrix4f A = Maths::Matrix4f::Zero();
    for (const auto& q : quaternions)
        A += q * q.transpose();
    // normalise with the number of quaternions
    A /= static_cast<float>(quaternions.size());
    // Compute the SVD of this 4x4 matrix
    Maths::JacobiSVD<Maths::MatrixXf> svd(A, Maths::ComputeThinU | Maths::ComputeThinV);
    Maths::VectorXf singularValues = svd.singularValues();
    Maths::MatrixXf matU = svd.matrixU();
    // find the eigen vector corresponding to the largest eigen value
    int index = 0;
    float value = singularValues(0);
    for (int i=1; i < static_cast<int>(singularValues.rows()); ++i) {
       if (singularValues(i) > value) {
            value = singularValues(i);
            index = i;
        }
    }
    return Vector4f(matU(0, index), matU(1, index), matU(2, index), matU(3, index));
}

/**
 * @brief <B> Compute average quaternion from a list of input quaternions.</B>
 * @param[in] quaternions vector of Quaternionf
 * @return average quaternion Quaternionf
 */
static Quaternionf quaternionAverage(const std::vector<Quaternionf>& quaternions) {
    std::vector<Vector4f> quaternionsVecs;
    for (const auto& q : quaternions)
        quaternionsVecs.emplace_back(q.x(), q.y(), q.z(), q.w());
    return Quaternionf(quaternionAverage(quaternionsVecs));
}

/**
 * @brief <B> Compute average transform3D from a list of input transform3Ds.</B>
 * @param[in] transforms list of transform3D
 * @return average transform3D
 */
 [[maybe_unused]] static Transform3Df transform3DAverage(const std::vector<Transform3Df>& transforms) {
    if (transforms.size() == 0)
        return Transform3Df(Maths::Matrix4f::Zero());
    else if (transforms.size() == 1)
        return transforms.front();
    Vector3f translations(0.f, 0.f, 0.f);
    std::vector<Quaternionf> quaternions;
    for (const auto& t : transforms) {
        translations += t.translation();
        quaternions.emplace_back(t.rotation());
    }
    translations /= static_cast<float>(transforms.size());
    Transform3Df transform3D;
    transform3D.linear() = quaternionAverage(quaternions).toRotationMatrix();
    transform3D.translation() = translations;
    return transform3D;
}

/**
 * @brief <B> Convert a 3x3 rotation matrix to a 3x1 Rodrigues vector (axis-angle representation).</B>
 * @param[in] rotMat 3x3 rotation matrix 
 * @return Rodrigues rotation vector 
 */
static Vector3f rotationMatrixToVector(const Rotation& rotMat) {
    float th = acos(0.5*(fmax(rotMat(0, 0) + rotMat(1, 1) + rotMat(2, 2), -1.f) - 1.f));
    float sth = sin(th);
    float cth = cos(th);
    if (fabs(sth) < 1e-6f && cth < 0.f) {
        float w[9], x, y, z;
        w[0] = 0.5f*(rotMat(0, 0) + rotMat(0, 0)) - 1.f;
        w[1] = 0.5f*(rotMat(1, 0) + rotMat(0, 1));
        w[2] = 0.5f*(rotMat(2, 0) + rotMat(0, 2));

        w[3] = 0.5f*(rotMat(0, 1) + rotMat(1, 0));
        w[4] = 0.5f*(rotMat(1, 1) + rotMat(1, 1)) - 1.f;
        w[5] = 0.5f*(rotMat(2, 1) + rotMat(1, 2));

        w[6] = 0.5f*(rotMat(0, 2) + rotMat(2, 0));
        w[7] = 0.5f*(rotMat(1, 2) + rotMat(2, 1));
        w[8] = 0.5f*(rotMat(2, 2) + rotMat(2, 2)) - 1.f;

        x = sqrt(0.5f * (w[0] - w[4] - w[8]));
        y = sqrt(0.5f * (w[4] - w[8] - w[0]));
        z = sqrt(0.5f * (w[8] - w[0] - w[4]));

        if (x >= y && x >= z) {
            y = (w[1] >= 0.f) ? y : -y;
            z = (w[2] >= 0.f) ? z : -z;
        }
        else if (y >= x && y >= z) {
            z = (w[5] >= 0.f) ? z : -z;
            x = (w[1] >= 0.f) ? x : -x;
        }
        else {
            x = (w[2] >= 0.f) ? x : -x;
            y = (w[5] >= 0.f) ? y : -y;
        }

        float scale = th / sqrt(1.f - cth);
        return Vector3f(scale * x, scale * y, scale * z);
    }
    else {
        float a = (fabs(sth) < 1e-6f) ? 1.f : th / sin(th);
        return Vector3f(0.5f*a*(rotMat(2, 1) - rotMat(1, 2)), 0.5f*a*(rotMat(0, 2) - rotMat(2, 0)), 0.5f*a*(rotMat(1, 0) - rotMat(0, 1)));
    }
}

/**
 * @brief <B> Convert a 3x1 Rodrigues vector (axis-angle representation) to a 3x3 rotation matrix.</B>
 * @param[in] rotVec 3x1 Rodrigues rotation vector  
 * @return 3x3 rotation matrix 
 */
static Rotation rotationVectorToMatrix(const Vector3f& rotVec) {
    float th = sqrt(rotVec(0)*rotVec(0) + rotVec(1)*rotVec(1) + rotVec(2)*rotVec(2));
    if (th < 1e-6f)
        return Rotation::Identity();

    float x = rotVec(0) / th;
    float y = rotVec(1) / th;
    float z = rotVec(2) / th;

    float xx = x * x;
    float xy = x * y;
    float xz = x * z;
    float yy = y * y;
    float yz = y * z;
    float zz = z * z;

    const float yx = xy;

    float sth = sin(th);
    float cth = cos(th);
    float mcth = 1.f - cth;

    Rotation matR;
    matR(0, 0) = 1.f - mcth * (yy + zz);
    matR(1, 0) = sth * z + mcth * xy;
    matR(2, 0) = -sth * y + mcth * xz;

    matR(0, 1) = -sth * z + mcth * yx;
    matR(1, 1) = 1.f - mcth * (zz + xx);
    matR(2, 1) = sth * x + mcth * yz;

    matR(0, 2) = sth * y + mcth * xz;
    matR(1, 2) = -sth * x + mcth * yz;
    matR(2, 2) = 1.f - mcth * (xx + yy);
    return matR;
}

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
                      const unsigned int /* version */)
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
