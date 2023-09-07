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

#include "api/reloc/IKeyframeRetriever.h"

namespace SolAR {
namespace api {
namespace reloc {

FrameworkReturnCode IKeyframeRetriever::retrieve(const SRef<SolAR::datastructure::Frame> frame, std::vector<uint32_t> & retKeyframeId) 
{
    std::vector<std::pair<uint32_t, double>> retKeyframeIdScore;
    if (retrieve(frame, retKeyframeIdScore) != FrameworkReturnCode::_SUCCESS)
        return FrameworkReturnCode::_ERROR_;
    retKeyframeId.clear();
    std::for_each(retKeyframeIdScore.cbegin(), retKeyframeIdScore.cend(), [&retKeyframeId](const auto& e) {retKeyframeId.push_back(e.first);});
    return FrameworkReturnCode::_SUCCESS;
}

} // end of namespace reloc 
} // end of namespace api 
} // end of namespace SolAR