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

#ifndef SOLAR_IHOMOGRAPHYVALIDATION_H
#define SOLAR_IHOMOGRAPHYVALIDATION_H

#include "IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Image.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace solver {
namespace pose {

/// @class IHomographyValidation

class  IHomographyValidation : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IHomographyValidation default constructor
    IHomographyValidation() = default;

    /// @brief IHomographyValidation default destructor
    virtual ~IHomographyValidation() = default;

    /// @brief evaluate the homography according to the projection of the 4 corners of a 2D squared Marker
    virtual bool isValid(const std::vector<SRef<Point2Df>>& ref2DSquaredMarkerCorners, const std::vector<SRef<Point2Df>>& projected2DSquaredMarkerCorners) = 0;

    XPCF_DECLARE_UUID("e95e8f70-dd32-11e7-9296-cec278b6b50a");
};

}
}
}
}  // end of namespace Solar

#endif // SOLAR_IHOMOGRAPHYVALIDATION_H
