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

#include "datastructure/Keyframe.h"

#include <cstddef> //TO DO: remove with a complete implementation

namespace SolAR {
namespace datastructure {

const uint32_t& Keyframe::getId() const
{
	return m_id;
}

void Keyframe::setId(const uint32_t& id_keyframe)
{
	m_id = id_keyframe;
}

template<typename Archive>
void Keyframe::serialize(Archive &ar, const unsigned int version) {
	ar & boost::serialization::base_object<Frame>(*this);
	ar & boost::serialization::base_object<PrimitiveInformation>(*this);
	ar & m_id;
}

IMPLEMENTSERIALIZE(Keyframe);

}
}
