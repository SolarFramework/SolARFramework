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

FrameworkReturnCode GlobalDescriptor::setData(GlobalDescriptorType type, GlobalDescriptorDataType dtype, unsigned char* buffer, size_t len)
{
    if (globalDescriptorToLengthType.find(type) == globalDescriptorToLengthType.end()) {
        LOG_ERROR("Unsupported global image descriptor type");
        return FrameworkReturnCode::_ERROR_;
    }
    if (globalDescriptorToLengthType.at(type).first != len) {
        LOG_ERROR("Global descriptor length {} does not match expected {}", len, globalDescriptorToLengthType.at(type).first);
        return FrameworkReturnCode::_ERROR_;
    }
    if (globalDescriptorToLengthType.at(type).second != dtype) {
        LOG_ERROR("Unsupported descriptor data type ({} bytes)", static_cast<size_t>(dtype));
        return FrameworkReturnCode::_ERROR_;
    }
    m_type = type;
    m_dataType = dtype;
    m_length = len;
    if (!m_buffer) {
        m_buffer = xpcf::utils::make_shared<BufferInternal>();
    }
    m_buffer->setData(buffer, len*static_cast<size_t>(dtype));
    LOG_DEBUG("Global descriptor buffer size: {} bytes", m_buffer->getSize());
    return FrameworkReturnCode::_SUCCESS;
}

size_t GlobalDescriptor::length() const
{
    return m_length;
}

unsigned char* GlobalDescriptor::data() const 
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
