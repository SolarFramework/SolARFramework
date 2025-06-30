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

#include "datastructure/Object2D.h"

namespace SolAR {
namespace datastructure {

void Object2D::setInstanceID(const uint32_t& id)
{
    m_instanceID = id;
}

void Object2D::setBoundingBox(const float& x, const float& y, const float& w, const float& h)
{
    m_bbox = BBox2Df(x, y, w, h);
}

void Object2D::setSegmentation(const Contour2Df& contour)
{
    m_contour = contour;
}

const uint32_t& Object2D::getInstanceID() const
{
    return m_instanceID;
}

const BBox2Df& Object2D::getBoundingBox() const
{
    return m_bbox;
}

const Contour2Df& Object2D::getSegmentation() const
{
    return m_contour;
}

template<typename Archive>
void Object2D::serialize(Archive &ar, const unsigned int /* version */) 
{
    ar & m_instanceID;
    ar & m_bbox;
    ar & m_contour;
}

IMPLEMENTSERIALIZE(Object2D);

} // datastructure
} // SolAR
