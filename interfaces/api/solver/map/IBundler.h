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
           /// @param[in, out] K: camera calibration parameters responsible of 3D points generation.
           /// @param[in, out] D: camera distorsion parameters responsible of 3D points generation
           /// @param[in] selectKeyframes : selected views to bundle following a given strategies. If it is empty then take all keyframes into account to perform global bundle adjustment.
		   /// @param[in] useSpanningTree: in the case of the global bundle adjustment, if it true, the optimization is based on a maximal spanning tree.
           /// @return the mean re-projection error after optimization.
           virtual  double bundleAdjustment(CamCalibration & K,
                                            CamDistortion & D,
                                            const std::vector<uint32_t> & selectKeyframes,
											const bool & useSpanningTree = false) = 0;
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
