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

#include "api/map/IRectifyMap.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace map {

FrameworkReturnCode IRectifyMap::createMap(const SRef<SolAR::datastructure::Map>& map)
{
    return FrameworkReturnCode::_NOT_IMPLEMENTED;
}

FrameworkReturnCode IRectifyMap::createMap(const SRef<KeyframeCollection> keyframes, const SRef<CameraParametersCollection> cameraParameters)
{
    if (!cameraParameters) {
        LOG_ERROR("IRectifyMap::createMap - invalid camera parameter collection.");
        return FrameworkReturnCode::_ERROR_;
    }
    std::vector<SRef<CameraParameters>> listCameraParameters;
    if (cameraParameters->getAllCameraParameters(listCameraParameters) != FrameworkReturnCode::_SUCCESS) {
        LOG_ERROR("IRectifyMap::createMap - failed to get all camera parameters.");
        return FrameworkReturnCode::_ERROR_;
    }
    return createMap(keyframes, listCameraParameters);
}

FrameworkReturnCode IRectifyMap::createMap(const SRef<KeyframeCollection> keyframes, const std::vector<SRef<CameraParameters>>& cameraParameters)
{
    if (!keyframes) {
        LOG_ERROR("IRectifyMap::createMap - invalid keyframes collection.");
        return FrameworkReturnCode::_ERROR_;
    }
    std::vector<SRef<Keyframe>> listKeyframes;
    if (keyframes->getAllKeyframes(listKeyframes) != FrameworkReturnCode::_SUCCESS) {
        LOG_ERROR("IRectifyMap::createMap - failed to get all keyframes.");
        return FrameworkReturnCode::_ERROR_;
    }
    return createMap(listKeyframes, cameraParameters);
}

FrameworkReturnCode IRectifyMap::createMap(const std::vector<SRef<Keyframe>>& keyframes, const SRef<CameraParametersCollection> cameraParameters)
{
    if (!cameraParameters) {
        LOG_ERROR("IRectifyMap::createMap - invalid camera parameter collection.");
        return FrameworkReturnCode::_ERROR_;
    }
    std::vector<SRef<CameraParameters>> listCameraParameters;
    if (cameraParameters->getAllCameraParameters(listCameraParameters) != FrameworkReturnCode::_SUCCESS) {
        LOG_ERROR("IRectifyMap::createMap - failed to get all camera parameters.");
        return FrameworkReturnCode::_ERROR_;
    }
    return createMap(keyframes, listCameraParameters);
}

FrameworkReturnCode IRectifyMap::createMap(const std::vector<std::pair<SRef<Image>, uint32_t>>& imageCamIds, const SRef<CameraParametersCollection> cameraParameters)
{
    if (!cameraParameters) {
        LOG_ERROR("IRectifyMap::createMap - invalid camera parameter collection.");
        return FrameworkReturnCode::_ERROR_;
    }
    std::vector<SRef<CameraParameters>> listCameraParameters;
    if (cameraParameters->getAllCameraParameters(listCameraParameters) != FrameworkReturnCode::_SUCCESS) {
        LOG_ERROR("IRectifyMap::createMap - failed to get all camera parameters.");
        return FrameworkReturnCode::_ERROR_;
    }
    return createMap(imageCamIds, listCameraParameters);
}

} // end of namespace map
} // end of namespace api 
} // end of namespace SolAR
