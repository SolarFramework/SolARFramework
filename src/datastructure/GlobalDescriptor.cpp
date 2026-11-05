/**
 * @copyright Copyright (c) 2024 B-com http://www.b-com.com/
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

#include "core/Log.h"
#include "datastructure/GlobalDescriptor.h"
#include <stdexcept>
#include <vector>
#include <xpcf/core/helpers.h>

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::GlobalDescriptor);

namespace xpcf  = org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

const static std::map<GlobalDescriptorType, std::pair<size_t, GlobalDescriptorDataType>> globalDescriptorToLengthType =
{
    {GlobalDescriptorType::NETVLAD, {4096, GlobalDescriptorDataType::TYPE_32F}},
    {GlobalDescriptorType::BOQ, {16384, GlobalDescriptorDataType::TYPE_32F}}
};

std::optional<GlobalDescriptor> GlobalDescriptor::build(GlobalDescriptorType type, unsigned char* buffer)
{
    if (!buffer) {
        LOG_ERROR("Empty input data buffer, cannot build global descriptor");
        return std::nullopt;
    }
    if (globalDescriptorToLengthType.find(type) == globalDescriptorToLengthType.end()) {
        LOG_ERROR("Unsupported type, cannot build global descriptor");
        return std::nullopt;
    }
    return GlobalDescriptor(type, globalDescriptorToLengthType.at(type).second, buffer, globalDescriptorToLengthType.at(type).first);
}

SRef<GlobalDescriptor> GlobalDescriptor::buildSharedRef(GlobalDescriptorType type, unsigned char* buffer)
{
    if (!buffer) {
        LOG_ERROR("Empty input data buffer, cannot build global descriptor");
        return nullptr;
    }
    if (globalDescriptorToLengthType.find(type) == globalDescriptorToLengthType.end()) {
        LOG_ERROR("Unsupported type, cannot build global descriptor");
        return nullptr;
    }
    auto gd = GlobalDescriptor(type, globalDescriptorToLengthType.at(type).second, buffer, globalDescriptorToLengthType.at(type).first);
    return xpcf::utils::make_shared<GlobalDescriptor>(gd);
}

GlobalDescriptor::GlobalDescriptor(GlobalDescriptorType type, GlobalDescriptorDataType dtype, unsigned char* buffer, size_t len)
{
    m_type = type;
    m_dataType = dtype;
    m_length = len;
    if (!m_buffer) {
        m_buffer = xpcf::utils::make_shared<BufferInternal>();
    }
    m_buffer->setData(buffer, len*static_cast<size_t>(dtype));
    LOG_DEBUG("Global descriptor buffer size: {} bytes", m_buffer->getSize());

}

size_t GlobalDescriptor::getLength() const
{
    return m_length;
}

const unsigned char* GlobalDescriptor::data() const 
{
    if (!m_buffer) {
        return nullptr;
    }
    return static_cast<const unsigned char*>(m_buffer->data());
}

unsigned char* GlobalDescriptor::data() 
{
    if (!m_buffer) {
        return nullptr;
    }
    return static_cast<unsigned char*>(m_buffer->data());
}

GlobalDescriptorType GlobalDescriptor::getType() const
{
    return m_type;
}

GlobalDescriptorDataType GlobalDescriptor::getDataType() const
{
    return m_dataType;
}

bool GlobalDescriptor::isValid() 
{
    if (!m_buffer) {
        return false;
    }
    if (globalDescriptorToLengthType.find(m_type) == globalDescriptorToLengthType.end()) {
        return false;
    }
    if (globalDescriptorToLengthType.at(m_type).first != m_length) {
        return false;
    }
    if (globalDescriptorToLengthType.at(m_type).second != m_dataType) {
        return false;
    }
    return true;
}

template<typename Archive>
void GlobalDescriptor::serialize(Archive &ar, const unsigned int version) {
    // float descriptors are written as FLOAT16 when the map descriptors are not stored as float32 (L2-normalised: no range issue)
    uint8_t half = 0;
    if constexpr (Archive::is_saving::value)
        half = (DescriptorBuffer::getStorage() != DescriptorBuffer::Storage::FLOAT32 && m_dataType == GlobalDescriptorDataType::TYPE_32F
                && m_buffer && m_length > 0 && m_buffer->getSize() >= m_length * sizeof(float)) ? 1 : 0;
    if (version >= 1)
        ar & half;
    ar & m_type;
    ar & m_dataType;
    if (!half) {
        ar & m_buffer;
        ar & m_length;
        return;
    }
    ar & m_length;
    if constexpr (Archive::is_saving::value) {
        const float* values = static_cast<const float*>(m_buffer->data());
        std::vector<uint16_t> halves(m_length);
        for (size_t i = 0; i < m_length; ++i) halves[i] = DescriptorBuffer::floatToHalf(values[i]);
        ar & halves;
    }
    else {
        std::vector<uint16_t> halves;
        ar & halves;
        if (halves.size() != m_length)
            throw std::runtime_error("GlobalDescriptor: FLOAT16 payload size does not match its length");
        m_buffer = org::bcom::xpcf::utils::make_shared<BufferInternal>(uint32_t(m_length * sizeof(float)));
        float* values = static_cast<float*>(m_buffer->data());
        for (size_t i = 0; i < m_length; ++i) values[i] = DescriptorBuffer::halfToFloat(halves[i]);
    }
}

IMPLEMENTSERIALIZE(GlobalDescriptor);

} // datastructure
} // SolAR
