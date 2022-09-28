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

#include "base/pipeline/AMappingPipeline.h"

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace base {
namespace pipeline {

AMappingPipeline::AMappingPipeline(std::map<std::string,std::string> componentInfosMap):xpcf::ConfigurableBase(componentInfosMap)
{
    declareInterface<SolAR::api::pipeline::IMappingPipeline>(this);
}

FrameworkReturnCode AMappingPipeline::mappingProcessRequest(const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                                            const std::vector<SolAR::datastructure::Transform3Df> & poses,
                                                            SolAR::api::pipeline::MappingStatus & status)
{
    datastructure::Transform3Df updatedTransform;
    return mappingProcessRequest(images, poses, datastructure::Transform3Df::Identity(), updatedTransform, status);
}

FrameworkReturnCode AMappingPipeline::mappingProcessRequest(const std::vector<SRef<SolAR::datastructure::Image>> & images,
                                                            const std::vector<SolAR::datastructure::Transform3Df> & poses,
                                                            SolAR::datastructure::Transform3Df & updatedTransform,
                                                            SolAR::api::pipeline::MappingStatus & status)
{
    return mappingProcessRequest(images, poses, datastructure::Transform3Df::Identity(), updatedTransform, status);
}



}
}
}  // end of namespace SolAR


