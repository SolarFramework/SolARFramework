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

#ifndef SOLAR_ISBPATTERNREINDEXER_H
#define SOLAR_ISBPATTERNREINDEXER_H

#include "IComponentIntrospect.h"
#include "api/features/IDescriptorMatcher.h"
#include "core/Messages.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/DescriptorMatch.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace features {

/**
 * @class ISBPatternReIndexer
 * @brief gives both the 4 corners of a pattern in its reference coordinate system (pixels, cells, etc.) and the 4 corners in pixels of this pattern in the current image.
 */
class  ISBPatternReIndexer : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief ISBPatternReIndexer default constructor
    ISBPatternReIndexer() = default;

    /// @brief ISBPatternReIndexer default destructor
    virtual ~ISBPatternReIndexer() = default;

    /// @brief Set the squared binary pattern size corresponding to horizontal or vertical cells
    /// As this pattern is squared, it has the same number of vertical and horizontal cells (without marker borders)
    /// @param[in] patternSize The number of horizontal or vertical cells of the squared binary pattern (without marker borders).
    virtual void setParameters (const int sbPatternSize) = 0;

    /// @brief From a set of Squared Binary Pattern matches as well as the contours of the candidate patterns extracted from the current image, this method provides both the 4 corners of a pattern in its reference coordinate system (pixels, cells, etc.) and the 4 corners in pixels of this pattern in the current image.
    /// @param[in] candidateContours The set of candidate contours of the patterns extracted in the current image.
    /// @param[in] matches The set of matches describing which candidates contours defined in the first parameters correspond to the targetted squared binary pattern (here, only work with one squared binary pattern).
    /// @param[out] patternPoints The 4 corners of the pattern that has been recognized in the image. These corners are defined in a user-defined coordinate system (e.g.the image marker image coordinate system defined in pixels, or the pattern coordinate system defined in cells, etc.). Be sure to use the same coordinate system in the whole pipeline when you are defining 2D points referencing the pattern (For example in the first parameter of the method IImage2WorldMapper::setParameters).
    /// @param[out] imagePoints the 4 corners in the current image of the recognized pattern. These corners are defined in the image coordinate system (in pixels).
    /// @return FrameworkReturnCode::_SUCCESS_ if reindexing succeed, else FrameworkReturnCode::_ERROR.
    virtual FrameworkReturnCode reindex(const std::vector<SRef<Contour2Df>>& candidateContours, const std::vector<DescriptorMatch> & matches, std::vector<SRef<Point2Df>>& patternPoints, std::vector<SRef<Point2Df>>& imagePoints) = 0;

    XPCF_DECLARE_UUID("79c5b810-d557-11e7-9296-cec278b6b50a");

protected:
   int m_sbPatternSize;
};

}
}
}  // end of namespace Solar

#endif // SOLAR_ISBPATTERNREINDEXER_H
