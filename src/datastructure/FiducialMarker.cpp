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

#include "xpcf/core/helpers.h"

#include <boost/serialization/export.hpp>

namespace SolAR {
namespace datastructure {

// Construct a new FiducialMarker from a binary pattern and a size (width and height)
FiducialMarker::FiducialMarker(const std::string & url, const Sizef & size,
                               const SquaredBinaryPattern & binaryPattern) :
                                    Trackable(url), Trackable2D(url, size), m_pattern(binaryPattern) {
    LOG_DEBUG("FiducialMarker constructor: url = {}, width = {}, height = {}, pattern size = {}",
              url, size.width, size.height, binaryPattern.getSize());
}

// Class methods

// Returns the type (class name) of the trackable object
TrackableType FiducialMarker::getType() const {
    return FIDUCIAL_MARKER;
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
void FiducialMarker::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {

    ar.template register_type<FiducialMarker>();
    ar & boost::serialization::base_object<Trackable2D>(*this);

    ar & m_pattern;
}

IMPLEMENTSERIALIZE(FiducialMarker);

}
}

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::FiducialMarker)
BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::FiducialMarker)
