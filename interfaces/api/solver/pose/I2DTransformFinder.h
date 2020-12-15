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

#include "xpcf/api/IComponentIntrospect.h"

#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"


namespace SolAR {
namespace api {
namespace solver {
namespace pose {
    class Transform2DFinder {
    public:
        enum  RetCode {
            TRANSFORM2D_ESTIMATION_OK = 0, /**< the default OK code*/
            TRANSFORM2D_EMPTY,			  /**< Homgraphy matrix is empty*/
        };
    };

/**
  * @class I2DTransformFinder
  * @brief <B>Finds the 2D transform from 2D-2D points correspondences.</B>
  * <TT>UUID: 45dd370a-0eab-4a7f-93d0-43453b4c7517</TT>
  */

class I2DTransformFinder : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    ///@brief I2DTransformFinder default constructor.
    I2DTransformFinder() = default;
    ///@brief I2DTransformFinder default deconstructor.
    virtual ~I2DTransformFinder() = default;
    /// @brief Find 2D transform matrix from 2 sets of 2d_points.
    /// @param[in] srcPoints set of 2d_points seen in view_1.
    /// @param[in] dstPoints set of 2d_points seen in view_2.
    /// @param[out] fundamental estimated 2D transform matrix.
    [[grpc::request("findTransform2DRequest")]] [[grpc::response("findTransform2DResponse")]] /// to remove ambiguity with I3D3DCorrespondencesFinder find()
    virtual Transform2DFinder::RetCode find(const std::vector<datastructure::Point2Df> & srcPoints,
        const std::vector<datastructure::Point2Df> & dstPoints,
        datastructure::Transform2Df & fundamental) = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::I2DTransformFinder,
                             "45dd370a-0eab-4a7f-93d0-43453b4c7517",
                             "I2DTransformFinder",
                             "SolAR::api::solver::pose::I2DTransformFinder");

#endif // SOLAR_IHOMOGRAPHYESTIMATION_H
