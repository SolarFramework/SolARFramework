/**
 * @copyright Copyright (c) 2017-2025 B-com http://www.b-com.com/
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

#include "datastructure/Mask2DCollection.h"
#include "core/Log.h"
#include <filesystem>
#include <xpcf/core/helpers.h>

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::Mask2DCollection);

namespace xpcf = org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

FrameworkReturnCode Mask2DCollection::addMask(SRef<const Mask2D> mask, bool defineMaskId)
{
    if (!mask) {
        LOG_ERROR("Mask2DCollection::addMask - invalid input mask pointer.");
        return FrameworkReturnCode::_ERROR_;
    }
    return addMask(*mask, defineMaskId);
}

FrameworkReturnCode Mask2DCollection::addMask(const Mask2D& mask, bool defineMaskId)
{
    auto newMask = xpcf::utils::make_shared<Mask2D>(mask);
    if (defineMaskId) {
        newMask->setId(m_currentId++);
    }
    m_masks[newMask->getId()] = newMask;
    return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode Mask2DCollection::getMask(uint32_t id, SRef<Mask2D>& mask) const
{
    auto maskIt = m_masks.find(id);
    if (maskIt != m_masks.end()) {
        mask = maskIt->second;
        return FrameworkReturnCode::_SUCCESS;
    }
    else {
        LOG_DEBUG("Mask2DCollection::getMask - cannot find mask with id {}", id);
        return FrameworkReturnCode::_ERROR_;
    }
}

FrameworkReturnCode Mask2DCollection::getMasks(const std::vector<uint32_t>& ids, std::vector<SRef<Mask2D>>& masks) const
{
    masks.clear();
    masks.reserve(ids.size());
    for (const auto& id : ids) {
        SRef<Mask2D> mask;
        if (getMask(id, mask) != FrameworkReturnCode::_SUCCESS) {
            continue;
        }
        masks.push_back(mask);
    }
    if (masks.empty()) {
        LOG_ERROR("Mask2DCollection::getMasks - didn't find any masks.");
        return FrameworkReturnCode::_ERROR_;
    }
    return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode Mask2DCollection::getAllMasks(std::vector<SRef<Mask2D>>& masks) const
{
    masks.clear();
    masks.reserve(m_masks.size());
    for (const auto& mask: m_masks) {
        masks.push_back(mask.second);
    }
    return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode Mask2DCollection::suppressMask(uint32_t id)
{
    auto maskIt = m_masks.find(id);
    if (maskIt == m_masks.end()) {
        LOG_ERROR("Mask2DCollection::suppressMask - cannot find mask with id {} to suppress", id);
        return FrameworkReturnCode::_ERROR_;
    }
    m_masks.erase(maskIt);
    return FrameworkReturnCode::_SUCCESS;
}

bool Mask2DCollection::isExistMask(uint32_t id) const
{
    return m_masks.find(id) != m_masks.end();
}

size_t Mask2DCollection::getNbMasks() const
{
	return m_masks.size();
}

void Mask2DCollection::clear()
{
    m_masks.clear();
    m_currentId = 0;
}

FrameworkReturnCode Mask2DCollection::save(const std::string& pathToFolder) const
{
    if (m_masks.empty()) {
        LOG_ERROR("Mask2DCollection::save - empty mask list.");
        return FrameworkReturnCode::_ERROR_;
    }
    if (!std::filesystem::exists(pathToFolder)) {
        std::filesystem::create_directory(pathToFolder);
    }
    for (const auto& [id, mask] : m_masks) {
        std::string filenamePng = pathToFolder + "/" + std::to_string(id) + ".png";
        std::string filenameJson = pathToFolder + "/" + std::to_string(id) + ".json";
        if (!mask->save(filenamePng, filenameJson)) {
            LOG_ERROR("Mask2DCollection::save - failed to save mask {}", id);
            return FrameworkReturnCode::_ERROR_;
        }
    }
    return FrameworkReturnCode::_SUCCESS;
}

void Mask2DCollection::print() const
{
    LOG_INFO("Current ID: {}", m_currentId);
    LOG_INFO("Number of masks: {}", m_masks.size());
    for (const auto& [id, mask] : m_masks) {
        LOG_INFO("Mask ID: {}", id);
        mask->print();
    }
}

template <typename Archive>
void Mask2DCollection::serialize(Archive &ar, const unsigned int /* version */)
{
	ar & m_currentId;
	ar & m_masks;
}

IMPLEMENTSERIALIZE(Mask2DCollection);

} // end of namespace datastructure
} // end of namespace SolAR
