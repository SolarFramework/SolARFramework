/**
 * @copyright Copyright (c) 2020 B-com http://www.b-com.com/
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

#include "datastructure/FiducialMarker.h"

namespace SolAR {
namespace datastructure {

// Construct a new FiducialMarker from a binary pattern and a size (width and height)
FiducialMarker::FiducialMarker(SquaredBinaryPattern & binaryPattern, Sizef & size) {
    m_pattern = binaryPattern;
    m_size = size;
}

// Class methods

// Returns the type (class name) of the trackable object
std::string FiducialMarker::getTrackableType() const {
    return "FiducialMarker";
}

// Sets the binary pattern of the fiducial marker
void FiducialMarker::setPattern(const SquaredBinaryPattern & binaryPattern) {
    m_pattern = binaryPattern;
}

// Returns the binary pattern of the fiducial marker
SquaredBinaryPattern FiducialMarker::getPattern() const {
    return m_pattern;
}

template<typename Archive>
void FiducialMarker::serialize(Archive &ar, const unsigned int version) {

    SquaredBinaryPatternMatrix matrix = m_pattern.getPatternMatrix();

    for (unsigned int row = 0; row < matrix.rows(); row++) {
        for (unsigned int col = 0; col < matrix.cols(); col++) {
        ar & matrix(row, col);
      }
    }
}

IMPLEMENTSERIALIZE(FiducialMarker);

}
}
