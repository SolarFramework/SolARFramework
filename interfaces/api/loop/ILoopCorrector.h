#ifndef ILOOPCORRECTOR_H
#define ILOOPCORRECTOR_H


#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED


// Definition of ILoopCorrector Class //
// part of SolAR namespace //
#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"

namespace SolAR {
// using namespace datastructure;
namespace api {
namespace loop{

/**
  * @class ILoopCorrector
  * @brief <B>Optimizes a system of 3D points and keyframes from a loop losing detection. </B>
  * <TT>UUID: 8f05eea8-c1c6-11ea-b3de-0242ac130004</TT>
  */

	class  ILoopCorrector : virtual public org::bcom::xpcf::IComponentIntrospect {
	public:
		ILoopCorrector() = default;
		///
		///@brief ~ILoopCorrector
		///
		virtual ~ILoopCorrector() {}

		/// @brief corrects a loop of keyframes and their associated point clouds from a loop detection result.
		/// @param[in] reference_keyframe_id: reference keyframe id.
		/// @param[in] loop_keyframe_id: detected loop keyframe id.
		/// @param[in] S_c_wl : 3D similarity transformation (Sim(3)) from loop world c.s to reference keyframe c.s..
        /// @return the mean re-projection error after optimization.
        // virtual  double correctsLoop(   const uint32_t reference_keyframe_id, const uint32_t loop_keyframe_id, const Transform3Df& S_c_wl) = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::loop::ILoopCorrector,
                             "8f05eea8-c1c6-11ea-b3de-0242ac130004",
                             "ILoopCorrector",
                             "SolAR::api::loop::ILoopCorrector interface for a bundle adjustement solver.");

#endif // IMapFilter_H
