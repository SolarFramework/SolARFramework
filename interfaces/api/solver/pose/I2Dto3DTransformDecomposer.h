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

#ifndef SOLAR_I2DTO3DTRANSFORMDECOMPOSER_H
#define SOLAR_I2DTO3DTRANSFORMDECOMPOSER_H

#include "IComponentIntrospect.h"

#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Pose.h"


namespace SolAR {
using namespace datastructure;
    namespace api {
        namespace solver {
            namespace pose {
            /**
             * @class I2DTO3DTransformDecomposer
             * @brief Decomposes 2D transform (ex Fundamental matrix) to 3D transform (ex camera pose).
             */
                class  I2DTO3DTransformDecomposer : public virtual org::bcom::xpcf::IComponentIntrospect {
                public:
                    /// @brief I2DTO3DTransformDecomposer default constructor.
                    I2DTO3DTransformDecomposer() = default;

                    /// @brief IFundamentalMatrixDecomposer default destructor.
                    virtual ~I2DTO3DTransformDecomposer() = default;
                    /// @brief decompose a transform 2d to a transform 3d (4  possible poses {R1,t1},{R1,t2}, {R2,t1}, {R2,t2}).
                    /// @param[in] Transform 2D (fundamental matrxi, homgraphy..).
                    /// @param[in] Camera calibration matrix parameters.
                    /// @param[in] Camera calibration distorsion parameters.
                    /// @param[out] Set (04 possibles cases) of the decomposed camera poses in the world coordinate system expressed as Transform3D.
                    virtual bool decompose(const Transform2Df& F,
                                           const CamCalibration& K,
                                           const CamDistortion& dist,
                                           std::vector<Transform3Df>& decomposedPoses)= 0;
                    XPCF_DECLARE_UUID("0404e8b9-b824-4852-a34d-6eafa7563918");
                };
            }
        }
    }
}  // end of namespace Solar
#endif // SOLAR_IHOMOGRAPHYESTIMATION_H
