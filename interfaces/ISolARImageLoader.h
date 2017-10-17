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

#ifndef ISOLARIMAGELOADER_H
#define ISOLARIMAGELOADER_H

#include "SolARImage.h"
#include "IComponentIntrospect.h"
#include "SolARMessages.h"

namespace SolAR {

class ISolARImageLoader : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    virtual ~ISolARImageLoader() = default;
    virtual FrameworkReturnCode loadImage(const std::string & filename, SRef<SolARImage> & img) = 0;

    static constexpr const char * UUID = "6FCDAA8D-6EA9-4C3F-97B0-46CD11B67A9B";
};


}

#endif
