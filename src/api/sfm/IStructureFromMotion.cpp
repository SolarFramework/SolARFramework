/**
 * @copyright Copyright (c) 2024 B-com http://www.b-com.com/
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

#include "api/sfm/IStructureFromMotion.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace sfm {

FrameworkReturnCode IStructureFromMotion::createMap(const SRef<KeyframeCollection> keyframes, const SRef<CameraParametersCollection> cameraParameters, SRef<Map> map)
{
    if (!cameraParameters) {
        LOG_ERROR("IStructureFromMotion::createMap - invalid camera parameter collection.");
        return FrameworkReturnCode::_ERROR_;
    }
    std::vector<SRef<CameraParameters>> listCameraParameters;
    if (cameraParameters->getAllCameraParameters(listCameraParameters) != FrameworkReturnCode::_SUCCESS) {
        LOG_ERROR("IStructureFromMotion::createMap - failed to get all camera parameters.");
        return FrameworkReturnCode::_ERROR_;
    }
    return createMap(keyframes, listCameraParameters, map);
}

FrameworkReturnCode IStructureFromMotion::createMap(const SRef<KeyframeCollection> keyframes, const std::vector<SRef<CameraParameters>>& cameraParameters, SRef<Map> map)
{
    if (!keyframes) {
        LOG_ERROR("IStructureFromMotion::createMap - invalid keyframes collection.");
        return FrameworkReturnCode::_ERROR_;
    }
    std::vector<SRef<Keyframe>> listKeyframes;
    if (keyframes->getAllKeyframes(listKeyframes) != FrameworkReturnCode::_SUCCESS) {
        LOG_ERROR("IStructureFromMotion::createMap - failed to get all keyframes.");
        return FrameworkReturnCode::_ERROR_;
    }
    return createMap(listKeyframes, cameraParameters, map);
}

FrameworkReturnCode IStructureFromMotion::createMap(const std::vector<SRef<Keyframe>>& keyframes, const SRef<CameraParametersCollection> cameraParameters, SRef<Map> map)
{
    if (!cameraParameters) {
        LOG_ERROR("IStructureFromMotion::createMap - invalid camera parameter collection.");
        return FrameworkReturnCode::_ERROR_;
    }
    std::vector<SRef<CameraParameters>> listCameraParameters;
    if (cameraParameters->getAllCameraParameters(listCameraParameters) != FrameworkReturnCode::_SUCCESS) {
        LOG_ERROR("IStructureFromMotion::createMap - failed to get all camera parameters.");
        return FrameworkReturnCode::_ERROR_;
    }
    return createMap(keyframes, listCameraParameters, map);
}

FrameworkReturnCode IStructureFromMotion::createMap(const std::vector<std::pair<SRef<Image>, uint32_t>>& imageCamIds, const SRef<CameraParametersCollection> cameraParameters, SRef<Map> map)
{
    if (!cameraParameters) {
        LOG_ERROR("IStructureFromMotion::createMap - invalid camera parameter collection.");
        return FrameworkReturnCode::_ERROR_;
    }
    std::vector<SRef<CameraParameters>> listCameraParameters;
    if (cameraParameters->getAllCameraParameters(listCameraParameters) != FrameworkReturnCode::_SUCCESS) {
        LOG_ERROR("IStructureFromMotion::createMap - failed to get all camera parameters.");
        return FrameworkReturnCode::_ERROR_;
    }
    return createMap(imageCamIds, listCameraParameters, map);
}

} // end of namespace reloc 
} // end of namespace api 
} // end of namespace SolAR
