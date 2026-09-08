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

#ifndef SOLAR_SCOPEDTEMPDIR_H
#define SOLAR_SCOPEDTEMPDIR_H

#include <string>
#include <filesystem>

namespace SolAR {
namespace util {

/**
     * @class ScopedTempDir
     * @brief <B>Create a temporary directory</B>
     *
     */
class ScopedTempDir {

public:

    ScopedTempDir();

    ~ScopedTempDir();

    // Delete copy operations to prevent double deletion
    ScopedTempDir(const ScopedTempDir&) = delete;
    ScopedTempDir& operator=(const ScopedTempDir&) = delete;
    ScopedTempDir(ScopedTempDir&&) = delete;
    ScopedTempDir& operator=(ScopedTempDir&&) = delete;

    const std::filesystem::path& getPath() const;
    const std::string getStringPath() const;

private:

    std::filesystem::path m_tempPath; // Temporary working directory used to copy, zip or unzip data

};

}  // end of namespace util
}  // end of namespace SolAR

#endif // SOLAR_SCOPEDTEMPDIR_H
