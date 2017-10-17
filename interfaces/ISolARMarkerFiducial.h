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

#ifndef ISOLARMARKERFIDUCIAL_H
#define ISOLARMARKERFIDUCIAL_H


#include "ISolARMarker.h"
#include "SolARImage.h"
#include "SolARMessages.h"
#include "Geometry"
#include "Dense"

namespace SolAR {

class ISolARMarkerFiducial : public virtual SolAR::ISolARMarker {
public:
    ISolARMarkerFiducial() = default;
    virtual ~ISolARMarkerFiducial() = default;

    // my own methods here:


    void generate7x7Marker(std::string& fileToWrite);

   //     friend bool operator<(const Marker &M1, const Marker&M2);
  //  friend std::ostream & operator<<(std::ostream &str, const Marker &M);

    int rotate(SRef<SolARImage>in,SRef<SolARImage>out);
    int hammDistMarker(SRef<SolARImage> bits);
    int mat2id(SRef<SolARImage>bits);
    int getMarkerId(SRef<SolARImage>in, int &nRotations);


    public:

        // Id of  the marker
    int id;

        // Marker transformation with regards to the camera

    Eigen::Vector3f Tpose;
    Eigen::Matrix3f Rpose;

     static constexpr const char * UUID = "12d592ff-aa46-40a6-8d65-7fbfb382d60b";
};
}

#endif // ISOLARIMAGEFILTER_H
