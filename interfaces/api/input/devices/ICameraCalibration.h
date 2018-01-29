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

#ifndef SOLAR_ICAMERACALIBRATION_H
#define SOLAR_ICAMERACALIBRATION_H

#include "IComponentIntrospect.h"
#include "datastructure/Image.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace input {
namespace devices {

/// @class ICameraCalibration
/// \brief The ICameraCalibration class
///
class  ICameraCalibration : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
   ICameraCalibration() = default;

   ///
   /// \brief ~ICameraCalibration
   ///
   virtual ~ICameraCalibration() {};

   /// \brief Calibrate the camera device referenced by its id and output the result in the given file
   virtual bool calibrate(int camera_id, std::string&output)=0;
   /// \brief Set the camera device calibration parameters
   virtual bool setParameters(std::string&config_file)=0;
   XPCF_DECLARE_UUID("0e83b228-b9ca-413d-9dc2-db45c427428b");
};

}
}
}
}  // end of namespace Solar

#endif // SOLAR_ICAMERACALIBRATION_H
