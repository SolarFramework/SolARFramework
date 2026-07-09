/**
 * @copyright Copyright (c) 2026 B-com http://www.b-com.com/
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

#include "api/pipeline/IMapProcessingPipeline.h"

namespace fs = std::filesystem;

namespace SolAR {
using namespace datastructure;
namespace api {
namespace pipeline {

FrameworkReturnCode IMapProcessingPipeline::loadMapFromFile(SRef<SolAR::datastructure::Map>& mapDatastructure) const
{
    if (m_processedMapUUID.empty()) {
        LOG_ERROR("IMapProcessingPipeline::loadMapFromFile - processed map UUID not defined.");
        return FrameworkReturnCode::_ERROR_;
    }
    if (!m_mapManager) {
        LOG_ERROR("IMapProcessingPipeline::loadMapFromFile - invalid shared pointer to Map Manager.");
        return FrameworkReturnCode::_ERROR_;
    }

    // Set file path for map datastructure using map UUID
    std::string map_folder = m_mapDirectory + "/" + m_processedMapUUID;
    LOG_DEBUG("Path for map storage: {}", map_folder);

    std::unique_lock<std::mutex> lock(m_mutexMapManager);

    try {
        m_mapManager->bindTo<xpcf::IConfigurable>()->getProperty("directory")->setStringValue(map_folder.c_str());

        // Try to load map from files (if exists)
        if (m_mapManager->loadFromFile() != FrameworkReturnCode::_SUCCESS) {
            LOG_ERROR("Unable to load the map datstructure from file");
            return FrameworkReturnCode::_NOT_FOUND;
        }

        m_mapManager->getMap(mapDatastructure);
        if (mapDatastructure == nullptr) {
            LOG_ERROR("No datastructure for map: {}", m_processedMapUUID);
            return FrameworkReturnCode::_MAP_NO_DATA;
        }
    }
    catch (const xpcf::Exception & e) {
        LOG_ERROR("The following exception has been caught {}", e.what());
        return FrameworkReturnCode::_ERROR_;
    }

    return FrameworkReturnCode::_SUCCESS;

}

FrameworkReturnCode IMapProcessingPipeline::saveMapToFile(SRef<SolAR::datastructure::Map>& mapDatastructure,
                                                          SolAR::datastructure::MapProcessingApplied mapProcessingApplied,
                                                          std::vector<SolAR::datastructure::MapProcessingStep> mapProcessingHistory) const
{
    if (m_processedMapUUID.empty()) {
        LOG_ERROR("IMapProcessingPipeline::saveMapToFile - processed map UUID not defined.");
        return FrameworkReturnCode::_ERROR_;
    }
    if (m_resultingMapUUID.empty()) {
        LOG_ERROR("IMapProcessingPipeline::saveMapToFile - resulting map UUID not defined.");
        return FrameworkReturnCode::_ERROR_;
    }
    if (!m_mapManager) {
        LOG_ERROR("IMapProcessingPipeline::saveMapToFile - invalid shared pointer to Map Manager.");
        return FrameworkReturnCode::_ERROR_;
    }

    // Try to create a new directory for this map datastructure
    fs::path p(m_mapDirectory + "/" + m_resultingMapUUID);
    try {
        if (!fs::create_directory(p)) {
            LOG_ERROR("Error while creating the datastructure directory for new map: {}", m_resultingMapUUID);
            return FrameworkReturnCode::_ERROR_;
        }
    }
    catch (const fs::filesystem_error& e) {
        LOG_ERROR("Exception while creating the datastructure directory: {}", e.what());
        return FrameworkReturnCode::_ERROR_;
    }

    // Reset the map history
    mapDatastructure->resetMapProcessingHistory();
    for (auto const& processingStep: mapProcessingHistory) {
        mapDatastructure->addMapProcessingStep(processingStep);
        LOG_DEBUG("Add a processing step to map: {} / {} / {} / {}",
                  toString(processingStep.getProcessingApplied()), processingStep.getSourceMapUUID(), processingStep.getTargetMapUUID(), processingStep.getDateTime());
    }
    // Add the new processing step
    MapProcessingStep newProcessingStep{mapProcessingApplied, m_processedMapUUID, m_resultingMapUUID};
    mapDatastructure->addMapProcessingStep(newProcessingStep);
    LOG_DEBUG("Add a new processing step to map: {} / {} / {} / {}",
              toString(newProcessingStep.getProcessingApplied()), newProcessingStep.getSourceMapUUID(), newProcessingStep.getTargetMapUUID(), newProcessingStep.getDateTime())

    // Set file path for map datastructure using map UUID
    std::string map_folder = m_mapDirectory + "/" + m_resultingMapUUID;
    LOG_DEBUG("Path for map storage: {}", map_folder);

    std::unique_lock<std::mutex> lock(m_mutexMapManager);

    m_mapManager->bindTo<xpcf::IConfigurable>()->getProperty("directory")->setStringValue(map_folder.c_str());

    // Set the datastructure on MapManager instance
    m_mapManager->setMap(mapDatastructure);

    // Try to save the map on file system
    if (m_mapManager->saveToFile() == FrameworkReturnCode::_ERROR_) {
        LOG_ERROR("Error trying to save datastructure for map: {}", m_resultingMapUUID);
        return FrameworkReturnCode::_ERROR_;
    }

    return FrameworkReturnCode::_SUCCESS;

}

} // end of namespace pipeline
} // end of namespace api
} // end of namespace SolAR
