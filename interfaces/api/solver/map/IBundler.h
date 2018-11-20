#ifndef IBUNDLER_H
#define IBUNDLER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED


// Definition of IMapper Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/CloudPoint.h"
#include "datastructure/Keyframe.h"


namespace SolAR {
    using namespace datastructure;
    namespace api {
        namespace solver {
            namespace map {
///
/// @brief The IBundler class
///

            class  IBundler : public virtual org::bcom::xpcf::IComponentIntrospect {
                    public:
                       IBundler() = default;
                       ///
                       ///@brief ~IBundler
                       ///
                       virtual ~IBundler() {}




                       virtual  bool adjustBundle(std::vector<SRef<Keyframe>>&framesToAdjust,
                                                  std::vector<SRef<CloudPoint>>&mapToAdjust,
                                                  const CamCalibration &K,
                                                  const CamDistortion &D,
                                                  const std::vector<int>&selectKeyframes) = 0;


            };
            }
        }
    }
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IBundler,
                             "35b9bdb7-d23c-4909-984f-ae7f9a292e6c",
                             "IBundler",
                             "SolAR::api::solver::map::IBundler interface for a bundle adjustement solver.");

#endif // IMAPPER_H
