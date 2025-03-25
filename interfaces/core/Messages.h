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

#include <string>

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

    // Requested resource has not been found
    _NOT_FOUND = -3,

    // Resource already exists
    _ALREADY_EXIST = -4,

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
    _NO_SERVICE_LOCKED = -23,

    // for client sessions
    _UNKNOWN_MAP_UUID = -30,
    _UNKNOWN_CLIENT_UUID = -31,
    _REQUEST_SERVICE_FAILURE = -32,
    _INIT_SERVICE_FAILURE = -33,
    _SERVICE_NOT_INITIALIZED = -34,
    _CAMERA_PARAMETERS_NOT_SET = -35,
    _SERVICE_NOT_STARTED = -36,

    // for license management
    _LICENSE_SERVER_UNKNOWN_ERROR = -40,
    _LICENSE_SERVER_NOT_REACHABLE = -41,
    _LICENSE_NOT_VALID = -42,
    _LICENSE_UNAVAILABLE_PARAMETER = -43,
    _LICENSE_INCORRECT_SERVICE_VERSION = -44,
    _LICENSE_MAX_CLIENTS_MAPPING_EXCEEDED = -45,
    _LICENSE_MAX_CLIENTS_RELOC_EXCEEDED = -46,
    _LICENSE_MAX_CLIENTS_STEREO_MAPPING_EXCEEDED = -47,
    _LICENSE_MAX_CLIENTS_DENSE_MAPPING_EXCEEDED = -48,
    _LICENSE_MAX_CLIENTS_STRUCTURE_FROM_MOTION_EXCEEDED = -49,

    // for authentication requests
    _AUTHENT_SERVICE_UNAVAILABLE = -50,
    _AUTHENT_REQUEST_FAILURE = -51,
    _AUTHENT_INVALID_TOKEN = -52,
    _AUTHENT_RESOURCE_NOT_FOUND = -53
};

/// @brief Return the text definition (string) of a return code
/// @param[in] returnCode return code
/// @return the text definition (string)
static std::string getReturnCodeDefinition(const FrameworkReturnCode returnCode)
{
    std::string txt_definition = "";

    switch (returnCode) {
        case FrameworkReturnCode::_ERROR_:
            txt_definition = "Generic error code";
            break;
        case FrameworkReturnCode::_NOT_IMPLEMENTED:
            txt_definition = "Method not implemented";
            break;
        case FrameworkReturnCode::_NOT_FOUND:
            txt_definition = "Requested resource has not been found";
            break;
        case FrameworkReturnCode::_ALREADY_EXIST:
            txt_definition = "Resource already exists";
            break;
        case FrameworkReturnCode::_ERROR_LOAD_IMAGE:
            txt_definition = "Error while loading an image";
            break;
        case FrameworkReturnCode::_ERROR_ACCESS_IMAGE:
            txt_definition = "Error while accessing an image";
            break;
        case FrameworkReturnCode::_BUSY:
            txt_definition = "Service busy";
            break;
        case FrameworkReturnCode::_NO_SERVICE_REGISTERED:
            txt_definition = "No service registered for this kind of processing";
            break;
        case FrameworkReturnCode::_NO_SERVICE_AVAILABLE:
            txt_definition = "No service available for this kind of processing";
            break;
        case FrameworkReturnCode::_NO_SERVICE_LOCKED:
            txt_definition = "No service locked for client for this kind of processing";
            break;
        case FrameworkReturnCode::_UNKNOWN_MAP_UUID:
            txt_definition = "Unknown map UUID";
            break;
        case FrameworkReturnCode::_UNKNOWN_CLIENT_UUID:
            txt_definition = "Unknown client UUID";
            break;
        case FrameworkReturnCode::_REQUEST_SERVICE_FAILURE:
            txt_definition = "Request to service failed";
            break;
        case FrameworkReturnCode::_INIT_SERVICE_FAILURE:
            txt_definition = "Service initialization failed";
            break;
        case FrameworkReturnCode::_SERVICE_NOT_INITIALIZED:
            txt_definition = "Service not initialized";
            break;
        case FrameworkReturnCode::_CAMERA_PARAMETERS_NOT_SET:
            txt_definition = "Camera parameters not set";
            break;
        case FrameworkReturnCode::_SERVICE_NOT_STARTED:
            txt_definition = "Service not started";
            break;
        case FrameworkReturnCode::_LICENSE_SERVER_UNKNOWN_ERROR:
            txt_definition = "License server unknown error";
            break;
        case FrameworkReturnCode::_LICENSE_SERVER_NOT_REACHABLE:
            txt_definition = "License server not reachable";
            break;
        case FrameworkReturnCode::_LICENSE_NOT_VALID:
            txt_definition = "Invalid license";
            break;
        case FrameworkReturnCode::_LICENSE_UNAVAILABLE_PARAMETER:
            txt_definition = "Unavailable parameter in license file";
            break;
        case FrameworkReturnCode::_LICENSE_INCORRECT_SERVICE_VERSION:
            txt_definition = "Incorrect version of services according to license file";
            break;
        case FrameworkReturnCode::_LICENSE_MAX_CLIENTS_MAPPING_EXCEEDED:
            txt_definition = "Maximum of clients for Mapping reached according to license file";
            break;
        case FrameworkReturnCode::_LICENSE_MAX_CLIENTS_RELOC_EXCEEDED:
            txt_definition = "Maximum of clients for Relocalization reached according to license file";
            break;
        case FrameworkReturnCode::_LICENSE_MAX_CLIENTS_STEREO_MAPPING_EXCEEDED:
            txt_definition = "Maximum of clients for Stereo Mapping reached according to license file";
            break;
        case FrameworkReturnCode::_LICENSE_MAX_CLIENTS_DENSE_MAPPING_EXCEEDED:
            txt_definition = "Maximum of clients for Dense Mapping reached according to license file";
            break;
        case FrameworkReturnCode::_LICENSE_MAX_CLIENTS_STRUCTURE_FROM_MOTION_EXCEEDED:
            txt_definition = "Maximum of clients for Structure From Motion reached according to license file";
            break;
        case FrameworkReturnCode::_AUTHENT_SERVICE_UNAVAILABLE:
            txt_definition = "Authentication service unavailable";
            break;
        case FrameworkReturnCode::_AUTHENT_REQUEST_FAILURE:
            txt_definition = "Authentication request failure";
            break;
        case FrameworkReturnCode::_AUTHENT_INVALID_TOKEN:
            txt_definition = "Authentication invalid token";
            break;
        case FrameworkReturnCode::_AUTHENT_RESOURCE_NOT_FOUND:
            txt_definition = "Authentication resource not found";
            break;
        default:
            txt_definition = "Unknown error code";
            break;
    }

    return txt_definition;
}

}  // end of namespace SolAR

#endif // SOLAR_MESSAGES_H
