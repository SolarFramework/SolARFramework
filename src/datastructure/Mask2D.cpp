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

#include "datastructure/Mask2D.h"
#include "core/Log.h"
#include <nlohmann/json.hpp>

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::Mask2D);

namespace SolAR {
namespace datastructure {

Mask2D::Mask2D(SRef<Image> mask, const Mask2D::MaskInfoType& info)
{
    m_mask = mask;
    m_maskInfo = info;
}

void Mask2D::setMask(SRef<Image> mask)
{
    m_mask = mask;
}

void Mask2D::setMaskInfo(const Mask2D::MaskInfoType& maskInfo)
{
    m_maskInfo = maskInfo;
}

SRef<Image> Mask2D::getMask() const
{
    return m_mask;
}

SRef<const Image> Mask2D::getConstMask() const
{
    return m_mask;
}

const Mask2D::MaskInfoType& Mask2D::getMaskInfo() const
{
    return m_maskInfo;
}

std::string Mask2D::toString() const
{
    nlohmann::json j;
    j["has_valid_mask_image"] = m_mask ? true : false;
    auto maskInfo = nlohmann::json::array();
    for (const auto& [v, info] : m_maskInfo) {
        maskInfo.push_back({ {"pixel_value", v},
                             {"class", info.classId},
                             {"instance", info.instanceId},
                             {"confidence_score", info.confidence} });
    }
    j["mask_pixel_info"] = maskInfo;
    return j.dump(0);
}

void Mask2D::print() const
{
    LOG_INFO("Mask2D::print - {}", toString());
}

bool Mask2D::save(const std::string& filePng, const std::string& fileJson) const
{
    if (m_mask->getImageEncoding() != Image::ENCODING_PNG) {
        m_mask->setImageEncoding(Image::ENCODING_PNG);
    }
    m_mask->setImageEncodingQuality(100);
    if (m_mask->save(filePng) != FrameworkReturnCode::_SUCCESS) {
        LOG_ERROR("Mask2D::save - failed to save mask image to {}", filePng);
        return false;
    }
    std::ofstream o(fileJson);
    o << toString() << std::endl;
    return true;
}

bool Mask2D::operator==(const Mask2D& other) const
{
    // first, compare the two mask infos
    const auto& inputMaskInfo = other.getMaskInfo();
    if (m_maskInfo.size() != inputMaskInfo.size()) {
        return false;
    }
    auto it = m_maskInfo.begin();
    auto itInput = inputMaskInfo.begin();
    while (it != m_maskInfo.end()) {
        if (it->first != itInput->first) {
            return false;
        }
        if (it->second != itInput->second) {
            return false;
        }
        ++it;
        ++itInput;
    }
    // second, compare the two masks
    if ( (!m_mask && other.getMask()) ||
         (m_mask && !other.getMask()) ) {
        return false;
    }
    if (!m_mask && !other.getMask()) {
        return true; // the same both are invalid
    }   
    uint32_t bufSize = m_mask->getBufferSize();
    if (other.getMask()->getBufferSize() != bufSize) {
        return false;
    }
    const uint8_t* buffer = static_cast<const uint8_t*>(m_mask->data());
    const uint8_t* bufferInput = static_cast<const uint8_t*>(other.getMask()->data());
    for (uint32_t i = 0; i < bufSize; ++i) {
        if (buffer[i] != bufferInput[i]) {
            return false;
        }
    }
    return true;
}

bool Mask2D::operator!=(const Mask2D& other) const
{
    return !(*this == other);
}

template<typename Archive>
void Mask2D::serialize(Archive &ar, const unsigned int /* version */) {
    ar& m_mask;
    ar& m_maskInfo;
}

IMPLEMENTSERIALIZE(Mask2D);

}
}
