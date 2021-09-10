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

#include "xpcf/core/helpers.h"

namespace  SolAR {
namespace datastructure {
const static std::map<DescriptorType, std::pair<uint32_t, DescriptorDataType>> descriptorType2elementsAndDataType =
{{DescriptorType::AKAZE, {61,DescriptorDataType::TYPE_8U}},
 {DescriptorType::SIFT, {128,DescriptorDataType::TYPE_32F}},
 {DescriptorType::SURF_64, {64,DescriptorDataType::TYPE_32F}},
 {DescriptorType::SURF_128, {128,DescriptorDataType::TYPE_32F}},
 {DescriptorType::ORB, {32,DescriptorDataType::TYPE_8U}}
};

DescriptorView::DescriptorView(void * startAddress, uint32_t length, DescriptorType type):
    m_length(length),m_baseAddress(startAddress), m_type(type)
{
    m_dataType = descriptorType2elementsAndDataType.at(type).second;
}

DescriptorBuffer::DescriptorBuffer( const DescriptorView8U & desc):DescriptorBuffer(desc.type(), 1)
{
    m_buffer->setData((void *)(desc.data()), m_nb_descriptors * m_nb_elements * m_data_type);
}

DescriptorBuffer::DescriptorBuffer( const DescriptorView32F & desc):DescriptorBuffer(desc.type(), 1)
{
    m_buffer->setData((void *)(desc.data()), m_nb_descriptors * m_nb_elements * m_data_type);
}

DescriptorBuffer::DescriptorBuffer( const DescriptorView & desc):DescriptorBuffer(desc.type(), 1)
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

DescriptorBuffer::DescriptorBuffer( unsigned char* descriptorData, DescriptorType descriptor_type, uint32_t nb_descriptors):
    m_nb_descriptors(nb_descriptors),m_descriptor_type(descriptor_type),m_buffer(new BufferInternal())
{
    if (!deduceProperties(descriptor_type)) {
        // ERROR no automatic translation : should throw an exception
        return;
    }
    //allocate and fill buffer
    m_buffer->setData(descriptorData, m_nb_descriptors * m_nb_elements * m_data_type);
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

DescriptorView DescriptorBuffer::getDescriptor(uint32_t index) const
{
    void* pDescriptor = m_buffer->data();
    uint32_t offset = m_data_type * m_nb_elements * index;
    pDescriptor = (uint8_t *)pDescriptor + offset;
    return DescriptorView(pDescriptor, m_nb_elements, m_descriptor_type);
}

void DescriptorBuffer::append(const DescriptorView8U & descriptor)
{
    if ((m_descriptor_type != descriptor.type()) || (m_data_type != DescriptorView8U::sDataType)) {
        //throw
        return;
    }
    m_buffer->appendData(static_cast<const void*>(descriptor.data()),descriptor.length());
	m_nb_descriptors++;
}

void DescriptorBuffer::append(const DescriptorView32F & descriptor)
{
    if ((m_descriptor_type != descriptor.type()) || (m_data_type != DescriptorView32F::sDataType)) {
        //throw
        return;
    }
    m_buffer->appendData(static_cast<const void*>(descriptor.data()), descriptor.length() * DescriptorView32F::sDataType);
	m_nb_descriptors++;
}

DescriptorBuffer DescriptorBuffer::convertTo(DescriptorDataType type) const
{
	if (m_data_type == type)
		return DescriptorBuffer(*this);
	std::vector<uint8_t> output;
	if (type == DescriptorDataType::TYPE_8U) {
		float *tmp_data = reinterpret_cast<float*>(m_buffer->data());
		std::vector<uint8_t> tmp_output(m_nb_descriptors * m_nb_elements);
        for (uint32_t i = 0; i < m_nb_descriptors * m_nb_elements; i++) {
			tmp_output[i] = static_cast<uint8_t>(tmp_data[i]);
		}
		output.swap(tmp_output);
	}
	else {
		uint8_t *tmp_data = reinterpret_cast<uint8_t*>(m_buffer->data());
		std::vector<float> tmp_output(m_nb_descriptors * m_nb_elements);
        for (uint32_t i = 0; i < m_nb_descriptors * m_nb_elements; i++) {
			tmp_output[i] = static_cast<float>(tmp_data[i]);
		}
		output.insert(output.begin(), reinterpret_cast<uint8_t*>(tmp_output.data()), reinterpret_cast<uint8_t*>(tmp_output.data()) + m_nb_descriptors * m_nb_elements * 4);
	}
	return DescriptorBuffer(output.data(), m_descriptor_type, type, m_nb_elements, m_nb_descriptors);
}

DescriptorBuffer DescriptorBuffer::operator+(const DescriptorBuffer & desc) const
{
	assert((m_descriptor_type == desc.getDescriptorType()) && (m_nb_descriptors == desc.getNbDescriptors()) && (m_nb_elements == desc.getNbElements()));
	DescriptorBuffer desc1 = this->convertTo(TYPE_32F);
	DescriptorBuffer desc2 = desc.convertTo(TYPE_32F);
	float *desc1_data = reinterpret_cast<float*>(desc1.data());
	float *desc2_data = reinterpret_cast<float*>(desc2.data());
	std::vector<float> output(m_nb_descriptors * m_nb_elements);
	for (int i = 0; i < output.size(); i++)
		output[i] = desc1_data[i] + desc2_data[i];
	return DescriptorBuffer(reinterpret_cast<uint8_t*>(output.data()), m_descriptor_type, TYPE_32F, m_nb_elements, m_nb_descriptors);
}

DescriptorBuffer DescriptorBuffer::operator*(float fac) const
{
	DescriptorBuffer desc = this->convertTo(TYPE_32F);
	float *desc_data = reinterpret_cast<float*>(desc.data());
	std::vector<float> output(m_nb_descriptors * m_nb_elements);
	for (int i = 0; i < output.size(); i++)
		output[i] = desc_data[i] * fac;
	return DescriptorBuffer(reinterpret_cast<uint8_t*>(output.data()), m_descriptor_type, TYPE_32F, m_nb_elements, m_nb_descriptors);
}

DescriptorBuffer DescriptorBuffer::operator/(float div) const
{
	DescriptorBuffer desc = this->convertTo(TYPE_32F);
	float *desc_data = reinterpret_cast<float*>(desc.data());
	std::vector<float> output(m_nb_descriptors * m_nb_elements);
	for (int i = 0; i < output.size(); i++)
		output[i] = desc_data[i] / div;
	return DescriptorBuffer(reinterpret_cast<uint8_t*>(output.data()), m_descriptor_type, TYPE_32F, m_nb_elements, m_nb_descriptors);
}

void DescriptorBuffer::append(const DescriptorView & descriptor)
{
    if ((m_descriptor_type != descriptor.type()) || (m_data_type != descriptor.dataType())) {
        //throw
        return;
    }
    m_buffer->appendData(static_cast<const void*>(descriptor.data()), descriptor.length() * descriptor.dataType());
	m_nb_descriptors++;
}

template<typename Archive>
void DescriptorBuffer::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
	ar & m_buffer;
	ar & m_nb_descriptors;
	ar & m_data_type;
	ar & m_nb_elements;
	ar & m_descriptor_type;
}

DescriptorBufferIterator::DescriptorBufferIterator(const SRef<DescriptorBuffer> & desc):m_buffer(desc),m_nbDescriptors(desc->getNbDescriptors())
{

}

DescriptorView DescriptorBufferIterator::operator *() {
    DescriptorView desc = m_buffer->getDescriptor(m_index);
    return desc;
}

IMPLEMENTSERIALIZE(DescriptorBuffer);

} // namespace datastructure
} // namespace SolAR
