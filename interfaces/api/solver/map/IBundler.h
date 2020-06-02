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

namespace SolAR {
using namespace datastructure;
namespace api {
namespace solver {
namespace map {
/**
  * @class IBundler
  * @brief <B>Optimize a system of 3D points and keyframes.</B>
  * <TT>UUID: 35b9bdb7-d23c-4909-984f-ae7f9a292e6c</TT>
  */

class IBundler : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    IBundler() = default;
    ///
    ///@brief ~IBundler
    ///
    virtual ~IBundler() {}

	/// @brief this method is used to set intrinsic parameters and distortion of the camera
	/// @param[in] Camera calibration matrix parameters.
	/// @param[in] Camera distortion parameters.
	virtual void setCameraParameters(const CamCalibration & intrinsicParams, const CamDistortion & distortionParams) = 0;

	/// @brief solve a non-linear problem related to bundle adjustement statement expressed as:
	/// minArg(pts3ds,intrinsics,extrinsics) = MIN_cam_i(MIN_3d_j(pts2d_j - reproje(pt3ds_j,intrinsics_i,extrinsics_i)),
	/// @param[in,out] framesToAdjust: contains a set of {2D points, camera extrinsics}.
	/// @param[in,out] mapToAjust: contains a set of of 3D points .
	/// @param[in] K: camera calibration parameters responsible of 3D points generation.
	/// @param[in] D: camera distorsion parameters responsible of 3D points generation
	/// K, D represent the camera intrinsic parameters
	/// @param[in] selectKeyframes : selected views to bundle following a given strategies (ex: poseGraph).
	/// @return the mean re-projection error after {pts3d, intrinsic, extrinsic} correction.
	virtual double solve(const std::vector<SRef<Keyframe>> & framesToAdjust,
						const std::vector<CloudPoint> & mapToAdjust,
						const CamCalibration & K,
						const CamDistortion & D,
						const std::vector<int> & selectKeyframes,
						std::vector<Transform3Df> & poseAdjusted,
						std::vector<CloudPoint> & mapAdjusted,
						CamCalibration & KAdjusted,
						CamDistortion & DAdjusted) = 0;

	/// @brief (Deprecated) Apply bundle adjustment on a set of 3D lines between two frames
	/// @param[in] originalKeylines: set of 2D correspondences for each given frame.
	/// @param[in] lineCloud: set of 3D lines as <Edge3Df>.
	/// @param[in] matches: set of 2D line correspondences.
	/// @param[in] indices: link 2D line correspondence index from matches vector with the triangulated 3D line from lineCloud.
	/// @param[in] originalPoses: set of camera poses for each given frame.
	/// @param[out] correctedLineCloud: corrected 3D line cloud.
	/// @param[out] correctedPoses: corrected camera poses.
	/// @return the mean re-projection error after 3D lines and poses correction.
	virtual double solve(const std::vector<std::vector<Keyline>> & originalKeylines,
						const std::vector<Edge3Df> & lineCloud,
						const std::vector<DescriptorMatch> & matches,
						const std::vector<int> & indices,
						const std::vector<Transform3Df> originalPoses,
						std::vector<Edge3Df> & correctedLineCloud,
						std::vector<Transform3Df> & correctedPoses) = 0;

	/// @brief (Deprecated) Apply bundle adjustment on a set of 3D lines between multiple frames
	/// @param[in] originalFrames: set of frames with extracted 2D lines and estimated camera poses.
	/// @param[in] frameTriangulatedLines: set of triangulated <Edge3Df> for each frame pair.
	/// @param[in] frameMatches: set of 2D line correspondences for each frame pair.
	/// @param[in] frame2D3DCorrespondences: link 2D line correspondence index with the triangulated 3D line, for each frame pair.
	/// @param[in] fixedFramesIndices: indices of the frames that will be fixed during optimization.
	/// @param[out] correctedLineCloud: corrected 3D line cloud.
	/// @param[out] correctedPoses: corrected camera poses.
	/// @return the mean re-projection error after 3D lines and poses correction.
	virtual double solve(const std::vector<SRef<Frame>> & originalFrames,
						const std::vector<std::vector<Edge3Df>> & frameTriangulatedLines,
						const std::vector<std::vector<DescriptorMatch>> & frameMatches,
						const std::vector<std::vector<int>> & frame2D3DCorrespondences,
						const std::vector<int> & fixedFramesIndices,
						std::vector<Edge3Df> & correctedLineCloud,
						std::vector<Transform3Df> & correctedPoses) = 0;

	/// @brief Apply bundle adjustment on a set of 3D lines between multiple frames
	/// @param[in] originalFrames: set of frames with extracted 2D lines and estimated camera poses.
	/// @param[in] frameTriangulatedLines: set of triangulated <CloudLine> for each frame pair.
	/// @param[out] correctedLineCloud: corrected 3D line cloud.
	/// @param[out] correctedPoses: corrected camera poses.
	/// @return the mean re-projection error after 3D lines and poses correction.
	virtual double solve(const std::vector<SRef<Frame>> & originalFrames,
						const std::vector<std::vector<CloudLine>> & frameTriangulatedLines,
						std::vector<CloudLine> & correctedLineCloud,
						std::vector<Transform3Df> & correctedPoses) = 0;
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
