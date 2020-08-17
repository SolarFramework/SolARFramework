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

#ifndef SOLAR_I3D3DCORRESPONDENCESFINDER_H
#define SOLAR_I3D3DCORRESPONDENCESFINDER_H

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
 * @class I3D3DCorrespondencesFinder
 * @brief <B>Finds the 3D-3D correspondences from feature matches of two keyframes.</B>
 * <TT>UUID: 90068876-655a-4d86-adfc-96a519041ab3</TT>
 */
    class  I3D3DCorrespondencesFinder : virtual public org::bcom::xpcf::IComponentIntrospect {
    public:
        /// @brief I3D3DCorrespondencesFinder default constructor.
        I3D3DCorrespondencesFinder() = default;

        /// @brief IFundamentalMatrixDecomposer default destructor.
        ///
        virtual ~I3D3DCorrespondencesFinder() = default;

        /// @brief Define 3D-3D point correspondences of two keyframes based on keypoint matches.
        /// @param[in] firstKeyframe: The first keyframe.
        /// @param[in] secondKeyframe: The second keyframe.
        /// @param[in] currentMatches: The 2D matches between the current keyframe and its reference keyframe.
        /// @param[out] firstCloudPoints: The cloud points seen from the first keyframe.
        /// @param[out] secondCloudPoints: The cloud points seen from the second keyframe.
        /// @param[out] found_matches: The matches allow to define 3D-3D correspondences.
        /// @param[out] remaining_matches: The remaining matches.
        virtual FrameworkReturnCode find(	const SRef<Keyframe> firstKeyframe,
                                            const SRef<Keyframe> secondKeyframe,
                                            const std::vector<DescriptorMatch> & current_matches,
                                            std::vector<SRef<CloudPoint>> & firstCloudPoints,
                                            std::vector<SRef<CloudPoint>> & secondCloudPoints,
                                            std::vector<DescriptorMatch> & found_matches,
                                            std::vector<DescriptorMatch> & remaining_matches) = 0;

    };
}
}
}
}  // end of namespace Solar


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::I3D3DCorrespondencesFinder,
                             "90068876-655a-4d86-adfc-96a519041ab3",
                             "I3D3DCorrespondencesFinder",
                             "SolAR::api::solver::pose::I3D3DCorrespondencesFinder");


#endif // SOLAR_I3D3DCORRESPONDENCESFINDER_H
