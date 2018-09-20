#ifndef IMAPFILTER_H
#define IMAPFILTER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

// Definition of IMapper Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/Keyframe.h"
#include "datastructure/CloudPoint.h"

namespace SolAR {
    using namespace datastructure;
    namespace api {
        namespace solver {
            namespace map {
///
/// @brief The IMapFilter class
///
class  IMapFilter : public virtual org::bcom::xpcf::IComponentIntrospect {
        public:
           IMapFilter() = default;
           ///
           ///@brief ~IMapper
           ///
           virtual ~IMapFilter() {}

           /// @brief  Filter point cloud reconstructed from 2 viewpoints
           /// @param[in] view1: the first keyframe used for building the point cloud.
           /// @param[in] view2: the second keyframe used for building the point cloud.
           /// @param[in] Set of triangulated 3d_points..
           /// @param[out] filtered point cloud
           virtual void  filter(const SRef<Keyframe> view1, const SRef<Keyframe> view2, const std::vector<SRef<CloudPoint>>& input,  std::vector<SRef<CloudPoint>>& output) = 0;
        };
}

}
}
}
XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IMapFilter,
                             "e0d6cc82-6af2-493d-901a-2384fca0b16f",
                             "SolAR::api::solver::map::IMapFilter interface");


#endif // IMAPPER_H
