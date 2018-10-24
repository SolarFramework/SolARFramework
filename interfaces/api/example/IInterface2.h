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

#ifndef SOLAR_IINTERFACEEXAMPLE2_H
#define SOLAR_IINTERFACEEXAMPLE2_H

#include "xpcf/api/IComponentIntrospect.h"

#include "core/Messages.h"

namespace SolAR {
namespace api {
namespace example {

///
/// \brief The IInterface2 class
///
class IInterface2 : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    virtual ~IInterface2() = default;
    ///
    /// \brief example interface # 2
    ///
    virtual FrameworkReturnCode function2(int var) = 0;


};

}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::example::IInterface2,
                             "68f7f567-a56a-4e3b-b8f1-bad6cd08ebf6",
                             "IInterface2",
                             "SolAR::IInterface2 interface");

#endif // SOLAR_IINTERFACEEXAMPLE2_H
