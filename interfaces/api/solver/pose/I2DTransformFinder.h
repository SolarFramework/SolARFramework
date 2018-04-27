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

#ifndef SOLAR_I2DTRANSFORMFINDER_H
#define SOLAR_I2DTRANSFORMFINDER_H

#include "IComponentIntrospect.h"

#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"


namespace SolAR {
using namespace datastructure;
    namespace api {
        namespace solver {
            namespace pose {
            namespace Transform2DFinder {
                ///
                /// @brief The 2DTransformFinder return codes.
                ///
                enum  RetCode {
                    TRANSFORM2D_ESTIMATION_OK = 0, /**< the default OK code*/
                    TRANSFORM2D_EMPTY,			  /**< Homgraphy matrix is empty*/
                };

            }
            /**
             * @class I2DransformFinder
             * @brief Finds the 2D transform  of 2D-2D points correspondaces.
             */
                class I2DTransformFinder : public virtual org::bcom::xpcf::IComponentIntrospect {
                public:
                    ///@brief I2DTransformFinder default constructor.
                    I2DTransformFinder() = default;
                    ///@brief I2DTransformFinder default deconstructor.
                    virtual ~I2DTransformFinder() = default;
                    /// @brief Find 2D transform matrix from 2 sets of 2d_points.
                    /// @param[in] Set of 2d_points seen in view_1.
                    /// @param[in] Set of 2d_points seen in view_2.
                    /// @param[out] Estimated 2D transform matrix.
                    ///
                    virtual Transform2DFinder::RetCode find(const std::vector<SRef<Point2Df> >& srcPoints,
                        const std::vector< SRef<Point2Df> >& dstPoints,
                        Transform2Df & fundamental) = 0;
                    static constexpr const char * UUID = "45dd370a-0eab-4a7f-93d0-43453b4c7517";
                };

            }
        }
    }
}

#endif // SOLAR_IHOMOGRAPHYESTIMATION_H
