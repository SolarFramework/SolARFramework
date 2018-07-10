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

#include "datastructure/CloudPoint.h"
#include <cstddef> //TO DO: remove with a complete implementation

namespace SolAR {
    namespace datastructure {

    CloudPoint::~CloudPoint(){

    }

    CloudPoint::CloudPoint( double x,
                            double y,
                            double z,
                            float r,
                            float g,
                            float b,
                            double reproj_error,
                            std::vector<int>&visibility): m_x(x),m_y(y), m_z(z),m_r(r),m_g(g),m_b(b), m_reproj_error(reproj_error),
                                                          m_visibility(visibility){
    }
  }
}
