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

#include "datastructure/Mesh.h"

#include "xpcf/core/helpers.h"

#include <cstddef> //TO DO: remove with a complete implementation

namespace SolAR {
namespace datastructure {

Mesh::~Mesh(){

}

Mesh::Mesh(const std::vector<Point3Df> points,
           const std::vector<Vector3ui> indexedFaceSets,
           const std::vector<Vector3f> normals,
           const std::vector<Vector3f> colors,
           const std::vector<Vector2f> texCoordinates):
           m_points(points), m_indexedFaceSets(indexedFaceSets), m_normals(normals), m_colors(colors), m_texCoordinates(texCoordinates)
{

}


template<typename Archive>
void Mesh::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
    ar & m_points;
    ar & m_indexedFaceSets;
    ar & m_normals;
    ar & m_colors;
    ar & m_texCoordinates;
}

IMPLEMENTSERIALIZE(Mesh);

}
}
