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

#ifndef SOLAR_DESCRIPTORMATCH_H
#define SOLAR_DESCRIPTORMATCH_H

#include <tuple>

namespace SolAR {
namespace datastructure {

/**
 * @class DescriptorMatch
 * @brief <B>A match between two descriptors.</B>
 *
 * This class provides a data structure to store only the results from IDescriptorMatcher.
 *
 *
 */
class DescriptorMatch
{
public:

    /// \brief DescriptorMatch
    ///  @param descriptor_idX:
    ///  @param descriptor_idY:
    ///  @param matching_score:
    ///
    DescriptorMatch(unsigned int descriptor_idA, unsigned int descriptor_idB, float matching_score){
        m_match =std::make_tuple(descriptor_idA, descriptor_idB,matching_score);
    }

    /// \brief Return the index of the matching descriptor from a DescriptorBuffer A.
    ///
    unsigned int getIndexInDescriptorA(void) const {
        return std::get<0>(m_match);
    }

    /// \brief Return the index of the matching descriptor from a DescriptorBuffer B.
    ///
    unsigned int getIndexInDescriptorB(void) const{
        return std::get<1>(m_match);
    }

    /// \brief Return the matching score between the two indexed descriptors.
    ///
    unsigned int getMatchingScore(void) const{
        return std::get<2>(m_match);
    }

    
private:
    std::tuple<unsigned int, unsigned int, float> m_match;
};

}
}

#endif //SOLAR_DESCRIPTORMATCH_H
