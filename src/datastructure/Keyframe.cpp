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

int Keyframe::m_keyframeIdx = 0;

void Keyframe::addVisibleMapPoints(const std::map<unsigned int, SRef<CloudPoint>>& mapPoints)
{
    m_mapVisibility.insert(mapPoints.begin(), mapPoints.end());
}

/*
void Keyframe::addVisibleMapPoints(const std::vector<SRef<CloudPoint>>& mapPoints)
{
    m_mapPoints.insert(m_mapPoints.end(), mapPoints.begin(), mapPoints.end());
}
*/
std::map<unsigned int, SRef<CloudPoint>>& Keyframe::getVisibleMapPoints()
{
    return m_mapVisibility;
}

}
}
