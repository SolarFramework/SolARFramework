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

#ifndef SOLAR_POSE_H
#define SOLAR_POSE_H

#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"

#include <memory>
namespace SolAR {
namespace datastructure {

/**
 * @class Pose
 * @brief Specifies the Pose base class.
 *
 * This class provides utilities to manipulate pose components and convertion to Euler angles or quaternion.
 */
class SOLARFRAMEWORK_API Pose {

    ///
    /// \brief ~Pose

    public:
    Pose();
    /// \brief constructs a Pose from a rotation matrix of size 3x3 and a translation vector of size 3
    /// \param rotation_matrix3x3, rotation matrix of size 3x3
    /// \param translation vector, translation vector of size 3
    Pose( const float rotation_matrix3x3 [], const float translation_vector []);

    /// \brief constructs a Pose from a rotation matrix of size 3x3 and a translation vector of size 3
    /// \param r, rotation matrix of size 3x3
    /// \param t, translation vector of size 3
    Pose( const  RotationMatrixf &r, const  Vector3f & t);

    /// \brief constructs a Pose from a pose matrix
    /// \param spm,
    Pose( const  Transform3Df &s3dt );


    /// \brief extract a Pose having the rotation but no translation
    Pose extractRotation();

    /// \brief extract a Pose having the translation but no rotation
    Pose extractTranslation();

    void setPoseTransform(const Transform3Df &s3dt);


    /// \brief copy the pose in a specified array. The user has to be aware of its tab size.
    /// \param dest: array pointer
    /// \param offset: offset array
    void toMatrix(float * dest, int offset =0);

    Transform3Df getPoseTransform(void) const;

    /// \brief returns the pose matrix under a string chain
    std::string toString();

    /// \brief returns the transformation of a 3D point p by the internal pose
    Point3Df transformPoint(const Point3Df & point);

    /// \brief Return the invert pose
    Pose Inverse() const;

    /// \brief returns the transformation of a 3D point p by the internal pose
    Vector4f transformPoint(const Vector4f & point);
    /// \brief returns the X component of the pose translation vector
    float tx();
    /// \brief returns the X component of the pose translation vector
    float ty();
    /// \brief returns the X component of the pose translation vector
    float tz();

    Transform3Df m_poseTransform;// a 4x4 matrix
    double m_data[4][4];
    private:


};

}
}

#endif //SOLAR_POSE_H
