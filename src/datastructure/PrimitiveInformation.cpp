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

#include <datastructure/PrimitiveInformation.h>


namespace SolAR {
namespace datastructure {

template<>	void PrimitiveInformation::serialize(InputArchive &ar, const unsigned int version)
{
    ar & m_confidence;
    ar & m_usedTimes;
    char * ptr = reinterpret_cast<char *>(&m_lastUpdateTime);
    for (int i = 0; i < sizeof(m_lastUpdateTime); ++i)
        ar & ptr[i];
    ar & m_semanticId;
}

template<>	void PrimitiveInformation::serialize(OutputArchive &ar, const unsigned int version)
{
    ar & m_confidence;
    ar & m_usedTimes;
    char * ptr = reinterpret_cast<char *>(&m_lastUpdateTime);
    for (int i = 0; i < sizeof(m_lastUpdateTime); ++i)
        ar & ptr[i];
    ar & m_semanticId;
}
}

}
