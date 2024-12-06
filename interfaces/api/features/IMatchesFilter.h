#ifndef IMATCHESFILTER_H
#define IMATCHESFILTER_H


#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "datastructure/DescriptorMatch.h"
#include "datastructure/Keypoint.h"
#include "datastructure/CameraDefinitions.h"

namespace SolAR {
namespace api {
namespace features {
   /** @class IMatchesFilter
     * @brief <B>Filters a set of matches.</B>
     * <TT>UUID: e0d6cc82-6af2-493d-901a-2384fca0b16f</TT>
     */
    class XPCF_IGNORE IMatchesFilter :
        virtual public org::bcom::xpcf::IComponentIntrospect {
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
         virtual void filter(const std::vector<SolAR::datastructure::DescriptorMatch> & inputMatches,
                             std::vector<SolAR::datastructure::DescriptorMatch> & outputMatches,
                             const std::vector<SolAR::datastructure::Keypoint> & keyPoints_1,
                             const std::vector<SolAR::datastructure::Keypoint> & keyPoints_2) = 0;
        
        /// @brief filter matches and get the fundamental matrix
        /// @param[in] keypoints1 list of undistorted keypoints of the first keyframe 
        /// @param[in] keypoints2 list of undistorted keypoints of the second keyframe
        /// @param[in] inputMatches list of descriptor matches
        /// @param[in] intrinsicParams1 intrinsic parameters of first keyframe
        /// @param[in] intrinsicParams2 intrinsic parameters of second keyframe
        /// @param[out] outputMatches list of filtered descriptor matches
        /// @param[out] relativePose list of 4 possible relative poses from first to second keyframes (translation vector is normalized, length is 1)
        virtual FrameworkReturnCode filter(const std::vector<SolAR::datastructure::Keypoint>& keypoints1,
                                           const std::vector<SolAR::datastructure::Keypoint>& keypoints2,
                                           const std::vector<SolAR::datastructure::DescriptorMatch>& inputMatches,
                                           const SolAR::datastructure::CamCalibration& intrinsicParams1,
                                           const SolAR::datastructure::CamCalibration& intrinsicParams2,
                                           std::vector<SolAR::datastructure::DescriptorMatch>& outputMatches,
                                           std::vector<SolAR::datastructure::Transform3Df>& relativePose) = 0;

		/// @brief filter matches based fundamental matrix calculated from camera matrices
		/// @param[in] Original matches found between two descriptors "desc_1" and "desc_2".
		/// @param[out] Filtred matches based on geometric relations such as epipolar constraint.
		/// @param[in] Original keypoints associated to desc_1.
		/// @param[in] Original keypoints associated to desc_2.
        /// @param[in] camera pose 1.
		/// @param[in] camera pose 2.
		/// @param[in] first camera's intrinsic parameters.
               /// @param[in] second camera's intrinsic parameters.
        virtual FrameworkReturnCode filter(const std::vector<SolAR::datastructure::DescriptorMatch> & inputMatches,
                                           std::vector<SolAR::datastructure::DescriptorMatch> & outputMatches,
                                           const std::vector<SolAR::datastructure::Keypoint> & inputKeyPoints1,
                                           const std::vector<SolAR::datastructure::Keypoint> & inputKeyPoints2,
                                           const SolAR::datastructure::Transform3Df &pose1,
                                           const SolAR::datastructure::Transform3Df &pose2,
                                           const SolAR::datastructure::CamCalibration &intrinsicParams1,
                                           const SolAR::datastructure::CamCalibration &intrinsicParams2 = SolAR::datastructure::CamCalibration::Zero()) = 0;
    };
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IMatchesFilter,
                             "e0d6cc82-6af2-493d-901a-2384fca0b16f",
                             "IMatchesFilter",
                             "SolAR::api::features::IMatchesFilter");


#endif // IMATCHESFILTER_H
