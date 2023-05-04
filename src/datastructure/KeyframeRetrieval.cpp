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

#include "datastructure/KeyframeRetrieval.h"
#include "xpcf/core/helpers.h"
#include "core/Log.h"

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::KeyframeRetrieval);

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

FrameworkReturnCode KeyframeRetrieval::addDescriptor(uint32_t id, const SolAR::datastructure::BoWFeature& bowDesc, const SolAR::datastructure::BoWLevelFeature& bowLevelDesc)
{
    if (m_listBoWFeature.find(id) != m_listBoWFeature.end())
		return FrameworkReturnCode::_ERROR_;
	// Add bow desc to the database
    m_listBoWFeature[id] = bowDesc;
    m_listBoWLevelFeature[id] = bowLevelDesc;

	// Add inverted index to the database
    for (auto const &it : bowLevelDesc)
		m_invertedIndexKfs[it.first].insert(id);

	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode KeyframeRetrieval::removeDescriptor(uint32_t id)
{
    auto it_BoWLevelFeature = m_listBoWLevelFeature.find(id);
    if (it_BoWLevelFeature == m_listBoWLevelFeature.end())
		return FrameworkReturnCode::_ERROR_;

	// remove inverted index
    const BoWLevelFeature &v_bowLevelFeature = it_BoWLevelFeature->second;
    for (auto const &it : v_bowLevelFeature)
		m_invertedIndexKfs[it.first].erase(id);

	// remove keyframe descriptors
    m_listBoWFeature.erase(id);
    m_listBoWLevelFeature.erase(id);
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode KeyframeRetrieval::getBoWFeature(uint32_t id, SolAR::datastructure::BoWFeature& bowDesc)
{
    auto it_BoWFeature = m_listBoWFeature.find(id);
    if (it_BoWFeature != m_listBoWFeature.end()) {
        bowDesc = it_BoWFeature->second;
		return FrameworkReturnCode::_SUCCESS;
	}
	else
		return FrameworkReturnCode::_ERROR_;
}

FrameworkReturnCode KeyframeRetrieval::getBoWLevelFeature(uint32_t id, SolAR::datastructure::BoWLevelFeature& bowLevelDesc)
{
    auto it_BoWLevelFeature = m_listBoWLevelFeature.find(id);
    if (it_BoWLevelFeature != m_listBoWLevelFeature.end()) {
        bowLevelDesc = it_BoWLevelFeature->second;
		return FrameworkReturnCode::_SUCCESS;
	}
	else
		return FrameworkReturnCode::_ERROR_;
}

FrameworkReturnCode KeyframeRetrieval::getInvertedIndex(uint32_t nodeId, std::set<uint32_t>& invertedIndex)
{
	auto it_invertedIndex = m_invertedIndexKfs.find(nodeId);
	if (it_invertedIndex != m_invertedIndexKfs.end()) {
		invertedIndex = it_invertedIndex->second;
		return FrameworkReturnCode::_SUCCESS;
	}
	else
		return FrameworkReturnCode::_ERROR_;
}

void KeyframeRetrieval::reset()
{
    m_listBoWFeature.clear();
    m_listBoWLevelFeature.clear();
    m_invertedIndexKfs.clear();
}

template <typename Archive>
void KeyframeRetrieval::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version)
{
    ar & m_listBoWFeature;
    ar & m_listBoWLevelFeature;
	ar & m_invertedIndexKfs;
}

IMPLEMENTSERIALIZE(KeyframeRetrieval);

} // end of namespace datastructure
} // end of namespace SolAR
