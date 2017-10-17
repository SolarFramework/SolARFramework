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

 #ifndef ISOLARCAMERA_H
#define ISOLARCAMERA_H

#include "IComponentIntrospect.h"
#include "SolARImage.h"
#include "SolARMessages.h"
#include "SolARMathDefinitions.h"

namespace SolAR {

class ISolARCamera : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    ISolARCamera() = default;
    virtual ~ISolARCamera() = default;
    virtual FrameworkReturnCode getNextImage(SRef<SolARImage> & img) = 0;
    virtual void setParameters(double frameWidth, double frameHeight, uint32_t device_id)=0;
    virtual void setParameters(double frameWidth, double frameHeight, std::string inputFileName)=0;

    virtual void setIntrinsicParameters(const SolARMatrix33f & intrinsic_parameters) =0;
    virtual void setDistorsionParameters(const SolARVector4f & distorsion_parameters) =0;

    virtual SolARMatrix33f getIntrinsicsParameters() = 0;
    virtual SolARVector4f getDistorsionParameters() = 0;

    //virtual params getCameraIntrinsics() = 0;
    //Frame : image + timestamp image + depth + timestamp depth ...

     static constexpr const char * UUID = "5DDC7DF0-8377-437F-9C81-3643F7676A5B";
};


}

#endif

