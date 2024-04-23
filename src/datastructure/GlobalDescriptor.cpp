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
#include <xpcf/core/helpers.h>

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::GlobalDescriptor);

namespace xpcf  = org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

const static std::map<GlobalDescriptorType, std::pair<size_t, GlobalDescriptorDataType>> globalDescriptorToLengthType =
{
    {GlobalDescriptorType::NETVLAD, {4096, GlobalDescriptorDataType::TYPE_32F}}
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
void GlobalDescriptor::serialize(Archive &ar, const unsigned int /* version */) {
    ar & m_type;
    ar & m_dataType;
    ar & m_buffer;
    ar & m_length;
}

IMPLEMENTSERIALIZE(GlobalDescriptor);

} // datastructure
} // SolAR
