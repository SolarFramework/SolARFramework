#ifndef IBUNDLER_H
#define IBUNDLER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED


// Definition of IMapFilter Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/CloudPoint.h"
#include "datastructure/Keyframe.h"


namespace SolAR {
using namespace datastructure;
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
           IBundler() = default;
           ///
           ///@brief ~IBundler
           ///
           virtual ~IBundler() {}



           /// @brief solve a non-linear problem related to bundle adjustement statement expressed as:
           /// minArg(pts3ds,intrinsics,extrinsics) = MIN_cam_i(MIN_3d_j(pts2d_j - reproje(pt3ds_j,intrinsics_i,extrinsics_i)),
           /// @param[in,out] framesToAdjust: contains a set of {2D points, camera extrinsics}.
           /// @param[in,out] mapToAjust: contains a set of of 3D points .
           /// @param[in,out] K: camera calibration parameters responsible of 3D points generation.
           /// @param[in,out] D: camera distorsion parameters responsible of 3D points generation
           /// K, D represent the camera intrinsic parameters
           /// @return[in] selectKeyframes : selected views to bundle following a given strategies (ex: poseGraph).
           /// @return the mean re-projection error after {pts3d, intrinsic, extrinsic} correction.
		   /*
           virtual  double solve(std::vector<SRef<Keyframe>> & framesToAdjust,
                                 std::vector<CloudPoint> & mapToAdjust,
                                 CamCalibration & K,
                                 CamDistortion & D,
                                 const std::vector<int> & selectKeyframes) = 0;
								 */


		   virtual  double solve(const std::vector<SRef<Keyframe>> & framesToAdjust,
							     const std::vector<CloudPoint> & mapToAdjust,
							     const  CamCalibration & K,
							     const CamDistortion & D,
							     const std::vector<int> & selectKeyframes,
							     std::vector<Transform3Df> & poseAdjusted,
							     std::vector<CloudPoint>&mapAdjusted,
							     CamCalibration&KAdjusted,
							     CamDistortion &DAdjusted) = 0;


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
