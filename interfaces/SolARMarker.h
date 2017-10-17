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

#ifndef SOLARMARKER_H
#define SOLARMARKER_H

#include "ComponentBase.h"
#include "SolARImage.h"

#include "XPCF_definitions.h"

#include <Dense>
#include <Geometry>

#include <string>

namespace SolAR {

class XPCF_EXPORT_API SolARMarker {

public:
    SolARMarker();
    SolARMarker(std::vector<std::pair<float, float>>&edges_temp);
    ~SolARMarker();

    void generate7x7Marker(std::string& fileToWrite);

    int rotate(SRef<SolARImage>in,SRef<SolARImage>out);
    int hammDistMarker(SRef<SolARImage> bits);
    int mat2id(SRef<SolARImage>bits);
    int getMarkerId(SRef<SolARImage>in, int &nRotations);
     double getArea();
        // Id of  the marker
    int id;

        // Marker transformation with regards to the camera

     Eigen::Vector3f Tpose;
     Eigen::Matrix3f Rpose;
     Eigen::Vector3f Anglespose;
     std::vector<std::pair<float, float> >edges;
};


}  // end of namespace Solar



#endif // SOLARMARKER_H
