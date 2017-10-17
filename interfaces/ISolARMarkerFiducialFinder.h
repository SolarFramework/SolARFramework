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

#ifndef ISOLARMARKERFIDUCIALFINDER_H
#define ISOLARMARKERFIDUCIALFINDER_H

#include "SolARImage.h"
#include "SolARMessages.h"
#include "ISolARMarkerFinder.h"

#include "ISolARMarkerFiducial.h"
#include "SolARMarker.h"


namespace SolAR {

class  ISolARMarkerFiducialFinder : public virtual SolAR::ISolARMarkerFinder{
public:
   ISolARMarkerFiducialFinder() = default;
   virtual ~ISolARMarkerFiducialFinder() = default;

   virtual void setParameters() = 0;
      virtual void setParameters(std::string&config_file) = 0;
   virtual void testMethod()=0;

   virtual int findMarkerCandidates(SRef<SolAR::SolARImage>&img) = 0;
   virtual void recognizeValidMarkers(SRef<SolAR::SolARImage>&img) = 0;
   virtual void drawValidMarkers(SRef<SolAR::SolARImage>&img) = 0;
   virtual void drawAllMarkers(SRef<SolAR::SolARImage>&img) = 0;
   virtual void drawValidMarkers3D(SRef<SolAR::SolARImage>&img) = 0;
   virtual void computePose()=0;

    std::vector<SRef<SolARMarker>>possibleMarkers;
    std::vector<SRef<SolARMarker>>recognizedMarkers;

   XPCF_DECLARE_UUID("a132a266-3c49-4caa-8ccf-cc871309e9dc");
};
}  // end of namespace Solar
#endif // ISOLARMARKERFIDUCIALVALIDATION_H
