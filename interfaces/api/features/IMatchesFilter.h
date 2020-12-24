#ifndef IMATCHESFILTER_H
#define IMATCHESFILTER_H


#include "xpcf/api/IComponentIntrospect.h"
#include "core/Messages.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/Keyline.h"
#include "datastructure/Keypoint.h"
#include "datastructure/CameraDefinitions.h"

namespace SolAR {
namespace api {
namespace features {
   /** @class IMatchesFilter
     * @brief <B>Filters a set of matches.</B>
     * <TT>UUID: e0d6cc82-6af2-493d-901a-2384fca0b16f</TT>
     */
    class IMatchesFilter : virtual public org::bcom::xpcf::IComponentIntrospect {
    public:
        ///@brief IMatchesFilter default constructor.
        IMatchesFilter() = default;
        ///@brief IMatchesFilter default destructor.
        virtual ~IMatchesFilter() = default;

        /// @brief filter matches.
        /// @param[in] Original matches found between two descriptors "desc_1" and "desc_2".
        /// @param[out] Filtred matches based on redundancy or geometric relations such as epipolar constraint.
        /// @param[in] Original keypoints associated to desc_1.
        /// @param[in] Original keypoints associated to desc_2.
         virtual void filter(const std::vector<datastructure::DescriptorMatch> & inputMatches,
                             std::vector<datastructure::DescriptorMatch> & outputMatches,
                             const std::vector<datastructure::Keypoint> & keyPoints_1,
                             const std::vector<datastructure::Keypoint> & keyPoints_2) = 0;

		/// @brief filter matches.
		/// @param[in] Original matches found between two descriptors "desc_1" and "desc_2".
		/// @param[out] Filtred matches based on redundancy or geometric relations such as epipolar constraint.
		/// @param[in] Original keylines associated to desc_1.
		/// @param[in] Original keylines associated to desc_2.
		virtual void filter([[maybe_unused]] const std::vector<datastructure::DescriptorMatch> & inputMatches,
							[[maybe_unused]] std::vector<datastructure::DescriptorMatch> & outputMatches,
							[[maybe_unused]] const std::vector<datastructure::Keyline> & keylines_1,
							[[maybe_unused]] const std::vector<datastructure::Keyline> & keylines_2) {};

		/// @brief filter matches based fundamental matrix calculated from camera matrices
		/// @param[in] Original matches found between two descriptors "desc_1" and "desc_2".
		/// @param[out] Filtred matches based on geometric relations such as epipolar constraint.
		/// @param[in] Original keypoints associated to desc_1.
		/// @param[in] Original keypoints associated to desc_2.
		/// @param[in] camera pose 1.
		/// @param[in] camera pose 2.
		/// @param[in] camera's intrinsic parameters.
        virtual void filter([[maybe_unused]] const std::vector<datastructure::DescriptorMatch> & inputMatches,
                            [[maybe_unused]] std::vector<datastructure::DescriptorMatch> & outputMatches,
                            [[maybe_unused]] const std::vector<datastructure::Keypoint> & inputKeyPoints1,
                            [[maybe_unused]] const std::vector<datastructure::Keypoint> & inputKeyPoints2,
                            [[maybe_unused]] const datastructure::Transform3Df &pose1,
                            [[maybe_unused]] const datastructure::Transform3Df &pose2,
                            [[maybe_unused]] const datastructure::CamCalibration &intrinsicParams) {};
    };
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IMatchesFilter,
                             "e0d6cc82-6af2-493d-901a-2384fca0b16f",
                             "IMatchesFilter",
                             "SolAR::api::features::IMatchesFilter");


#endif // IMATCHESFILTER_H
