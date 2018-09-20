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
           /// @param[in] pose1: the first pose used for building the point cloud.
           /// @param[in] pose2: the second pose used for building the point cloud.
           /// @param[in] input: The set of points to filter
           /// @param[out] output: the filtered point cloud
           virtual void  filter(const Transform3Df pose1, const Transform3Df pose2, const std::vector<SRef<CloudPoint>>& input,  std::vector<SRef<CloudPoint>>& output) = 0;
        };
}

}
}
}
XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::map::IMapFilter,
                             "e0d6cc82-6af2-493d-901a-2384fca0b16f",
                             "SolAR::api::solver::map::IMapFilter interface");


#endif // IMAPPER_H
