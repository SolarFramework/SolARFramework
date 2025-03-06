/**
 * @copyright Copyright (c) 2025 B-com http://www.b-com.com/
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

#ifndef IAUTHORIZATIONCHECKER_H
#define IAUTHORIZATIONCHECKER_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/api/IComponentManager.h>
#include <xpcf/core/helpers.h>
#include "core/Messages.h"
#include "core/SolARFrameworkDefinitions.h"

namespace SolAR {
namespace api {
namespace service {

/**
 * @class IAuthorizationChecker
 * @brief <B>Checks if a client providing a token is authorized to use a service.</B>
 * <TT>UUID: 02031edc-2388-470e-84e5-4d997fd1f093</TT>
 */

class XPCF_IGNORE SOLARFRAMEWORK_API IAuthorizationChecker :
    virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    /// @brief IAuthorizationChecker default constructor
    IAuthorizationChecker() = default;

    /// @brief IAuthorizationChecker default destructor
    virtual ~IAuthorizationChecker() = default;

    /// @brief Check if the token is valid.
    /// @param[in] accessToken the token to verify
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the the token is valid
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * FrameworkReturnCode::_AUTHENT_SERVICE_UNAVAILABLE if authentication server is unavailable
    /// * FrameworkReturnCode::_AUTHENT_REQUEST_FAILURE if the request to the authentication server failed
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode isTokenValid(const std::string & accessToken) = 0;

    /// @brief Checks if a client providing a token is authorized to use a service.
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] apiName the name of the api for which the authorization is checked
    /// @param[in] resource the name of to be used by the api
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the client is authorized to use the service with the given resource.
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode isAuthorized(const std::string & accessToken,
                                             const std::string & apiName,
                                             const std::string & resource) = 0;

    /// @brief return the list of resources that can be used by a given service from a given token.
    /// @param[in] accessToken a valid Token collected by client after login to the authentication server
    /// @param[in] apiName the name of the api for which we want to return all the authorized resources
    /// @param[in] authorizedResources the list of resources that can be used by the given service.
    /// @return
    /// * FrameworkReturnCode::_SUCCESS if the client is registered with its UUID
    /// * FrameworkReturnCode::_AUTHENT_INVALID_TOKEN if the authentication token is invalid
    /// * else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode getAuthorizedResources(const std::string & accessToken,
                                                       const std::string & apiName,
                                                       std::vector<std::string>& authorizedResources) = 0;
};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::service::IAuthorizationChecker,
                             "02031edc-2388-470e-84e5-4d997fd1f093",
                             "IAuthorizationChecker",
                             "The interface to check a service authorization access from a token");

#endif // IAUTHORIZATIONCHECKER_H
