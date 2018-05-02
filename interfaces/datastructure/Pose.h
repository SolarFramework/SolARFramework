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
class SOLARFRAMEWORK_API Pose
{
public:
    Pose();
    
    /// \brief constructs a Pose from a pose matrix
    /// \param spm,
    Pose( const Transform3Df& s3dt );

    /// \brief extract a Pose having the rotation but no translation
    Pose extractRotation();

    /// \brief extract a Pose having the translation but no rotation
    Pose extractTranslation();

    void setPoseTransform(const Transform3Df& s3dt);


    /// \brief copy the pose in a specified array. The user has to be aware of its tab size.
    /// \param dest: array pointer
    /// \param offset: offset array
    void toMatrix(float* dest, int offset=0);

    const Transform3Df& getPoseTransform(void) const;

    /// \brief returns the pose matrix under a string chain
    std::string toString();

    /// \brief Return the invert pose
    Pose Inverse() const;

    /// \brief returns the X component of the pose translation vector
    float tx();
    /// \brief returns the X component of the pose translation vector
    float ty();
    /// \brief returns the X component of the pose translation vector
    float tz();

private:
    Transform3Df m_poseTransform;// a 4x4 matrix

};
}
}
#endif //SOLAR_POSE_H
