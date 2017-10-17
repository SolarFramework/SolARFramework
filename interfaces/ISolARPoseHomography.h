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

#ifndef ISOLARPOSEHOMOGRAPHY_H
#define ISOLARPOSEHOMOGRAPHY_H

#include "SolARMathDefinitions.h"
#include "IComponentIntrospect.h"
#include "SolARImage.h"
#include "ISolARDescriptorMatcher.h"
#include "SolARKeypoint.h"
#include "SolARPose.h"

namespace SolAR {

class ISolARPoseHomography : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
    ISolARPoseHomography() = default;
    virtual ~ISolARPoseHomography() = default;

    virtual SolARPoseMatrix findPose (const std::vector<SolARPoint_2Df> & sourcePoints, const std::vector<SolARPoint_2Df> & dstPoints, const SolARMatrix33d & cameraCalibrationMatrix, SolARPoseMatrix previousPoseMatrix = SolARPoseMatrix() ) = 0;

    // matches not const ?? modified in underlying implementation, but is it the good way ?
    virtual int findHomography(std::vector<std::vector<SolAR::DescriptorMatcher::Match>>& matches,
                  const std::vector< sptrnms::shared_ptr<SolAR::SolARKeypoint> >& keypoints1,
                  const std::vector< sptrnms::shared_ptr<SolAR::SolARKeypoint> >& keypoints2,
                  SolARMatrix33d & homography) = 0;

    virtual void setRefDimensions(int refWidth,int refHeight)=0;

    virtual int computeRefinedPose( const SolARMatrix33d & homography, sptrnms::shared_ptr<ISolARCamera>& cam,const SRef<SolAR::SolARImage> refImage, SolAR::SolARPose & pose) =0;
    virtual int computePose( const SolARMatrix33d & homography, sptrnms::shared_ptr<ISolARCamera>& cam, SolARPoseMatrix & pose) = 0;
    virtual void overlay(const SolARMatrix33d & homography,const SRef<SolAR::SolARImage> refImage, SRef<SolAR::SolARImage> displayImage) = 0;

    virtual void overlay3DProjectedPoint( SolAR::SolARPose & pose, sptrnms::shared_ptr<ISolARCamera>& cam , const SRef<SolAR::SolARImage> refImage, SRef<SolAR::SolARImage> displayImage) =0;

    static constexpr const char * UUID = "4E1320EB-B98B-474C-A741-D3AA9E7AE1CF";
};

}

#endif
