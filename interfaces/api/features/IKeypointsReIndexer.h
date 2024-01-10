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

#ifndef SOLAR_IKEYPOINTSREINDEXER_H
#define SOLAR_IKEYPOINTSREINDEXER_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>
#include "datastructure/Keypoint.h"
#include "api/features/IDescriptorMatcher.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/DescriptorMatch.h"

namespace SolAR {
namespace api {
namespace features {

/**
 * @class IKeypointsReIndexer
 * @brief <B>Reorganizes the keypoints detected from two images that match together in two vector of points where the nth point of the first vector matches with the nth point of the second vector.</B>
 * <TT>UUID: 920e64a2-df17-11e7-80c1-9a214cf093ae</TT>
 */
class XPCF_CLIENTUUID("681727ef-5122-4b21-8cd0-e56314c215bc") XPCF_SERVERUUID("0305c89a-f5f2-46ce-a3a3-c795179f8e8c") IKeypointsReIndexer :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IKeypointsReIndexer default constructor
    IKeypointsReIndexer() = default;

    /// @brief IContoursExtractor default destructor
    virtual ~IKeypointsReIndexer() = default;

    /// @brief This method reorganizes the keypoints detected from two images that match together in two vector of points where the nth point of the first vector matches with the nth point of the second vector.
    /// @param[in] keypoints1 The first set of keypoints that have been matched.
    /// @param[in] keypoints2 The second set of keypoints that have been matched.
    /// @param[in] matches The matches between the first and the second set of keypoints.
    /// @param[out] matchedKeypoints1 The keypoints from the first set that match with one or more keypoints of the second set of keypoints. The nth point of this set match with the nth point of the second set matchedKeypoints2.
    /// @param[out] matchedKeypoints2 The keypoints from the second set that match with one or more keypoints of the first set of keypoints. The nth point of this set match with the nth point of the first set matchedKeypoints1.
    /// @return FrameworkReturnCode::_SUCCESS_ if reindexing succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode reindex(const std::vector<SolAR::datastructure::Keypoint> & keypoints1,
                                        const std::vector<SolAR::datastructure::Keypoint> & keypoints2,
                                        const std::vector<SolAR::datastructure::DescriptorMatch> & matches,
                                        std::vector<SolAR::datastructure::Point2Df> & matchedKeypoints1,
                                        std::vector<SolAR::datastructure::Point2Df> & matchedKeypoints2) = 0;

};

}
}
}  // end of namespace Solar

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IKeypointsReIndexer,
                             "920e64a2-df17-11e7-80c1-9a214cf093ae",
                             "IKeypointsReIndexer",
                             "SolAR::api::features::IKeypointsReIndexer");

#endif // SOLAR_IKEYPOINTSREINDEXER_H
