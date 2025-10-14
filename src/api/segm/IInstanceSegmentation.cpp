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

#include "api/segm/IInstanceSegmentation.h"
#include "core/Log.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace segm {

FrameworkReturnCode IInstanceSegmentation::segment(const std::vector<SRef<Image>>& images,
                    std::vector<std::vector<Rectanglei>>& boxes,
                    std::vector<std::vector<SRef<Image>>>& masks,
                    std::vector<std::vector<uint32_t>>& classIds,
                    std::vector<std::vector<float>>& scores)
{
    boxes.resize(images.size());
    masks.resize(images.size());
    classIds.resize(images.size());
    scores.resize(images.size());
    for (size_t i = 0; i < images.size(); ++i) {
        if (segment(images[i], boxes[i], masks[i], classIds[i], scores[i]) != FrameworkReturnCode::_SUCCESS) {
            boxes.clear();
            masks.clear();
            classIds.clear();
            scores.clear();
            LOG_ERROR("IInstanceSegmentation::segment - instance segmentation encountered errors.");
            return FrameworkReturnCode::_ERROR_;
        }
    }
    return FrameworkReturnCode::_SUCCESS;
}

} // segm
} // api
} // SolAR
