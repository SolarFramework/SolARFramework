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

#include "api/segm/IPanopticSegmentation.h"
#include "core/Log.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace segm {

FrameworkReturnCode IPanopticSegmentation::segment(const std::vector<SRef<const Image>>& images,
                    std::vector<SRef<Image>>& labelMaps,
                    std::vector<std::vector<Rectanglei>>& boxes,
                    std::vector<std::vector<std::pair<uint32_t, uint32_t>>>& classObjectIds,
                    std::vector<std::vector<float>>& scores)
{
    labelMaps.resize(images.size());
    boxes.resize(images.size());
    classObjectIds.resize(images.size());
    scores.resize(images.size());
    for (size_t i = 0; i < images.size(); ++i) {
        if (segment(images[i], labelMaps[i], boxes[i], classObjectIds[i], scores[i]) != FrameworkReturnCode::_SUCCESS) {
            labelMaps.clear();
            boxes.clear();
            classObjectIds.clear();
            scores.clear();
            LOG_ERROR("IPanopticSegmentation::segment - panoptic segmentation encountered errors.");
            return FrameworkReturnCode::_ERROR_;
        }
    }
    return FrameworkReturnCode::_SUCCESS;
}

} // segm
} // api
} // SolAR
