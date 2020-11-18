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

#include "datastructure/Trackable2D.h"

#include "core/Log.h"

namespace SolAR {
namespace datastructure {

// Constructors

Trackable2D::Trackable2D(const std::string & url, const Sizef & size) : Trackable(url), m_size(size) {
    LOG_DEBUG("Trackable2D constructor: url = {}, width = {}, height = {}",
              url, size.width, size.height);
}


Trackable2D::Trackable2D(const std::string & url,
                         const float & width, const float & height) : Trackable(url) {
    LOG_DEBUG("Trackable2D constructor: url = {}, width = {}, height = {}", url, width, height);

    m_size.width = width;
    m_size.height = height;
}

// Class methods

Sizef Trackable2D::getSize() const {
    return m_size;
}

float Trackable2D::getWidth() const {
    return m_size.width;
}

float Trackable2D::getHeight() const {
    return m_size.height;
}

void Trackable2D::setSize(const Sizef & size) {
    if ((size.width > 0) && (size.height > 0))
        m_size = size;
}

void Trackable2D::setWidth(const float & width) {
    if (width > 0)
        m_size.width = width;
}

void Trackable2D::setHeight(const float &height) {
    if (height > 0)
        m_size.height = height;
}

template<typename Archive>
void Trackable2D::serialize(Archive &ar, const unsigned int version) {
    ar & m_size.width;
    ar & m_size.height;
}

IMPLEMENTSERIALIZE(Trackable2D);

}
}
