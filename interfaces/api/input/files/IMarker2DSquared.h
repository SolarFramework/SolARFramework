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

#ifndef SOLAR_IMARKER2DSQUARED_H
#define SOLAR_IMARKER2DSQUARED_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "xpcf/api/IComponentIntrospect.h"

#include "IMarker.h"

#include "core/Messages.h"
#include "datastructure/Image.h"
#include "datastructure/GeometryDefinitions.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace input {
namespace files {

//!  The abstract class defining all 2D marker
/*!
  The origin of the marker is position at its center. The x-axis points to the right of the marker, the y-axis points to the top of the marker, and the z-axis points frontward.
*/

/**
 * @class IMarker2DSquared
 * @brief Specifies the IMarker2DSquared interface class.
 */
class IMarker2DSquared : public virtual IMarker {
public:
    IMarker2DSquared() = default;
    virtual ~IMarker2DSquared() = default;
    inline void setSize (const float & width, const float & height) { m_size.width = width; m_size.height = height; };
    inline float getWidth() const { return m_size.width; };
    inline float getHeight() const { return m_size.height; };
    inline Sizef getSize() const { return m_size; };

    /// @brief Provide the position of 2D corners in image coordinate system
    /// @param[out] imageCorners the 2D corners of the marker in image coordinate system
    /// @return FrameworkReturnCode::_SUCCESS if sucessful, eiher FrameworkRetunrnCode::_ERROR_.
    virtual FrameworkReturnCode getImageCorners(std::vector<SRef<Point2Df>>& imageCorners) const = 0;

    /// @brief Provide the position of 3D corners in world coordinate system
    /// @param[out] worldCorners the 3D corners of the marker in world coordinate system
    /// @return FrameworkReturnCode::_SUCCESS if sucessful, eiher FrameworkRetunrnCode::_ERROR_.
    virtual FrameworkReturnCode getWorldCorners(std::vector<SRef<Point3Df>>& worldCorners) const = 0;

protected:
    Sizef m_size;  ///<define the size of the 2D Marker according to the user-defined unit (the same used for the camera calibration)

};

}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::input::files::IMarker2DSquared,
                             "e9cdcf6e-c54c-11e7-abc4-cec278b6b50a",
                             "IMarker2DSquared",
                             "SolAR::api::input::files::IMarker2DSquared interface");

#endif // SOLAR_IMARKER2DSQUARED_H

