/**
 * @copyright Copyright (c) 2025 B-com http://www.b-com.com/
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

#include "datastructure/Object2DCollection.h"
#include "core/Log.h"

namespace SolAR {
namespace datastructure {

FrameworkReturnCode Object2DCollection::addObject2D(const SRef<Object2D>& obj)
{
    if (!obj) {
        LOG_ERROR("Object2DCollection::addObject2D - Object2D is invalid.");
        return FrameworkReturnCode::_ERROR_;
    }
    m_objects[obj->getInstanceID()] = obj;
    return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode Object2DCollection::removeObject2D(const uint32_t& id)
{
    if (m_objects.find(id) == m_objects.end()) {
        LOG_WARNING("Object2DCollection::addObject2D - Object2D {} does not exist.", id);
    }
    else {
        m_objects.erase(id);
    }
    return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode Object2DCollection::getObject2D(const uint32_t& id, SRef<Object2D>& obj)
{
    if (m_objects.find(id) == m_objects.end()) {
        LOG_WARNING("Object2DCollection::addObject2D - Object2D {} does not exist.", id);
        return FrameworkReturnCode::_ERROR_;
    }
    obj = m_objects.at(id);
    return FrameworkReturnCode::_SUCCESS;
}

template<typename Archive>
void Object2DCollection::serialize(Archive &ar, const unsigned int /* version */) 
{
    ar & m_objects;
}

IMPLEMENTSERIALIZE(Object2DCollection);

}
}