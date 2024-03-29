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

#ifndef SOLAR_TIMER_H
#define SOLAR_TIMER_H

#include <chrono>

namespace SolAR {

class Timer {
public:
    Timer(){ m_clock = std::chrono::steady_clock::now(); }

    void restart() { m_clock = std::chrono::steady_clock::now(); }

    template <class T = std::chrono::milliseconds>
    auto elapsed()
    {
        return std::chrono::duration_cast<T>(std::chrono::steady_clock::now() - m_clock).count();
    }
private:
    std::chrono::steady_clock::time_point m_clock;
};

}  // end of namespace SolAR

#endif // SOLAR_TIMER_H
