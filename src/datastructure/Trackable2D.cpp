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

#include <xpcf/core/helpers.h>

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

// destructor
Trackable2D::~Trackable2D() = default;

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

FrameworkReturnCode Trackable2D::getWorldCorners(std::vector<Point3Df> & worldCorners) const {
    worldCorners.clear();
    std::vector<Point3Df> local3DPts;
    local3DPts.push_back(Point3Df(-m_size.width/2.0f, -m_size.height/2.0f, 0.0f));
    local3DPts.push_back(Point3Df(m_size.width/2.0f, -m_size.height/2.0f, 0.0f));
    local3DPts.push_back(Point3Df(m_size.width/2.0f, m_size.height/2.0f, 0.0f));
    local3DPts.push_back(Point3Df(-m_size.width/2.0f, m_size.height/2.0f, 0.0f));
    for (const auto & pt3D : local3DPts){
        Vector3f inVec3f(pt3D.getX(),pt3D.getY(), pt3D.getZ());
        Vector3f outVec3f = m_transform3D * inVec3f;
        worldCorners.push_back(Point3Df(outVec3f[0], outVec3f[1], outVec3f[2]));
    }

    return FrameworkReturnCode::_SUCCESS;
}

template<typename Archive>
void Trackable2D::serialize(Archive &ar, const unsigned int /* version */) {

    ar & boost::serialization::base_object<Trackable>(*this);

    ar & m_size.width;
    ar & m_size.height;
}

IMPLEMENTSERIALIZE(Trackable2D);

}
}
