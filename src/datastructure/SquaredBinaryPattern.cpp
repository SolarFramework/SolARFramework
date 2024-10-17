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

#include "datastructure/SquaredBinaryPattern.h"
#include "core/Log.h"
#include "xpcf/core/helpers.h"
#include <iostream>

namespace SolAR {
namespace datastructure {

SquaredBinaryPattern::SquaredBinaryPattern(const SquaredBinaryPatternMatrix & pattern) : m_size {0}
{
    if (setPatternMatrix(pattern) != FrameworkReturnCode::_SUCCESS) {
        // should throw ??
    }
}

const SquaredBinaryPatternMatrix & SquaredBinaryPattern::getPatternMatrix(void) const
{
    return m_patternMatrix;
};

FrameworkReturnCode SquaredBinaryPattern::setPatternMatrix (const SquaredBinaryPatternMatrix & pattern)
{
    if (pattern.rows() != pattern.cols())
    {
        LOG_ERROR("SquaredBinaryPattern::setPatternMatrix: Try to set a pattern that is not squared. Number of rows and columns must be equals.")
        return FrameworkReturnCode::_ERROR_;
    }
    m_patternMatrix = pattern;
    m_size = pattern.rows();
    return FrameworkReturnCode::_SUCCESS;
};

 SquaredBinaryPattern SquaredBinaryPattern::fromString(const std::string& str, int size) {
    assert(str.length() == size * size);

    SquaredBinaryPatternMatrix matrix(size, size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix(i, j) = str[i * size + j] == '1';
        }
    }

    return SquaredBinaryPattern(matrix);
}
template <typename Archive>
void SquaredBinaryPattern::serialize(Archive &ar, const unsigned int /* version */)
{
    ar & m_size;
    ar & m_patternMatrix;
}

IMPLEMENTSERIALIZE(SquaredBinaryPattern);

}//end namespace datastructure
}//end namespace SolAR
