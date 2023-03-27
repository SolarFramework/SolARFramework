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

#include "datastructure/Keypoint.h"
#include "xpcf/core/helpers.h"
#include <cstddef> //TO DO: remove with a complete implementation

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::Keypoint);

namespace SolAR {
namespace datastructure {

Keypoint::~Keypoint(){

}

Keypoint::Keypoint( unsigned int id,
                    float x,
                    float y,
					float r,
					float g,
					float b,
                    float size,
                    float angle,
                    float response,
                    int	octave,
                    int class_id ):m_id(id), Point2Df(x,y), m_rgb(r, g, b), m_size(size),m_angle(angle), m_response(response), m_octave(octave), m_class_id(class_id){


}
void Keypoint::init(unsigned int id,
                    float x,
                    float y,
					float r,
					float g,
					float b,
                    float size,
                    float angle,
                    float response,
                    int octave,
                    int class_id ){

    m_id = id;
    setX(x);
    setY(y);
	m_rgb = Vector3f(r, g, b);
    m_size=size;
    m_angle=angle;
    m_response=response;
    m_octave=octave;
    m_class_id=class_id;
}

template<typename Archive>
void Keypoint::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
	ar & boost::serialization::base_object<Point2Df>(*this);
	ar & boost::serialization::make_array(m_rgb.data(), 3);
	ar & m_id;
	ar & m_size;
	ar & m_angle;
	ar & m_response;
	ar & m_octave;
	ar & m_class_id;
}

IMPLEMENTSERIALIZE(Keypoint);

}
}
