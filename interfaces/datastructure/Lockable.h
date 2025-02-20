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

#ifndef SOLAR_LOCKABLE_H
#define SOLAR_LOCKABLE_H

#include <mutex>
#include <core/SolARFrameworkDefinitions.h>

// Definition of Lockable Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
* @class Lockable
*/
class  SOLARFRAMEWORK_API Lockable {

   public:
		///
        /// @brief LockableCollection constructor.
        ///
        Lockable() = default;
        ~Lockable() = default;

		///
		/// @brief This method returns the point cloud
        /// @return the lock preventing concurrent access to the PointCloud set
		///
        [[nodiscard]]
        std::unique_lock<std::mutex> acquireLock() {
            return std::unique_lock<std::mutex>(m_mutex);
        }

        void lock() { m_mutex.lock(); }
        void unlock() { m_mutex.unlock(); }
        bool tryLock() { return m_mutex.try_lock(); }

    private:
        std::mutex m_mutex;
};


}
}  // end of namespace SolAR

#endif // SOLAR_LOCKABLE_H
