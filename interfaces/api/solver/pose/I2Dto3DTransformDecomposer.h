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

#ifndef SOLAR_I2Dto3DTransformDecomposer_H
#define SOLAR_I2Dto3DTransformDecomposer_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>

#include "datastructure/CameraDefinitions.h"
#include "datastructure/MathDefinitions.h"

namespace SolAR {
namespace api {
namespace solver {
namespace pose {
/**
 * @class I2Dto3DTransformDecomposer
 * @brief <B>Decomposes 2D transform (ex Fundamental matrix) to 3D transform (ex camera pose).</B>
 * <TT>UUID: 0404e8b9-b824-4852-a34d-6eafa7563918</TT>
 *
 * Knowing a frame, its reference keyframe which already has 3D correpspondences, as well the 2D matches between them, the component find the 2d-3D correspondences between the current frame and the 3D Points visible from the reference keyframe. *
 */
class XPCF_CLIENTUUID("861a828d-bdda-424b-a00b-3a6a7ef48f8e") XPCF_SERVERUUID("eded8db8-d32b-49bc-8b72-db936a63ec9f") I2Dto3DTransformDecomposer :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief I2Dto3DTransformDecomposer default constructor.
    I2Dto3DTransformDecomposer() = default;

    /// @brief I2Dto3DTransformDecomposer default destructor.
    virtual ~I2Dto3DTransformDecomposer() = default;

    /// @brief decompose a transform 2d to a transform 3d (4  possible poses {R1,t1},{R1,t2}, {R2,t1}, {R2,t2}).
    /// @param[in] F the fundamental matrix.
    /// @param[in] camParams the camera parameters.
    /// @param[out] Set (04 possibles cases) of the decomposed camera poses in the world coordinate system expressed as Transform3D.
    /// @return true if succeed, else false
    virtual bool decompose(const SolAR::datastructure::Transform2Df & F,
                           const SolAR::datastructure::CameraParameters & camParams,
                           std::vector<SolAR::datastructure::Transform3Df> & decomposedPoses)= 0;
};
}
}
}
}  // end of namespace Solar


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::I2Dto3DTransformDecomposer,
                             "0404e8b9-b824-4852-a34d-6eafa7563918",
                             "I2Dto3DTransformDecomposer",
                             "SolAR::api::solver::pose::I2Dto3DTransformDecomposer interface");

#endif // SOLAR_IHOMOGRAPHYESTIMATION_H
