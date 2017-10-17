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

#ifndef SOLARPOSE_H
#define SOLARPOSE_H

#include "SolARFrameworkDefinitions.h"

// WIP, uncomment to work on it
#include "SolARMathDefinitions.h"


#include <memory>
namespace SolAR {

class SOLARFRAMEWORK_API SolARPose {

    ///
    /// \brief ~SolARPose

    public:
    SolARPose();
    /// \brief constructs a SolARPose from a rotation matrix of size 3x3 and a translation vector of size 3
    /// \param rotation_matrix3x3, rotation matrix of size 3x3
    /// \param translation vector, translation vector of size 3
    SolARPose( const float rotation_matrix3x3 [], const float translation_vector []);

    /// \brief constructs a SolARPose from a rotation matrix of size 3x3 and a translation vector of size 3
    /// \param SolarRotationMatrixf, rotation matrix of size 3x3
    /// \param translation vector, translation vector of size 3
    SolARPose( const  SolARRotationMatrixf &r, const  SolARVector3f & t);

    /// \brief constructs a SolARPose from a pose matrix
    /// \param spm,
    SolARPose( const  SolARPoseMatrix &spm );


    /// \brief extract a SolARPose having the rotation but no translation
    SolARPose extractRotation();

    /// \brief extract a SolARPose having the translation but no rotation
    SolARPose extractTranslation();
/*
    /// \brief returns the rotation quaternion of the pose
    SolARQuaternionf getRotationQuaternion();

    /// \brief returns the translation vector of the pose
    SolARVectorf getTranslationVector();

    /// \brief returns the interpolation pose between two poses based on quaternion representation
    /// \param pose_a: first pose
    /// \param pose_b: second pose
    /// \param t: must belongs to the range [0;1.0]
    SolARPose makeInterpolated(const SolARPose & pose_a, const SolARPose &  pose_b, const float & t);
*/

    /// \brief copy the pose in a specified array. The user has to be aware of its tab size.
    /// \param dest: array pointer
    /// \param offset: offset array
    void toMatrix(float * dest, int offset =0);

    SolARPoseMatrix getPoseMatrix(void) const;

    /// \brief returns the pose matrix under a string chain
    std::string toString();

    /// \brief returns the transformation of a 3D point p by the internal pose
    SolARVector3f transformPoint(const SolARVector3f & point);

    /// \brief returns the transformation of a 3D point p by the internal pose
    SolARVector4f transformPoint(const SolARVector4f & point);
    /// \brief returns the X component of the pose translation vector
    float tx();
    /// \brief returns the X component of the pose translation vector
    float ty();
    /// \brief returns the X component of the pose translation vector
    float tz();

    private:

    SolARPoseMatrix m_poseMatrix;// a 4x4 matrix

};

}

#endif //SOLARPOSE_H
