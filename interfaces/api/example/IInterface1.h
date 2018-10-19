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

#ifndef SOLAR_IINTERFACEEXAMPLE1_H
#define SOLAR_IINTERFACEEXAMPLE1_H

#include "xpcf/api/IComponentIntrospect.h"

#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace example {

///
/// \brief The IInterface1 class
///
class IInterface1 : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    virtual ~IInterface1() = default;
    ///
    /// \brief example interface # 1
    ///
    virtual FrameworkReturnCode function1(int var) = 0;


};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::example::IInterface1,
                             "b713caa4-832d-4d2e-9cc1-651e33fe49c2",
                             "SolAR::IInterface1 interface");

#endif // SOLAR_IINTERFACEEXAMPLE1_H
