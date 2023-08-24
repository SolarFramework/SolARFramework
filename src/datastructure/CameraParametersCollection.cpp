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

#include "datastructure/CameraParametersCollection.h"
#include <xpcf/core/helpers.h>
#include "core/Log.h"

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::CameraParametersCollection);

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

FrameworkReturnCode CameraParametersCollection::addCameraParameters(const SRef<CameraParameters> cameraParameters, bool defineCameraParametersId)
{
    uint32_t id;
    if (defineCameraParametersId==true)
    {
        id = m_id++;
        cameraParameters->id = id;
    }
    else
    {
        id = cameraParameters->id;
        if (m_id<=id)
            m_id = id+1;

    }
    m_cameraParameters[id] = cameraParameters;
    LOG_DEBUG("Add camera[{}] = {}", id, cameraParameters->id);
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode CameraParametersCollection::addCameraParameters(CameraParameters & cameraParameters, bool defineCameraParametersId)
{
    SRef<CameraParameters> cameraParameters_ptr = xpcf::utils::make_shared<CameraParameters>(cameraParameters);
    uint32_t id;
    if (defineCameraParametersId==true)
    {
        id = m_id++;
        cameraParameters.id = id;

    }
    else
    {
        id = cameraParameters.id;
        if (m_id<=id)
            m_id = id+1;

    }
    cameraParameters_ptr->id = id;
    m_cameraParameters[id] = cameraParameters_ptr;
    LOG_DEBUG("Add camera[{}] = {}", id, cameraParameters_ptr->id);
    return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode CameraParametersCollection::getCameraParameters(const uint32_t id, SRef<CameraParameters> & cameraParameters) const
{
    std::map< uint32_t, SRef<CameraParameters>>::const_iterator cameraParametersIt = m_cameraParameters.find(id);
    if (cameraParametersIt != m_cameraParameters.end()) {
        cameraParameters = cameraParametersIt->second;
		return FrameworkReturnCode::_SUCCESS;
	}
	else {
        LOG_DEBUG("Cannot find cameraParameters with id {} to get", id);
		return FrameworkReturnCode::_ERROR_;
	}
}

FrameworkReturnCode CameraParametersCollection::getCameraParameters(const uint32_t id, CameraParameters & cameraParameters) const
{
    std::map< uint32_t, SRef<CameraParameters>>::const_iterator cameraParametersIt = m_cameraParameters.find(id);
    if (cameraParametersIt != m_cameraParameters.end()) {
        cameraParameters = *(cameraParametersIt->second);
        return FrameworkReturnCode::_SUCCESS;
    }
    else {
        LOG_DEBUG("Cannot find cameraParameters with id {} to get", id);
        return FrameworkReturnCode::_ERROR_;
    }
}

FrameworkReturnCode CameraParametersCollection::getCameraParameters(const std::vector<uint32_t>& ids, std::vector<SRef<CameraParameters>>& cameraParameters) const
{
	for (auto &it : ids) {
        std::map< uint32_t, SRef<CameraParameters>>::const_iterator cameraParametersIt = m_cameraParameters.find(it);
        if (cameraParametersIt == m_cameraParameters.end()) {
            LOG_DEBUG("Cannot find cameraParameters with id {} to get", it);
			return FrameworkReturnCode::_ERROR_;
		}
        cameraParameters.push_back(cameraParametersIt->second);
	}
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode CameraParametersCollection::getAllCameraParameters(std::vector<SRef<CameraParameters>>& cameraParameters) const
{
    for (auto cameraParametersIt = m_cameraParameters.begin(); cameraParametersIt != m_cameraParameters.end(); cameraParametersIt++)
        cameraParameters.push_back(cameraParametersIt->second);
    return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode CameraParametersCollection::suppressCameraParameters(const uint32_t id)
{
    std::map< uint32_t, SRef<CameraParameters>>::iterator cameraParametersIt = m_cameraParameters.find(id);
    if (cameraParametersIt != m_cameraParameters.end()) {
        m_cameraParameters.erase(cameraParametersIt);
		return FrameworkReturnCode::_SUCCESS;
	}
	else {
        LOG_DEBUG("Cannot find cameraParameters with id {} to suppress", id);
		return FrameworkReturnCode::_ERROR_;
	}
}

bool CameraParametersCollection::isExistCameraParameters(const uint32_t id) const
{
    if (m_cameraParameters.find(id) != m_cameraParameters.end())
		return true;
	else
		return false;
}

int CameraParametersCollection::getNbCameraParameters() const
{
    return static_cast<int>(m_cameraParameters.size());
}

template <typename Archive>
void CameraParametersCollection::serialize(Archive &ar, const unsigned int /* version */)
{
	ar & m_id;
    ar & m_cameraParameters;
}

IMPLEMENTSERIALIZE(CameraParametersCollection);

} // end of namespace datastructure
} // end of namespace SolAR
