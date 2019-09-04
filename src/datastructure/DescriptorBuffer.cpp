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

#include <vector>
#include <map>

#include "datastructure/DescriptorBuffer.h"

namespace  SolAR {
namespace datastructure {
const static std::map<DescriptorType, std::pair<uint32_t, DescriptorDataType>> descriptorType2elementsAndDataType =
{{DescriptorType::AKAZE, {32,DescriptorDataType::TYPE_8U}},
 {DescriptorType::SIFT, {128,DescriptorDataType::TYPE_8U}},
 {DescriptorType::SURF_64, {64,DescriptorDataType::TYPE_8U}},
 {DescriptorType::SURF_128, {128,DescriptorDataType::TYPE_8U}},
 {DescriptorType::ORB, {32,DescriptorDataType::TYPE_8U}}
};

DescriptorBase::DescriptorBase(void * startAddress, uint32_t length, DescriptorType type):
    m_length(length),m_baseAddress(startAddress), m_type(type)
{
    m_dataType = descriptorType2elementsAndDataType.at(type).second;
}

DescriptorBuffer::DescriptorBuffer( const Descriptor8U & desc):DescriptorBuffer(static_cast<DescriptorType>(desc.type()), 1)
{
    m_buffer->setData((void *)(desc.data()), m_nb_descriptors * m_nb_elements * m_data_type);
}

DescriptorBuffer::DescriptorBuffer( const Descriptor32F & desc):DescriptorBuffer(static_cast<DescriptorType>(desc.type()), 1)
{
    m_buffer->setData((void *)(desc.data()), m_nb_descriptors * m_nb_elements * m_data_type);
}

bool DescriptorBuffer::deduceProperties(const DescriptorType & type)
{
    if (descriptorType2elementsAndDataType.find(type) == descriptorType2elementsAndDataType.end()) {
        // ERROR no automatic translation : should throw an exception
        return false;
    }
    m_nb_elements = descriptorType2elementsAndDataType.at(type).first;
    m_data_type = descriptorType2elementsAndDataType.at(type).second;
    return true;
}

DescriptorBuffer::DescriptorBuffer( DescriptorType descriptor_type, uint32_t nb_descriptors):
    m_nb_descriptors(nb_descriptors),m_descriptor_type(descriptor_type),m_buffer(new BufferInternal())
{
    if (!deduceProperties(descriptor_type)) {
        // ERROR no automatic translation : should throw an exception
        return;
    }
    //allocate buffer
    m_buffer->setSize(m_nb_descriptors * m_nb_elements * m_data_type);
}


DescriptorBuffer::DescriptorBuffer():m_buffer(new BufferInternal()){
    m_descriptor_type = DescriptorType::SIFT;
    m_nb_elements = 128;
    m_data_type = DescriptorDataType::TYPE_32F;
    m_nb_descriptors= 0;
}

DescriptorBuffer::DescriptorBuffer( unsigned char* descriptorData, enum DescriptorType descriptor_type, DescriptorDataType data_type, uint32_t nb_elements, uint32_t nb_descriptors):m_buffer(new BufferInternal()){
    m_descriptor_type = descriptor_type;
    m_nb_descriptors= nb_descriptors;
    m_data_type = data_type;
    m_nb_elements = nb_elements;
    //allocate buffer and fill buffer
    m_buffer->setData(descriptorData, m_nb_descriptors * m_nb_elements * m_data_type);
}

DescriptorBuffer::DescriptorBuffer( enum DescriptorType descriptor_type, DescriptorDataType data_type, uint32_t nb_elements, uint32_t nb_descriptors):m_buffer(new BufferInternal())
{
    m_descriptor_type = descriptor_type;
    m_nb_descriptors= nb_descriptors;
    m_data_type = data_type;
    m_nb_elements = nb_elements;
    //allocate buffer
    m_buffer->setSize(m_nb_descriptors * m_nb_elements * m_data_type);
}

void* DescriptorBuffer::data()
{
    return m_buffer->data();
}

const void* DescriptorBuffer::data() const
{
    return m_buffer->data();
}

DescriptorBase DescriptorBuffer::getDescriptor(uint32_t index)
{
    void* pDescriptor = m_buffer->data();
    uint32_t offset = m_data_type * m_nb_elements * index;
    pDescriptor = (uint8_t *)pDescriptor + offset;
    return DescriptorBase(pDescriptor, m_nb_elements, m_descriptor_type);
}

void DescriptorBuffer::append(const Descriptor8U & descriptor)
{
    if ((m_descriptor_type != descriptor.type()) || (m_data_type != Descriptor8U::sDataType)) {
        //throw
        return;
    }
    m_buffer->appendData(static_cast<const void*>(descriptor.data()),descriptor.length());
}

void DescriptorBuffer::append(const Descriptor32F & descriptor)
{
    if ((m_descriptor_type != descriptor.type()) || (m_data_type != Descriptor32F::sDataType)) {
        //throw
        return;
    }
    m_buffer->appendData(static_cast<const void*>(descriptor.data()), descriptor.length() * Descriptor32F::sDataType);
}

void DescriptorBuffer::append(const DescriptorBase & descriptor)
{
    if ((m_descriptor_type != descriptor.type()) || (m_data_type != descriptor.dataType())) {
        //throw
        return;
    }
    m_buffer->appendData(static_cast<const void*>(descriptor.data()), descriptor.length() * descriptor.dataType());
}

}
}
