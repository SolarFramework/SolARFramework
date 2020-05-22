/**
 * @copyright Copyright (c) 2017 B-com http://www.b-com.com/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SOLAR_I2D3DCORRESPONDENCESFINDER_H
#define SOLAR_I2D3DCORRESPONDENCESFINDER_H

#include "xpcf/api/IComponentIntrospect.h"

#include "core/Messages.h"

#include "datastructure/GeometryDefinitions.h"
#include "datastructure/MathDefinitions.h"
#include "datastructure/Keyframe.h"
#include "api/storage/IPointCloudManager.h"

namespace SolAR {
using namespace datastructure;
using namespace api::storage;
namespace api {	
namespace solver {
namespace pose {
/**
 * @class I2D3DCorrespondencesFinder
 * @brief <B>Finds the 2D-3D correspondences giving a frame and its matches with a second frame which has known 2D-3D correspondences.</B>
 * <TT>UUID: 0404e8b9-b824-4852-a34d-6eafa7563918</TT>
 *
 * Knowing a frame, its reference keyframe which already has 3D correpspondences, as well the 2D matches between them, the component find the 2d-3D correspondences between the current frame and the 3D Points visible from the reference keyframe.
 */
    class  I2D3DCorrespondencesFinder : virtual public org::bcom::xpcf::IComponentIntrospect {
    public:
        /// @brief I2D3DCorrespondencesFinder default constructor.
        I2D3DCorrespondencesFinder() = default;

        /// @brief IFundamentalMatrixDecomposer default destructor.
        ///
        virtual ~I2D3DCorrespondencesFinder() = default;
        /// @brief .
        /// @param[in] referenceKeyfram: The reference keyframe which have both 2D-3D correspondences and matches with th ecurrent frame.
        /// @param[in] currentFrame: The current framr for which we want to find 2D-3D correspondances.
        /// @param[in] currentMatches: The 2D matches between the current keyframe and its reference keyframe.
        /// @param[out] shared_mapPoint: The 3D cloud points visible from the current frame.
        /// @param[out] shared_3dpoint: The 3D points visible from the current frame.
        /// @param[out] shared_2Dpoint: The 2D point in the current frame that correspond to a 3D point.
        /// @param[out] found_matches: The matches between the current frame and its reference keyframe which have a 3 correspondant.
        /// @param[out] remaining_matches: The matches between the current frame and its reference keyframe for which no 3D points have been found.
        virtual FrameworkReturnCode  find(const SRef<Keyframe> referenceKeyframe,
                                          const SRef<Frame> currentFrame,
                                          const std::vector<DescriptorMatch> & current_matches,
                                          const SRef<IPointCloudManager> &worldMap,
                                          std::vector<Point3Df> & shared_3dpoint,
                                          std::vector<Point2Df> & shared_2dpoint,
                                          std::vector<DescriptorMatch> & found_matches,
                                          std::vector<DescriptorMatch> & remaining_matches)=0;

        /// @brief .
        /// @param[in] lastFrame: The temporally last frame to the current frame.
        /// @param[in] currentFrame: The current framr for which we want to find 2D-3D correspondances.
        /// @param[in] currentMatches: The 2D matches between the current keyframe and its reference keyframe.
        /// @param[out] shared_mapPoint: The 3D cloud points visible from the current frame.
        /// @param[out] shared_3dpoint: The 3D points visible from the current frame.
        /// @param[out] shared_2Dpoint: The 2D point in the current frame that correspond to a 3D point.
        /// @param[out] found_matches: The matches between the current frame and its reference keyframe which have a 3 correspondant.
        /// @param[out] remaining_matches: The matches between the current frame and its reference keyframe for which no 3D points have been found.
        virtual FrameworkReturnCode find(	const SRef<Frame> lastFrame,
                                            const SRef<Frame> currentFrame,
                                            const std::vector<DescriptorMatch> & current_matches,
											const SRef<IPointCloudManager> &worldMap,
                                            std::vector<Point3Df> & shared_3dpoint,
                                            std::vector<Point2Df> & shared_2dpoint,
                                            std::vector<DescriptorMatch> & found_matches,
                                            std::vector<DescriptorMatch> & remaining_matches) = 0;

    };
}
}
}
}  // end of namespace Solar


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::I2D3DCorrespondencesFinder,
                             "0404e8b9-b824-4852-a34d-6eafa7563918",
                             "I2D3DCorrespondencesFinder",
                             "SolAR::api::solver::pose::I2D3DCorrespondencesFinder");


#endif // SOLAR_IHOMOGRAPHYESTIMATION_H
