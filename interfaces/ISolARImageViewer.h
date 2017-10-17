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

#ifndef ISOLARIMAGEVIEWER_H
#define ISOLARIMAGEVIEWER_H

#include "SolARImage.h"
#include "IComponentIntrospect.h"
#include "SolARMessages.h"

namespace SolAR {

class ISolARImageViewer : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    virtual ~ISolARImageViewer() = default;
    virtual FrameworkReturnCode display(const char * title, SRef<SolARImage> img) = 0;
    virtual FrameworkReturnCode display(const char * title, SRef<SolARImage> img, const char* exitKey) = 0;
    virtual FrameworkReturnCode display(const char * title, SRef<SolARImage> img, uint32_t duration) = 0;
    static constexpr const char * UUID = "B05F3DBB-F93D-465C-AEE1-FB58E1480C42";
};


}

#endif
