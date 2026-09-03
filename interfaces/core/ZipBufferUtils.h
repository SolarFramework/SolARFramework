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

#ifndef SOLAR_ZIPBUFFERUTILS_H
#define SOLAR_ZIPBUFFERUTILS_H

#include "core/Messages.h"
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

namespace SolAR {

/**
 * @class ZipBufferUtils
 * @brief <B>Defines methods to zip/unzip data to/from a binary buffer </B>
 *
 */

class ZipBufferUtils {

public:

    /**
     * @class ScopedWorkingDir
     * @brief <B>Create a temporary working directory</B>
     *
     */
    class ScopedWorkingDir {
    public:
        ScopedWorkingDir() { m_workingPath = fs::temp_directory_path(); m_workingPath += "/solar"; }
        ~ScopedWorkingDir() { fs::remove_all(m_workingPath); }
        fs::path getPath() { return m_workingPath; }
        std::string getStringPath() { return m_workingPath.string(); }
    private:
        fs::path m_workingPath; // Temporary working directory used to copy, zip or unzip data
    };

    /// @brief zip the content of the original path and store the binary result in the output buffer
    /// @param[in] originalPath path to data to zip
    /// @param[out] compressedZipBuffer output buffer containing the zip data
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the process succeeds
    /// * else FrameworkReturnCode::_ERROR_
    static FrameworkReturnCode compress(const std::string & originalPath,
                                        std::vector<unsigned char> & compressedZipBuffer);

    /// @brief unzip the content of the input buffer and store the result in the destination path
    /// @param[in] compressedZipBuffer input buffer containing the zip data
    /// @param[out] destinationPath path for unzipped data
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the process succeeds
    /// * else FrameworkReturnCode::_ERROR_
    static FrameworkReturnCode extract(const std::vector<unsigned char> & compressedZipBuffer,
                                       std::string & destinationPath);

};

}  // end of namespace SolAR

#endif // SOLAR_ZIPBUFFERUTILS_H
