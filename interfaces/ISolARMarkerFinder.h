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

#ifndef ISOLARMARKERFINDER_H
#define ISOLARMARKERFINDER_H

#include "IComponentIntrospect.h"
#include "SolARImage.h"
#include "SolARMarker.h"
#include "SolARMessages.h"

namespace SolAR {
class  ISolARMarkerFinder : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
   ISolARMarkerFinder() = default;
   virtual ~ISolARMarkerFinder() = default;

   XPCF_DECLARE_UUID("c7f7253b-9de0-44dc-a159-bbfc8eab6f63");
};
}  // end of namespace Solar

#endif // ISOLARMARKERVALIDATION_H
