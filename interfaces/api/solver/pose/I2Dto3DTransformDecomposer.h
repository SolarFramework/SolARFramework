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

#include "xpcf/api/IComponentIntrospect.h"

#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"

namespace SolAR {
using namespace datastructure;
    namespace api {
        namespace solver {
            namespace pose {
            /**
             * @class I2Dto3DTransformDecomposer
             * @brief Decomposes 2D transform (ex Fundamental matrix) to 3D transform (ex camera pose).
             */
                class  I2Dto3DTransformDecomposer : public virtual org::bcom::xpcf::IComponentIntrospect {
                public:
                    /// @brief I2Dto3DTransformDecomposer default constructor.
                    I2Dto3DTransformDecomposer() = default;

                    /// @brief IFundamentalMatrixDecomposer default destructor.
                    virtual ~I2Dto3DTransformDecomposer() = default;

                    /// @brief this method is used to set intrinsic parameters and distorsion of the camera
                    /// @param[in] Camera calibration matrix parameters.
                    /// @param[in] Camera distorsion parameters.
                    virtual void setCameraParameters(const CamCalibration & intrinsicParams, const CamDistortion & distorsionParams) = 0;

                    /// @brief decompose a transform 2d to a transform 3d (4  possible poses {R1,t1},{R1,t2}, {R2,t1}, {R2,t2}).
                    /// @param[in] Transform 2D (fundamental matrxi, homgraphy..).
                    /// @param[out] Set (04 possibles cases) of the decomposed camera poses in the world coordinate system expressed as Transform3D.
                    virtual bool decompose(const Transform2Df& F, std::vector<Transform3Df>& decomposedPoses)= 0;
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
