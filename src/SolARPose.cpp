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

#include "SolARPose.h"
#include <cstddef> //TO DO: remove with a complete implementation

namespace SolAR {

SolARPose::SolARPose(){

}

SolARPose::SolARPose( const float rotation_matrix3x3 [], const float translation_vector []){

    //rotation matrix
    m_poseMatrix(0,0) = rotation_matrix3x3[0];  m_poseMatrix(0,1) = rotation_matrix3x3[1];   m_poseMatrix(0,2) = rotation_matrix3x3[2];
    m_poseMatrix(1,0) = rotation_matrix3x3[3];  m_poseMatrix(1,1) = rotation_matrix3x3[4];   m_poseMatrix(1,2) = rotation_matrix3x3[5];
    m_poseMatrix(2,0) = rotation_matrix3x3[6];  m_poseMatrix(2,1) = rotation_matrix3x3[7];   m_poseMatrix(2,2) = rotation_matrix3x3[8];

    //translation vector
    m_poseMatrix(0,3) =   translation_vector[0];
    m_poseMatrix(1,3) =   translation_vector[1];
    m_poseMatrix(2,3) =   translation_vector[2];

    m_poseMatrix(3,0) = 0; m_poseMatrix(3,1) = 0; m_poseMatrix(3,2) = 0; m_poseMatrix(3,3) = 1;
}



SolARPose::SolARPose( const  SolARRotationMatrixf &r, const  SolARVector3f & t){

    //copy by block
   //  m_poseMatrix.block<3,3>(0,0) = r;
   //  m_poseMatrix.block<1,3>(0,3) = t;

    m_poseMatrix(0,0) =  r(0,0);  m_poseMatrix(0,1) = r(0,1);   m_poseMatrix(0,2) = r(0,2);
         m_poseMatrix(1,0) =  r(1,0);  m_poseMatrix(1,1) = r(1,1);   m_poseMatrix(1,2) = r(1,2);
         m_poseMatrix(2,0) =  r(2,0);  m_poseMatrix(2,1) = r(2,1);   m_poseMatrix(2,2) = r(2,2);

         m_poseMatrix(0,3) =   t[0];
         m_poseMatrix(1,3) =   t[1];
         m_poseMatrix(2,3) =   t[2];

     m_poseMatrix(3,0) = 0; m_poseMatrix(3,1) = 0; m_poseMatrix(3,2) = 0; m_poseMatrix(3,3) = 1;

}

SolARPose::SolARPose( const  SolARPoseMatrix &spm ){
    m_poseMatrix=spm;
}



SolARPose SolARPose::extractRotation(){

    SolARPoseMatrix tmp;
    // not the most efficient way to set the memory..
    tmp << m_poseMatrix(0,0), m_poseMatrix(0,1), m_poseMatrix(0,2), 0.0f,
            m_poseMatrix(1,0), m_poseMatrix(1,1), m_poseMatrix(1,2), 0.0f,
            m_poseMatrix(2,0), m_poseMatrix(2,1), m_poseMatrix(2,2),0.0f,
            0.0f, 0.0f, 0.0f, 1.0f  ;

 return   SolARPose(tmp);
}


SolARPose SolARPose::extractTranslation(){

    SolARPoseMatrix tmp;
    // not the most efficient way to set the memory..
    tmp << 0.0f, 0.0f, 0.0f, m_poseMatrix(0,3),
           0.0f, 0.0f, 0.0f, m_poseMatrix(1,3),
           0.0f, 0.0f, 0.0f, m_poseMatrix(2,3),
           0.0f, 0.0f, 0.0f, 1.0f  ;


 return   SolARPose(tmp);
}

/*
SolARQuaternion SolARPose::getRotationQuaternion(){

}

SolARVector3f SolARPose::getTranslationVector(){
    return SolARVector3f(m_poseMatrix(0,3),m_poseMatrix(1,3),m_poseMatrix(2,3));
}

SolARPose SolARPose::makeInterpolated(const SolARPose & pose_a, const SolARPose &  pose_b, const float & t){
 return SolARPose(0,0);
}
*/
SolARPoseMatrix SolARPose::getPoseMatrix() const{
    return m_poseMatrix;
}

void SolARPose::toMatrix(float * dest, int offset){

    dest[ 0 + offset] = m_poseMatrix(0,0) ;
    dest[ 1 + offset] = m_poseMatrix(0,1) ;
    dest[ 2 + offset] = m_poseMatrix(0,2) ;
    dest[ 3 + offset] = m_poseMatrix(0,3) ;

    dest[ 4 + offset] = m_poseMatrix(1,0) ;
    dest[ 5 + offset] = m_poseMatrix(1,1) ;
    dest[ 6 + offset] = m_poseMatrix(1,2) ;
    dest[ 7 + offset] = m_poseMatrix(1,3) ;

    dest[ 8 + offset] = m_poseMatrix(2,0) ;
    dest[ 9 + offset] = m_poseMatrix(2,1) ;
    dest[10 + offset] = m_poseMatrix(2,2) ;
    dest[11 + offset] = m_poseMatrix(2,3) ;

    dest[12 + offset] = m_poseMatrix(3,0) ;
    dest[13 + offset] = m_poseMatrix(3,1) ;
    dest[14 + offset] = m_poseMatrix(3,2) ;
    dest[15 + offset] = m_poseMatrix(3,3) ;

}

std::string SolARPose::toString(){
    return std::string("TODO");

}


SolARVector3f SolARPose::transformPoint(const SolARVector3f & point){
    return (m_poseMatrix*SolARVector4f(point(0),point(1),point(2),1)).block<1,3>(0,0);
}

SolARVector4f SolARPose::transformPoint(const SolARVector4f & point){
    return m_poseMatrix*point;
}

float SolARPose::tx(){
    return m_poseMatrix(0,3);
}

float SolARPose::ty(){
    return m_poseMatrix(1,3);
}

float SolARPose::tz(){
    return m_poseMatrix(2,3);
}

}//end namespace SolAR
