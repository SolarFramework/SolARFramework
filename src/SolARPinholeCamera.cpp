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

#include "SolARPinholeCamera.h"
namespace SolAR {


SolARPinholeCamera::SolARPinholeCamera( const SolARProjectionMatrix & proj, const SolARPoseMatrix & pose):m_proj(proj), m_pose(pose){

}

SolARVector3f SolARPinholeCamera::project( SolARVector4f & point){
      return m_proj*m_pose*point;
}

}
