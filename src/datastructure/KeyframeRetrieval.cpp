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

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

FrameworkReturnCode KeyframeRetrieval::addDescriptor(uint32_t id, const fbow::fBow & fbowDesc, const fbow::fBow2 & fbow2Desc)
{
	if (m_list_KFBoW.find(id) != m_list_KFBoW.end())
		return FrameworkReturnCode::_ERROR_;
	// Add bow desc to the database
	m_list_KFBoW[id] = fbowDesc;
	m_list_KFBoW2[id] = fbow2Desc;

	// Add inverted index to the database
	for (auto const &it : fbow2Desc)
		m_invertedIndexKfs[it.first].insert(id);

	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode KeyframeRetrieval::removeDescriptor(uint32_t id)
{
	auto it_KFBoW2 = m_list_KFBoW2.find(id);
	if (it_KFBoW2 == m_list_KFBoW2.end())
		return FrameworkReturnCode::_ERROR_;

	// remove inverted index
	const fbow::fBow2 &v_bow2 = it_KFBoW2->second;
	for (auto const &it : v_bow2)
		m_invertedIndexKfs[it.first].erase(id);

	// remove keyframe descriptors
	m_list_KFBoW.erase(id);
	m_list_KFBoW2.erase(id);
	return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode KeyframeRetrieval::getFBow(uint32_t id, fbow::fBow & fbowDesc)
{
	auto it_KFBoW = m_list_KFBoW.find(id);
	if (it_KFBoW != m_list_KFBoW.end()) {
		fbowDesc = it_KFBoW->second;
		return FrameworkReturnCode::_SUCCESS;
	}
	else
		return FrameworkReturnCode::_ERROR_;
}

FrameworkReturnCode KeyframeRetrieval::getFBow2(uint32_t id, fbow::fBow2 & fbow2Desc)
{
	auto it_KFBoW2 = m_list_KFBoW2.find(id);
	if (it_KFBoW2 != m_list_KFBoW2.end()) {
		fbow2Desc = it_KFBoW2->second;
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

template <typename Archive>
void KeyframeRetrieval::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version)
{
	ar & m_list_KFBoW;
	ar & m_list_KFBoW2;
	ar & m_invertedIndexKfs;
}

IMPLEMENTSERIALIZE(KeyframeRetrieval);

} // end of namespace datastructure
} // end of namespace SolAR
