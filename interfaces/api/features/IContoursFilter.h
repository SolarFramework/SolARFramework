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

#ifndef SOLAR_ICONTOURSFILTER_H
#define SOLAR_ICONTOURSFILTER_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "datastructure/Image.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
namespace api {
namespace features {

/**
 * @class IContoursFilter
 * @brief <B>Filters a set of contours.</B>
 * <TT>UUID: 6b3de3a0-cc72-11e7-abc4-cec278b6b50a</TT>
 *
 * This class provides a filtering method to prune a set of contours.
 */

class XPCF_IGNORE IContoursFilter :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
   /// @brief IContoursFilter default constructor
   IContoursFilter() = default;

   /// @brief IContoursFilter default destructor
   virtual ~IContoursFilter() = default;

   /// @brief Filter a set of contours
   /// @param[in] inContours The contours to filter
   /// @param[out] outContours The resulting vector of contours after filtering
   virtual FrameworkReturnCode filter(const std::vector<SolAR::datastructure::Contour2Df> & inContours, std::vector<SolAR::datastructure::Contour2Df> & outContours) = 0;

};
}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IContoursFilter,
                             "6b3de3a0-cc72-11e7-abc4-cec278b6b50a",
                             "IContoursFilter",
                             "SolAR::api::features::IContoursFilter");

#endif // SOLAR_ICONTOURSFILTER_H
