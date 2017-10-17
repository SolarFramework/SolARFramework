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

#ifndef ISOLARDESCRIPTOREXTRACTOR_H
#define ISOLARDESCRIPTOREXTRACTOR_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <vector>
#include "SolARKeypoint.h"
#include "ISolARDescriptor.h"
#include "SolARImage.h"


// Definition of ISolARDescriptorExtractor Class //
// part of SolAR namespace //

#include "IComponentIntrospect.h"

namespace SolAR {

///
/// \brief The SolARDescriptorExtractorType enum
///
	enum class SolARDescriptorExtractorType {
		UNKNOWN_TYPE=-1,
		SURF,
		ORB,
		SIFT,
		DAISY,
		LATCH,
		AKAZE,
		AKAZEUP,
		BRISK,
		BRIEF,
	};

///
/// \brief The ISolARDescriptorExtractor class
///
	class  ISolARDescriptorExtractor : public virtual org::bcom::xpcf::IComponentIntrospect {
	public:
		ISolARDescriptorExtractor() = default;

   ///
   /// \brief ~ISolARDescriptorExtractor
   ///
		virtual ~ISolARDescriptorExtractor() {};

   ///
   /// \brief setType
   /// \param type
   ///
		virtual void setType(SolARDescriptorExtractorType type) = 0;

   ///
   /// \brief getType
   /// \return
   ///
		virtual SolARDescriptorExtractorType  getType() = 0;
		virtual std::string  getTypeString() = 0;

   ///
   /// \brief compute
   /// \param image
   /// \param keypoints
   /// \param descriptors
   ///
        virtual void compute (const SRef<SolARImage> image, std::vector< sptrnms::shared_ptr<SolARKeypoint> > &keypoints,sptrnms::shared_ptr<ISolARDescriptor>& descriptors) = 0;
		XPCF_DECLARE_UUID("c0e49ff1-0696-4fe6-85a8-9b2c1e155d2e");
	};

}  // end of namespace SolAR

#endif // ISOLARDESCRIPTOREXTRACTOR_H
