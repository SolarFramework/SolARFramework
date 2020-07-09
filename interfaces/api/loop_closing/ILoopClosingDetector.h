#ifndef ILOOPCLOSINGDETECTOR_H
#define ILOOPCLOSINGDETECTOR_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED


// Definition of ILoopClosingDetector Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"


namespace SolAR {
using namespace datastructure;
namespace api {
namespace loop_closing {
/**
  * @class ILoopClosingDetector
  * @brief <B>Detects a loop in from a keyframe and a system of 3D points and keyframes.</B>
  * <TT>UUID: a267c93a-c1c6-11ea-b3de-0242ac130004</TT>
  */

	class  ILoopClosingDetector : virtual public org::bcom::xpcf::IComponentIntrospect {
	public:
		ILoopClosingDetector() = default;
		///
		///@brief ~ILoopClosingDetector
		///
		virtual ~ILoopClosingDetector() {}

		/// @brief detects a loop in from a keyframe and a system of 3D points and keyframes.
		/// @param[out] reference_keyframe_id: reference keyframe id.
		/// @param[out] loop_keyframe_id: detected loop keyframe id.
		/// @param[out] S_c_wl : 3D similarity transformation (Sim(3)) from loop world c.s to reference keyframe c.s..
		/// @return True : if a loop closing is detected ; False : if no loop closing is detected.
        virtual  double detectsLoop( uint32_t & reference_keyframe_id, uint32_t & loop_keyframe_id, Transform3Df & S_c_wl ) = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::loop_closing::ILoopClosingDetector,
                             "a267c93a-c1c6-11ea-b3de-0242ac130004",
                             "ILoopClosingDetector",
                             "SolAR::api::loop_closing::ILoopClosingDetector interface for a bundle adjustement solver.");

#endif // IMapFilter_H
