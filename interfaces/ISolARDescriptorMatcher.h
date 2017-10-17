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

#ifndef ISOLARDESCRIPTORMATCHER_H
#define ISOLARDESCRIPTORMATCHER_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include <vector>
#include "ISolARDescriptor.h"

// Definition of ISolARDescriptorMatcher Class //
// part of SolAR namespace //

#include "IComponentIntrospect.h"

namespace SolAR {

	namespace DescriptorMatcher {

    ///
    /// \brief The DescriptorMatcher return codes
    ///
		enum  RetCode {
          DESCRIPTORS_MATCHER_OK=0,     /**< the default OK code*/
           DESCRIPTORS_DONT_MATCH,      /**< try to match descriptors of different types*/
           DESCRIPTOR_TYPE_UNDEFINED,   /**< one of the descriptor sets is is unknown*/
           DESCRIPTOR_EMPTY             /**< One set is empty*/
		};

    ///
    /// \brief The DescriptorMatcher Match element
    ///
		struct Match{
            int idx1;               /**< the index of the match in the first set of descriptors*/
            int idx2;               /**< the index of the match in the second set of descriptors*/
            float distance;         /**< the distance betwenn the two descriptors*/
		};
    }    // end of namespace DescriptorMatcher

///
/// \brief The ISolARDescriptorMatcher class
///
    class  ISolARDescriptorMatcher : public virtual org::bcom::xpcf::IComponentIntrospect {
    public:
    	ISolARDescriptorMatcher() = default;

   ///
   /// \brief ~ISolARDescriptorMatcher
   ///
    	virtual ~ISolARDescriptorMatcher() {};
       ///
       /// \brief Match function
       /// returns one match per element of the first descriptor set
       ///
    	virtual DescriptorMatcher::RetCode match(
               sptrnms::shared_ptr<ISolARDescriptor>& descriptors1,       /**< first set of descriptors*/
               sptrnms::shared_ptr<ISolARDescriptor>& descriptors2,       /**< second set of descriptors to match against the first set*/
               std::vector<DescriptorMatcher::Match>& matches        /**< one dimensional set of matches */
    		)=0;


       ///
       /// \brief Match function
       /// returns several matches per element of the first descriptor set
       ///
    	virtual DescriptorMatcher::RetCode match(
               sptrnms::shared_ptr<ISolARDescriptor>& descriptors1,                      /**< first set of descriptors*/
               sptrnms::shared_ptr<ISolARDescriptor>& descriptors2,                      /**< second set of descriptors to match against the first set*/
               std::vector<std::vector<DescriptorMatcher::Match>>& matches,         /**< two dimensional set of matches */
               int nbOfMatches                                                      /**< number of matches per element of the first set of descriptors*/
    		)=0;



    	XPCF_DECLARE_UUID("dda38a40-c50a-4e7d-8433-0f04c7c98518");
    };

}  // end of namespace SolAR

#endif // ISOLARDESCRIPTORMATCHER_H
