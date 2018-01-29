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

#ifndef SOLARFRAMEWORK_H
#define SOLARFRAMEWORK_H

#if _WIN32
#ifdef SolARFramework_API_DLLEXPORT
#define _BCOM_SHARED __declspec(dllexport)
#else //_BCOM_SHARED
#define _BCOM_SHARED __declspec(dllimport)
#endif //_BCOM_SHARED
#else //_WIN32
#define _BCOM_SHARED
#endif //_WIN32

#include <string>

#define _STR(x) #x
#define STR(X)  _STR(x)

namespace SolAR {

/// \brief This method returns the version of the SolAR Framework
_BCOM_SHARED std::string getSolARFrameworkVersion();

}

#endif // SOLARFRAMEWORK_H
