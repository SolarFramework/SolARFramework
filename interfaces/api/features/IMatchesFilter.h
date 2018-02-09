#ifndef IMATCHESFILTER_H
#define IMATCHESFILTER_H


#include "IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/Keypoint.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace features {

class IMatchesFilter : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    IMatchesFilter() = default;
    virtual ~IMatchesFilter() = default;

    /// @brief filter matches.
    /// Draw all the lines joining the keypoints that match between two images
    /// @param[in] inputMatches: original matches found between two descriptors "desc_1" and "desc_2".
    /// @param[out] outputMatches: filtred matches based on redanduncy or geometric relations such as epipolar constraint
    /// @param[in] keypoints_1: The original keypoints associated to desc_1.
    /// @param[in] keypoints_2: The original keypoints associated to desc_2.
     virtual void filter(std::vector<DescriptorMatch>&inputMatches,
                         std::vector<DescriptorMatch>&outputMatches,
                         std::vector<SRef<Keypoint>>&keyPoints_1,
                         std::vector<SRef<Keypoint>>&keyPoints_2) = 0;

      XPCF_DECLARE_UUID("e0d6cc82-6af2-493d-901a-2384fca0b16f");
};

}
}
}


#endif // IMATCHESFILTER_H
