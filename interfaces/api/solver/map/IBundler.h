#ifndef IBUNDLER_H
#define IBUNDLER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED


// Definition of IBundler Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Keyline.h"
#include "datastructure/Keyframe.h"
#include "api/solver/map/IMapper.h"

namespace SolAR {
namespace api {
namespace solver {
namespace map {

/**
* @class IBundler
* @brief <B>Optimizes a system of 3D points and keyframes.</B>
* <TT>UUID: 35b9bdb7-d23c-4909-984f-ae7f9a292e6c</TT>
*/

class  IBundler : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
	/// @brief IBundler default constructor
	IBundler() = default;

	///@brief ~IBundler default destructor
	virtual ~IBundler() = default;

	/// @brief set mapper reference to optimize
	/// @param[in] map: the input map.
	/// @return FrameworkReturnCode::_SUCCESS_ if the map is set, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode setMapper(const SRef<IMapper> map) = 0;

	/// @brief solve a non-linear problem related to bundle adjustement statement expressed as:
	/// minArg(pts3ds,intrinsics,extrinsics) = MIN_cam_i(MIN_3d_j(pts2d_j - reproje(pt3ds_j,intrinsics_i,extrinsics_i)),
	/// @param[in, out] K: camera calibration parameters responsible of 3D points generation.
	/// @param[in, out] D: camera distorsion parameters responsible of 3D points generation
    /// @param[in] selectKeyframes: selected views to bundle following a given strategies. If it is empty then take all keyframes into account to perform global bundle adjustment.
	/// @return the mean re-projection error after optimization.
	virtual double bundleAdjustment(datastructure::CamCalibration & K,
									datastructure::CamDistortion & D,
									const std::vector<uint32_t> & selectKeyframes = {}) = 0;

	/// @brief Apply bundle adjustment on a set of 3D lines between multiple frames
	/// @param[in] originalFrames: set of frames with extracted 2D lines and estimated camera poses.
	/// @param[in] frameTriangulatedLines: set of triangulated <CloudLine> for each frame pair.
	/// @param[out] correctedLineCloud: corrected 3D line cloud.
	/// @param[out] correctedPoses: corrected camera poses.
	/// @return the mean re-projection error after 3D lines and poses correction.
	virtual double solve(	const std::vector<SRef<datastructure::Frame>> & originalFrames,
							const std::vector<std::vector<SRef<datastructure::CloudLine>>> & frameTriangulatedLines,
							std::vector<SRef<datastructure::CloudLine>> & correctedLineCloud,
							std::vector<datastructure::Transform3Df> & correctedPoses) = 0;

	/// @brief this method is used to set intrinsic parameters and distortion of the camera
	/// @param[in] Camera calibration matrix parameters.
	/// @param[in] Camera distortion parameters.
	virtual void setCameraParameters(const datastructure::CamCalibration & intrinsicParams, const datastructure::CamDistortion & distortionParams) = 0;
};
}
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IBundler,
                             "35b9bdb7-d23c-4909-984f-ae7f9a292e6c",
                             "IBundler",
                             "SolAR::api::solver::map::IBundler interface for a bundle adjustement solver.");

#endif // IBUNDLER_H
