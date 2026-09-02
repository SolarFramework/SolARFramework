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

#ifndef SOLAR_ZIPBUFFER_H
#define SOLAR_ZIPBUFFER_H

#include "core/Messages.h"
#include <string>
#include <vector>

namespace SolAR {

/**
 * @class ZipBuffer
 * @brief <B>Defines methods to zip/unzip data to/from a binary buffer </B>
 *
 */

class ZipBuffer {

public:

    /// @brief Class constructor
    ZipBuffer();

    /// @brief Class destructor
    ~ZipBuffer();

    /// @brief zip the content of the original path and store the binary result in the output buffer
    /// @param[in] originalPath path to data to zip
    /// @param[out] compressedZipBuffer output buffer containing the zip data
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the process succeeds
    /// * FrameworkReturnCode::_NOT_FOUND if data is not found in original path
    /// * else FrameworkReturnCode::_ERROR_
    FrameworkReturnCode zipToBuffer(const std::string & originalPath,
                                    std::vector<unsigned char> & compressedZipBuffer);

    /// @brief unzip the content of the input buffer and store the result in the destination path
    /// @param[in] compressedZipBuffer input buffer containing the zip data
    /// @param[out] destinationPath path for unzipped data
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the process succeeds
    /// * else FrameworkReturnCode::_ERROR_
    FrameworkReturnCode bufferToUnzip(const std::vector<unsigned char> & compressedZipBuffer,
                                      std::string & destinationPath);

private:

    /// @brief Delete the content of the working directory
    void cleanWorkingDirectory();

    std::string m_workingPath = "./working_dir"; // Working directory used to copy, zip or unzip data
};

}  // end of namespace SolAR

#endif // SOLAR_ZIPBUFFER_H
