#ifndef IBUNDLER_H
#define IBUNDLER_H

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

                       virtual  bool adjustBundle(const std::string&path_bundle,
                                                  std::vector<SRef<CloudPoint>>& cloud_before,
                                                  std::vector<SRef<CloudPoint>>& cloud_after) = 0;

                       virtual  bool adjustBundle(std::vector<SRef<Keyframe>>&framesToAdjust,
                                                  std::vector<SRef<CloudPoint>>&mapToAdjust,
                                                  std::vector<int>&selectKeyframes) = 0;

                       virtual  bool saveBundleProblem(std::string &path_ba) = 0;


            };
            }
        }
    }
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IBundler,
                             "35b9bdb7-d23c-4909-984f-ae7f9a292e6c",
                             "SolAR::api::solver::map::IBundler interface");

#endif // IMAPPER_H
