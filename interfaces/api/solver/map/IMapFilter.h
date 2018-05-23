#ifndef IMAPFILTER_H
#define IMAPFILTER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

// Definition of IMapper Class //
// part of SolAR namespace //

#include "IComponentIntrospect.h"
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
                       virtual void filter(std::vector<SRef<CloudPoint>>& input,
                                           std::vector<SRef<CloudPoint>>& output) = 0;

                       virtual void testMethod()=0;
                       XPCF_DECLARE_UUID("e0d6cc82-6af2-493d-901a-2384fca0b16f");
                    };
            }
        }
    }
}


#endif // IMAPPER_H
