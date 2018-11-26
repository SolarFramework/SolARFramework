#ifndef IMATCHESFILTER_H
#define IMATCHESFILTER_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/Keypoint.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace features {
    ///@class IMatchesFilter
    class IMatchesFilter : public virtual org::bcom::xpcf::IComponentIntrospect {
    public:
        ///@brief IMatchesFilter default constructor.
        IMatchesFilter() = default;
        ///@brief IMatchesFilter default destructor.
        virtual ~IMatchesFilter() = default;

        /// @brief filter matches.
        /// Draw all the lines joining the keypoints that match between two images
        /// @param[in] Original matches found between two descriptors "desc_1" and "desc_2".
        /// @param[out] Filtred matches based on redanduncy or geometric relations such as epipolar constraint.
        /// @param[in] Original keypoints associated to desc_1.
        /// @param[in] Original keypoints associated to desc_2.
         virtual void filter(const std::vector<DescriptorMatch>&inputMatches,
                             std::vector<DescriptorMatch>&outputMatches,
                             const std::vector<SRef<Keypoint>>&keyPoints_1,
                             const std::vector<SRef<Keypoint>>&keyPoints_2) = 0;
    };
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IMatchesFilter,
                             "e0d6cc82-6af2-493d-901a-2384fca0b16f",
                             "IMatchesFilter",
                             "SolAR::api::features::IMatchesFilter");


#endif // IMATCHESFILTER_H
