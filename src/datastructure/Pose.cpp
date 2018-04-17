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

#include "datastructure/Pose.h"
//#include <cstddef> //TO DO: remove with a complete implementation

namespace SolAR {
namespace datastructure {

Pose::Pose()
{
    m_poseTransform.Identity();
}

Pose::Pose( const Transform3Df& s3dt )
	: m_poseTransform(s3dt)
{
}

Pose Pose::extractRotation()
{
    Transform3Df tmp;
    // not the most efficient way to set the memory..
    tmp.matrix() << m_poseTransform(0,0), m_poseTransform(0,1), m_poseTransform(0,2), 0.0f,
                    m_poseTransform(1,0), m_poseTransform(1,1), m_poseTransform(1,2), 0.0f,
                    m_poseTransform(2,0), m_poseTransform(2,1), m_poseTransform(2,2),0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f  ;
    return Pose(tmp);
}


Pose Pose::extractTranslation()
{
    Transform3Df tmp;
    // not the most efficient way to set the memory..
    tmp.matrix() << 1.0f, 0.0f, 0.0f, m_poseTransform(0,3),
                    0.0f, 1.0f, 0.0f, m_poseTransform(1,3),
                    0.0f, 0.0f, 1.0f, m_poseTransform(2,3),
                    0.0f, 0.0f, 0.0f, 1.0f;
    return Pose(tmp);
}

void Pose::setPoseTransform(const Transform3Df& s3dt)
{
    m_poseTransform=s3dt;
}

const Transform3Df& Pose::getPoseTransform() const
{
    return m_poseTransform;
}

void Pose::toMatrix(float * dest, int offset)
{
    dest[ 0 + offset] = m_poseTransform(0,0) ;
    dest[ 1 + offset] = m_poseTransform(0,1) ;
    dest[ 2 + offset] = m_poseTransform(0,2) ;
    dest[ 3 + offset] = m_poseTransform(0,3) ;

    dest[ 4 + offset] = m_poseTransform(1,0) ;
    dest[ 5 + offset] = m_poseTransform(1,1) ;
    dest[ 6 + offset] = m_poseTransform(1,2) ;
    dest[ 7 + offset] = m_poseTransform(1,3) ;

    dest[ 8 + offset] = m_poseTransform(2,0) ;
    dest[ 9 + offset] = m_poseTransform(2,1) ;
    dest[10 + offset] = m_poseTransform(2,2) ;
    dest[11 + offset] = m_poseTransform(2,3) ;

    dest[12 + offset] = m_poseTransform(3,0) ;
    dest[13 + offset] = m_poseTransform(3,1) ;
    dest[14 + offset] = m_poseTransform(3,2) ;
    dest[15 + offset] = m_poseTransform(3,3) ;
}

std::string Pose::toString ()
{
    std::stringstream strstream;
    strstream << "[ " << m_poseTransform(0,0) << ",\t" << m_poseTransform(0,1) << ",\t" << m_poseTransform(0,2) << ",\t" << m_poseTransform(0,3) << "]\n" <<
                 "[ " << m_poseTransform(1,0) << ",\t" << m_poseTransform(1,1) << ",\t" << m_poseTransform(1,2) << ",\t" << m_poseTransform(1,3) << "]\n" <<
                 "[ " << m_poseTransform(2,0) << ",\t" << m_poseTransform(2,1) << ",\t" << m_poseTransform(2,2) << ",\t" << m_poseTransform(2,3) << "]\n" <<
                 "[ " << m_poseTransform(3,0) << ",\t" << m_poseTransform(3,1) << ",\t" << m_poseTransform(3,2) << ",\t" << m_poseTransform(3,3) << "]";
    return strstream.str();
}


Pose Pose::Inverse() const
{
    return Pose(m_poseTransform.inverse());
}

float Pose::tx()
{
    return m_poseTransform(0,3);
}

float Pose::ty()
{
    return m_poseTransform(1,3);
}

float Pose::tz()
{
    return m_poseTransform(2,3);
}
}
}//end namespace SolAR
