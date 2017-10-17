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

#ifndef ISOLARFILTER_H
#define ISOLARFILTER_H


#include "IComponentIntrospect.h"
#include "SolARMessages.h"

namespace SolAR {

class ISolARFilter : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    ISolARFilter() = default;
    virtual ~ISolARFilter() = default;
     XPCF_DECLARE_UUID("2beadfb7-4bfc-4cbc-8d6f-22c59d10a17b");
};
}


#endif

