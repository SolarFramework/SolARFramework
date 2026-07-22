/*******************************************************************************
 *  SolAR ARCloud
 *  (C) Copyright 2026 b<>com. All rights reserved.
 *
 *  IDDN: FR.001.020021.005.S.C.2024.000.00000
 *  This software is the confidential intellectual property of b<>com.
 *  You shall not disclose it and shall use it only in accordance with
 *  the terms of the license agreement you entered into with b<>com.
 *
 ********************************************************************************/
#ifndef SOLAR_API_DISPLAY_I3DMESHVIEWER_H
#define SOLAR_API_DISPLAY_I3DMESHVIEWER_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/traits.h>
#include "core/Messages.h"
#include "datastructure/Mesh.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"

#include <vector>

namespace SolAR {
namespace api {
namespace display {

/**
 * @class I3DMeshViewer
 * @brief Display a triangle mesh in an interactive 3D OpenGL window.
 * <TT>UUID: a9f5bdee-c3f6-4b7a-a1d2-1e2f3a4b5c6d</TT>
 */
class XPCF_IGNORE I3DMeshViewer : virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
    I3DMeshViewer() = default;
    virtual ~I3DMeshViewer() = default;

    /// @brief Display the mesh in a 3D window.
    /// @param[in] mesh The triangle mesh to render.
    /// @param[in] pose Current camera pose (world-to-camera transform used to draw a frustum overlay).
    /// @param[in] keyframePoses Optional set of keyframe poses to overlay as frustums.
    /// @return FrameworkReturnCode::_SUCCESS, or _STOP when the user requests to close the window.
    virtual FrameworkReturnCode display(
        const SRef<SolAR::datastructure::Mesh> & mesh,
        const SolAR::datastructure::Transform3Df & pose,
        const std::vector<SolAR::datastructure::Transform3Df> & keyframePoses = {}) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::display::I3DMeshViewer,
                             "a9f5bdee-c3f6-4b7a-a1d2-1e2f3a4b5c6d",
                             "I3DMeshViewer",
                             "Display a 3D triangle mesh in an interactive OpenGL window");

#endif // SOLAR_API_DISPLAY_I3DMESHVIEWER_H