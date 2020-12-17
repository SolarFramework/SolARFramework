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

#ifndef SOLAR_IMARKER2DSQUAREDBINARY_H
#define SOLAR_IMARKER2DSQUAREDBINARY_H


#include "IMarker2DSquared.h"
#include "core/Messages.h"
#include "datastructure/Image.h"
#include "datastructure/SquaredBinaryPattern.h"

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace api {
namespace input {
namespace files {

/**
 * @class IMarker2DSquaredBinary
 * @brief <B>Loads 2D squared marker based on a black and white grid.</B>
 * <TT>UUID: 12d592ff-aa46-40a6-8d65-7fbfb382d60b</TT>
 *
 */
class  [[xpcf::ignore]] IMarker2DSquaredBinary : virtual public IMarker2DSquared {
public:
    IMarker2DSquaredBinary() = default;
    virtual ~IMarker2DSquaredBinary() = default;

    /// @brief Return the pattern of the 2D squared marker
    /// @return datastructure::SquaredBinaryPattern the pattern of the 2D squared marker
    virtual const datastructure::SquaredBinaryPattern & getPattern() const = 0;
};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::files::IMarker2DSquaredBinary,
                             "12d592ff-aa46-40a6-8d65-7fbfb382d60b",
                             "IMarker2DSquaredBinary",
                             "SolAR::api::input::files::IMarker2DSquaredBinary interface");

#endif // SOLAR_IMARKER2DSQUAREDBINARY_H
