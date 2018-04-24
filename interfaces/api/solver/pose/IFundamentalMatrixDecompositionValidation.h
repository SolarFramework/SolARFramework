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

#ifndef SOLAR_IFUNDAMENTALMATRIXDECOMPOSITIONVALIDATION_H
#define SOLAR_IFUNDAMENTALMATRIXDECOMPOSITIONVALIDATION_H

#include "IComponentIntrospect.h"

#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Pose.h"


namespace SolAR {
using namespace datastructure;
    namespace api {
        namespace solver {
            namespace pose {

                /// @class IFundamentalMatrixDecompositionValidation

                class  IFundamentalMatrixDecompositionValidation : public virtual org::bcom::xpcf::IComponentIntrospect {
                public:
                    /// @brief IFundamentalMatrixDecompositionValidation default constructor
                    IFundamentalMatrixDecompositionValidation() = default;

                    /// @brief IFundamentalMatrixDecompositionValidation default destructor
                    virtual ~IFundamentalMatrixDecompositionValidation() = default;

                    /// @brief evaluate the fundamental according to the projection of the 4 corners of a 2D squared Marker
                    virtual bool isValid(const std::vector<SRef<Point2Df>>&pt2d_v1,
                                         const std::vector<SRef<Point2Df>>&pt2d_v2,
                                         const CamCalibration&K,
                                         const Pose&P1,
                                         const Pose&P2,
                                         const std::vector<SRef<Point3Df>>&pt3d) = 0;
                };

            }
        }
    }
}  // end of namespace Solar

#endif // SOLAR_IHOMOGRAPHYESTIMATION_H
