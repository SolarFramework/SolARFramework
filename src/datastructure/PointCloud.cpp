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

#include "datastructure/PointCloud.h"

#include "xpcf/core/helpers.h"

namespace SolAR {
namespace datastructure {

const std::vector<CloudPoint>& PointCloud::getConstPointCloud() const
{
    return m_points;
}

std::vector<CloudPoint>& PointCloud::getPointCloud()
{
    return m_points;
}

template <typename Archive>
void PointCloud::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version)
{
    ar & m_points;
}

IMPLEMENTSERIALIZE(PointCloud);


} // end of namespace datastructure
} // end of namespace SolAR
