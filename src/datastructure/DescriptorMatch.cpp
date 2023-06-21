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

#include "datastructure/DescriptorMatch.h"

#include "xpcf/core/helpers.h"

namespace SolAR {
namespace datastructure {

template <typename Archive>
void DescriptorMatch::serialize(Archive &ar, const unsigned int /* version */)
{
    ar & std::get<0>(m_match);
    ar & std::get<1>(m_match);
    ar & std::get<2>(m_match);
}

IMPLEMENTSERIALIZE(DescriptorMatch);


} // end of namespace datastructure
} // end of namespace SolAR
