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

#ifndef SOLAR_BINARYPATTERN_H
#define SOLAR_BINARYPATTERN_H

#include "core/Messages.h"
#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/MathDefinitions.h"

namespace SolAR {
namespace datastructure {

typedef Maths::Matrix<bool,Maths::Dynamic,Maths::Dynamic> SquaredBinaryPatternMatrix;

/**
* @class SquaredBinaryPattern
* @brief <B>A SquaredBinaryPattern defined with a binary regular grid.</B>
*
*/
class SOLARFRAMEWORK_API SquaredBinaryPattern {

public:
    /// \brief constructs a default SquaredBinaryPattern
    SquaredBinaryPattern() = default;

    /// \brief constructs a SquaredBinaryPattern from a given SquaredBinaryPatternMatrix
    SquaredBinaryPattern (SquaredBinaryPatternMatrix pattern): m_patternMatrix(pattern){};

    /// \brief defines the destructor
    ~SquaredBinaryPattern() = default;

    /// \brief returns the SquaredBinaryPatternMatrix to detect.
    /// \returns the SquaredBinaryPatternMatrix to detect.
    const SquaredBinaryPatternMatrix & getPatternMatrix(void) const;

    /// \brief defines the new pattern matrix to consider
    ///
    FrameworkReturnCode setPatternMatrix (const SquaredBinaryPatternMatrix& pattern);

    /// \brief returns the size of the squared fiducial pattern to detect
    /// \returns the size of the squared fiducial pattern to detect. If the marker is a square of size 7x7, we return 7.
    inline int getSize () const { return m_size; }

private :
    SquaredBinaryPatternMatrix m_patternMatrix;
    int m_size;
};

}
}
#endif // SOLAR_BINARYPATTERN_H
