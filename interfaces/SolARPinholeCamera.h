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

#include "XPCF_definitions.h"
#include "SolARMathDefinitions.h"


#include <memory>
namespace SolAR {

class XPCF_EXPORT_API SolARPinholeCamera {

    ///
    /// \brief ~SolARPinholeCamera

    public:
    /// \brief constructs a SolARPinholeCamera from a projection matrix of size 3x4 and a pose matrix of size 4x4
    /// \brief proj: projection matrix
    /// \brief pose: pose matrix
    SolARPinholeCamera( const SolARProjectionMatrix & proj, const SolARPoseMatrix & pose);

    /// \brief projects a 3D point to obtain its 2D position on the camera plane
    /// \brief point: the point to project
    SolARVector3f project( SolARVector4f & point);

    private:

    SolARPoseMatrix m_pose;// a 4x4 matrix
    SolARProjectionMatrix m_proj;// a 3x4 matrix
};

}

#endif //SOLARPOSE_H
