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

#include "IComponentIntrospect.h"
#include "datastructure/Keypoint.h"
#include "api/features/IDescriptorMatcher.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/DescriptorMatch.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace features {

/**
 * @class IKeypointsReIndexer
 * @brief Reorganizes the keypoints detected from two images that match together in two vector of points where the nth point of the first vector matches with the nth point of the second vector.
 */
class  IKeypointsReIndexer : public virtual org::bcom::xpcf::IComponentIntrospect {
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
    virtual FrameworkReturnCode reindex(const std::vector<SRef<Keypoint>>& keypoints1, const std::vector<SRef<Keypoint>>& keypoints2, std::vector<DescriptorMatch>& matches, std::vector<SRef<Point2Df>>& matchedKeypoints1, std::vector<SRef<Point2Df>>& matchedKeypoints2) = 0;

    XPCF_DECLARE_UUID("920e64a2-df17-11e7-80c1-9a214cf093ae");

};

}
}
}  // end of namespace Solar

#endif // SOLAR_IKEYPOINTSREINDEXER_H
