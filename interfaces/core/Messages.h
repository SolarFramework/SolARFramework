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

#ifndef SOLAR_MESSAGES_H
#define SOLAR_MESSAGES_H

namespace SolAR {

enum class FrameworkReturnCode:long{

    /** means stop the process */
    _STOP = 1,
    /** Successfull operation */
    _SUCCESS = 0,

    // error codes
    /** unknown error, better stop!! */
    _ERROR_ = -1,

    // Not implemented interface
    _NOT_IMPLEMENTED = -2,

    // for IImage
    /** Cannot load Image */
    _ERROR_LOAD_IMAGE = -10,
    /** Cannot acces Image */
    _ERROR_ACCESS_IMAGE = -11,

    // for services
    /** Service is busy */
    _BUSY = -20,
    /** No service registered (Service Manager) */
    _NO_SERVICE_REGISTERED = -21,
    /** No service available (Service Manager) */
    _NO_SERVICE_AVAILABLE = -22,
    /** Service not locked by a client (Service Manager) */
    _NO_SERVICE_LOCKED = -23
};

}  // end of namespace SolAR

#endif // SOLAR_MESSAGES_H
