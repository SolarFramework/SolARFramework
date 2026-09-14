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

#ifndef SOLAR_MAPEXPORTIMPORTPIPELINE_H
#define SOLAR_MAPEXPORTIMPORTPIPELINE_H

#include "api/pipeline/IPipeline.h"

#include <xpcf/core/helpers.h>

namespace SolAR {
namespace api {
namespace pipeline {

/**
 * @class IMapExportImportPipeline
 * @brief <B>Defines a map export/import pipeline.</B>
 * <TT>UUID: 6fed31af-2b41-4a49-ba3c-1b382229b0f9</TT>
 *
 * This class provides the interface to define a map export/import pipeline.
 */

class XPCF_CLIENTUUID("59bed21a-caeb-4144-86b0-a006f2e4ff01") XPCF_SERVERUUID("a72a8498-eaf8-483a-9c6f-423faaefb047")
    XPCF_GRPC_CLIENT_RECV_SIZE("-1") XPCF_GRPC_CLIENT_SEND_SIZE("-1")
    IMapExportImportPipeline : virtual public IPipeline {
public:
    /// @brief IMapExportImportPipeline default constructor
    IMapExportImportPipeline() = default;

    /// @brief IMapExportImportPipeline default destructor
    virtual ~IMapExportImportPipeline() = default;

    /// @brief Export a map to the format managed by the service
    /// @param[in] mapUUID map to export
    /// @param[out] compressedZipExport the exported files of the map in a compressed buffer (ZIP format)
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the export succeeds
    /// * FrameworkReturnCode::_NOT_FOUND if mapUUID is not found on storage
    /// * FrameworkReturnCode::_MAP_NO_DATA if no data is available on storage for mapUUID
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode exportMap(const std::string & mapUUID, std::vector<unsigned char> & compressedZipExport) = 0;

    /// @brief Import a map from the format managed by the service
    /// @param[in] mapUUID map to import
    /// @param[in] compressedZipImport the map imported files in a compressed buffer (ZIP format)
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the import succeeds
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode importMap(const std::string & mapUUID, const std::vector<unsigned char> & compressedZipImport) = 0;

};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::pipeline::IMapExportImportPipeline,
                             "6fed31af-2b41-4a49-ba3c-1b382229b0f9",
                             "IMapExportImportPipeline",
                             "The interface to define a map export/import pipeline")

#endif // SOLAR_MAPEXPORTIMPORTPIPELINE_H
