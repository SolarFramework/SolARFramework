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

using json = nlohmann::json;

namespace SolAR {
namespace datastructure {

Mask2D::Mask2D(uint32_t id, SRef<Image> mask, const Mask2D::MaskInfoType& info)
{
    m_id = id;
    m_mask = mask;
    m_maskInfo = info;
}

void Mask2D::setId(uint32_t id)
{
    m_id = id;
}

void Mask2D::setMask(SRef<Image> mask)
{
    m_mask = mask;
}

void Mask2D::setMaskInfo(const Mask2D::MaskInfoType& maskInfo)
{
    m_maskInfo = maskInfo;
}

uint32_t Mask2D::getId() const
{
    return m_id;
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

void Mask2D::print() const
{
    LOG_INFO("ID: {}", m_id);
    LOG_INFO("has valid mask image: {}", m_mask ? "true" : "false");
    for (const auto& [v, info]: m_maskInfo) {
        LOG_INFO("[Mask info] pixel_value {}: class_id {}, instance_id {}, confidence {:.2f}", v, info.classId, info.instanceId, info.confidence);
    }
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
    json j;
    j["id"] = m_id;
    auto maskInfo = json::array();
    for (const auto& [v, info] : m_maskInfo) {
        maskInfo.push_back({ {"pixel_value", v},
                             {"class", info.classId},
                             {"instance", info.instanceId},
                             {"confidence_score", info.confidence} });
    }
    j["mask_pixel_info"] = maskInfo;
    std::ofstream o(fileJson);
    o << j.dump(0) << std::endl;
    return true;
}

template<typename Archive>
void Mask2D::serialize(Archive &ar, const unsigned int /* version */) {
    ar& m_id;
    ar& m_mask;
    ar& m_maskInfo;
}

IMPLEMENTSERIALIZE(Mask2D);

}
}
