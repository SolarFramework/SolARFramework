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

#ifndef SOLAR_MAPPINGPIPELINE_H
#define SOLAR_MAPPINGPIPELINE_H


#include "api/pipeline/IPipeline.h"
#include "datastructure/CameraDefinitions.h"
#include "datastructure/Image.h"
#include "datastructure/CloudPoint.h"
#include "datastructure/Keypoint.h"
#include "datastructure/Trackable.h"
#include "xpcf/core/helpers.h"


namespace SolAR {
namespace api {
namespace pipeline {

/**
 * @class IMappingPipeline
 * @brief <B>Defines a mapping pipeline.</B>
 * <TT>UUID: 2dc3cd33-5a11-4748-94a3-e7ab40462097</TT>
 *
 * This class provides the interface to define a mapping processing pipeline.
 */

class XPCF_CLIENTUUID("110a089c-0bb1-488e-b24b-c1b96bc9df3b") XPCF_SERVERUUID("aced265d-832c-44e3-9356-dab531fa153a") IMappingPipeline :
    virtual public IPipeline {
public:
    /// @brief IMappingPipeline default constructor
    IMappingPipeline() = default;

    /// @brief IMappingPipeline default destructor
    virtual ~IMappingPipeline() = default;

    /// @brief Set the camera parameters
    /// @param[in] cameraParams: the camera parameters (its resolution and its focal)
    /// @return FrameworkReturnCode::_SUCCESS if the camera parameters are correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setCameraParameters(const datastructure::CameraParameters & cameraParams) = 0;

    /// @brief Set the object to track during mapping
    /// @param[in] trackableObject: the trackable object
    /// @return FrameworkReturnCode::_SUCCESS if the trackable object is correctly set, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode setObjectToTrack(const SRef<datastructure::Trackable> trackableObject) = 0;

    /// @brief Request to the mapping pipeline to process a new image/pose
    /// Retrieve the new image (and pose) to process, in the current pipeline context
    /// (camera configuration, fiducial marker, point cloud, key frames, key points)
    /// @param[in] image: the input image to process
    /// @param[in] pose: the input pose to process
    /// @return FrameworkReturnCode::_SUCCESS if the data are ready to be processed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode mappingProcessRequest(const SRef<datastructure::Image> image,
                                                      const datastructure::Transform3Df & pose) = 0;

    /// @brief Provide the current data from the mapping pipeline context for visualization
    /// (resulting from all mapping processing since the start of the pipeline)
    /// @param[out] outputPointClouds: pipeline current point clouds
    /// @param[out] keyframePoses: pipeline current keyframe poses
    /// @return FrameworkReturnCode::_SUCCESS if data are available, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getDataForVisualization(std::vector<SRef<datastructure::CloudPoint>> & outputPointClouds,
                                                        std::vector<datastructure::Transform3Df> & keyframePoses) const = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IMappingPipeline,
                             "2dc3cd33-5a11-4748-94a3-e7ab40462097",
                             "IMappingPipeline",
                             "The interface to define a mapping processing pipeline")

#endif // SOLAR_MAPPINGPIPELINE_H
