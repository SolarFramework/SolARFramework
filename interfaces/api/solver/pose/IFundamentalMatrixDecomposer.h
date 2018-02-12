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

#ifndef SOLAR_IFUNDAMENTALMATRIXDECOMPOSER_H
#define SOLAR_IFUNDAMENTALMATRIXDECOMPOSER_H

#include "IComponentIntrospect.h"

#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Pose.h"


namespace SolAR {
using namespace datastructure;
    namespace api {
        namespace solver {
            namespace pose {

                /// @class IFundamentalMatrixDecomposer

                class  IFundamentalMatrixDecomposer : public virtual org::bcom::xpcf::IComponentIntrospect {
                public:
                    /// @brief IFundamentalMatrixDecomposer default constructor
                    IFundamentalMatrixDecomposer() = default;

                    /// @brief IFundamentalMatrixDecomposer default destructor
                    virtual ~IFundamentalMatrixDecomposer() = default;

                    /// @brief decompose the fundamental matrix to 4 pose possibilities ((R1,t1),(R1,t2), (R2,t1), (R2,t2))
                    virtual bool decompose(const Transform2Df&F, const CamCalibration&K, std::vector<SRef<Pose>>& decomposedPoses)= 0;

                    XPCF_DECLARE_UUID("1697e697-e6df-4e6a-b8e7-d78ddc03f3f6");
                };

            }
        }
    }
}  // end of namespace Solar
#endif // SOLAR_IHOMOGRAPHYESTIMATION_H
