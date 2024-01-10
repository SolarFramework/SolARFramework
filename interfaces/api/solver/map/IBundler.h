#ifndef IBUNDLER_H
#define IBUNDLER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED


// Definition of IMapFilter Class //
// part of SolAR namespace //

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/CloudPoint.h"
#include "datastructure/Keyframe.h"
#include "datastructure/Map.h"

namespace SolAR {
namespace api {
namespace solver {
namespace map {
/**
* @class IBundler
* @brief <B>Optimizes a system of 3D points and keyframes.</B>
* <TT>UUID: 35b9bdb7-d23c-4909-984f-ae7f9a292e6c</TT>
*/

class XPCF_CLIENTUUID("258dfecc-850e-4ec7-9b25-77c5bca8694a") XPCF_SERVERUUID("96d272a9-fbc8-4a77-83ad-63edd60a8065") IBundler :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief IBundler default constructor
	IBundler() = default;

	///@brief ~IBundler default destructor
	virtual ~IBundler() = default;

	/// @brief set map reference to optimize
	/// @param[in] map the input map.
	/// @return FrameworkReturnCode::_SUCCESS_ if the map is set, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode setMap(const SRef<SolAR::datastructure::Map> map) = 0;

	/// @brief solve a non-linear problem related to bundle adjustement statement expressed as:
	/// minArg(pts3ds,intrinsics,extrinsics) = MIN_cam_i(MIN_3d_j(pts2d_j - reproje(pt3ds_j,intrinsics_i,extrinsics_i)),
    /// @param[in] selectKeyframes selected views to bundle following a given strategies. If it is empty then take all keyframes into account to perform global bundle adjustment.
	/// @return the mean re-projection error after optimization.
    virtual double bundleAdjustment(const std::vector<uint32_t> & selectKeyframes = {}) = 0;
	
	/// @brief solve a non-linear problem related to sim3D optimization between two overlaped keyframes of two different maps:
    /// @param[in] keyframe1 first overlapping keyframe from map 1.
    /// @param[in] keyframe2 second overlapping keyframe from map 2.
    /// @param[in] matches matches between two keyframes.
    /// @param[in] pts3D1 first set of 3D points.
    /// @param[in] pts3D2 second set of 3D points.
	/// @param[in, out] pose: Sim3 matrix pose between map1 and map2
	/// @return the mean re-projection error.
    virtual double optimizeSim3(const SRef<SolAR::datastructure::Keyframe>& keyframe1,
                                const SRef<SolAR::datastructure::Keyframe>& keyframe2,
                                const std::vector<SolAR::datastructure::DescriptorMatch>& matches,
                                const std::vector<SolAR::datastructure::Point3Df> & pts3D1,
                                const std::vector<SolAR::datastructure::Point3Df> & pts3D2,
                                SolAR::datastructure::Transform3Df & pose) = 0;
};
}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IBundler,
                             "35b9bdb7-d23c-4909-984f-ae7f9a292e6c",
                             "IBundler",
                             "SolAR::api::solver::map::IBundler interface for a bundle adjustement solver.");

#endif // IMapFilter_H
