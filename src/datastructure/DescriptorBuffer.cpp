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
#include <atomic>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stdexcept>

#include "datastructure/DescriptorBuffer.h"

#include <xpcf/core/helpers.h>

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::DescriptorBuffer);

namespace  SolAR {
namespace datastructure {
const static std::map<DescriptorType, std::pair<uint32_t, DescriptorDataType>> descriptorType2elementsAndDataType =
{{DescriptorType::AKAZE, {61,DescriptorDataType::TYPE_8U}},
 {DescriptorType::SIFT, {128,DescriptorDataType::TYPE_32F}},
 {DescriptorType::SIFT_UINT8, {128,DescriptorDataType::TYPE_8U}},
 {DescriptorType::SURF_64, {64,DescriptorDataType::TYPE_32F}},
 {DescriptorType::SURF_128, {128,DescriptorDataType::TYPE_32F}},
 {DescriptorType::ORB, {32,DescriptorDataType::TYPE_8U}},
 {DescriptorType::DISK, {128,DescriptorDataType::TYPE_8U}}
};

DescriptorView::DescriptorView(void * startAddress, uint32_t length, DescriptorType type):
    m_baseAddress(startAddress), m_length(length), m_type(type)
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
    m_buffer(new BufferInternal()), m_nb_descriptors(nb_descriptors), m_descriptor_type(descriptor_type)
{
    if (!deduceProperties(descriptor_type)) {
        // ERROR no automatic translation : should throw an exception
        return;
    }
    //allocate buffer
    m_buffer->setSize(m_nb_descriptors * m_nb_elements * m_data_type);
}

DescriptorBuffer::DescriptorBuffer( unsigned char* descriptorData, DescriptorType descriptor_type, uint32_t nb_descriptors):
    m_buffer(new BufferInternal()), m_nb_descriptors(nb_descriptors), m_descriptor_type(descriptor_type)
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
            tmp_output[i] = static_cast<uint8_t>(tmp_data[i] + 0.5);
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
    for (size_t i = 0; i < output.size(); i++)
		output[i] = desc1_data[i] + desc2_data[i];
	return DescriptorBuffer(reinterpret_cast<uint8_t*>(output.data()), m_descriptor_type, TYPE_32F, m_nb_elements, m_nb_descriptors);
}

DescriptorBuffer DescriptorBuffer::operator*(float fac) const
{
	DescriptorBuffer desc = this->convertTo(TYPE_32F);
	float *desc_data = reinterpret_cast<float*>(desc.data());
	std::vector<float> output(m_nb_descriptors * m_nb_elements);
    for (size_t i = 0; i < output.size(); i++)
		output[i] = desc_data[i] * fac;
	return DescriptorBuffer(reinterpret_cast<uint8_t*>(output.data()), m_descriptor_type, TYPE_32F, m_nb_elements, m_nb_descriptors);
}

DescriptorBuffer DescriptorBuffer::operator/(float div) const
{
	DescriptorBuffer desc = this->convertTo(TYPE_32F);
	float *desc_data = reinterpret_cast<float*>(desc.data());
	std::vector<float> output(m_nb_descriptors * m_nb_elements);
    for (size_t i = 0; i < output.size(); i++)
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

namespace {

std::atomic<uint8_t> g_storage{static_cast<uint8_t>(DescriptorBuffer::Storage::FLOAT32)};

// IEEE 754 binary16, round to nearest even
uint16_t toHalfImpl(float value)
{
    uint32_t f;
    std::memcpy(&f, &value, 4);
    const uint32_t sign = (f >> 16) & 0x8000u;
    const uint32_t absf = f & 0x7FFFFFFFu;
    if (absf >= 0x7F800000u)                                   // inf, nan
        return uint16_t(sign | 0x7C00u | (absf > 0x7F800000u ? 0x200u : 0u));
    if (absf >= 0x477FF000u)                                   // overflow to inf
        return uint16_t(sign | 0x7C00u);
    if (absf < 0x38800000u) {                                  // subnormal or zero
        if (absf < 0x33000000u) return uint16_t(sign);
        const uint32_t mant = (absf & 0x7FFFFFu) | 0x800000u;
        const int shift = 126 - int(absf >> 23);
        const uint32_t half = mant >> shift, rest = mant & ((1u << shift) - 1u), mid = 1u << (shift - 1);
        return uint16_t(sign | (half + (rest > mid || (rest == mid && (half & 1u)))));
    }
    const uint32_t half = ((absf - 0x38000000u) >> 13), rest = absf & 0x1FFFu;
    return uint16_t(sign | (half + (rest > 0x1000u || (rest == 0x1000u && (half & 1u)))));
}

float fromHalfImpl(uint16_t h)
{
    const uint32_t sign = uint32_t(h & 0x8000u) << 16, exp = (h >> 10) & 0x1Fu, mant = h & 0x3FFu;
    uint32_t f;
    if (exp == 0) {
        if (mant == 0) f = sign;
        else {                                                 // subnormal
            int e = -1;
            uint32_t m = mant;
            do { m <<= 1; ++e; } while (!(m & 0x400u));
            f = sign | (uint32_t(112 - e) << 23) | ((m & 0x3FFu) << 13);
        }
    }
    else if (exp == 0x1F) f = sign | 0x7F800000u | (mant << 13);
    else f = sign | ((exp + 112) << 23) | (mant << 13);
    float value;
    std::memcpy(&value, &f, 4);
    return value;
}

} // namespace

uint16_t DescriptorBuffer::floatToHalf(float value) { return toHalfImpl(value); }
float DescriptorBuffer::halfToFloat(uint16_t half) { return fromHalfImpl(half); }

void DescriptorBuffer::setStorage(Storage storage)
{
    g_storage.store(static_cast<uint8_t>(storage));
}

DescriptorBuffer::Storage DescriptorBuffer::getStorage()
{
    return static_cast<Storage>(g_storage.load());
}

template<typename Archive>
void DescriptorBuffer::serialize(Archive &ar, const unsigned int version) {
    uint8_t storage = static_cast<uint8_t>(Storage::FLOAT32);
    const size_t count = size_t(m_nb_descriptors) * m_nb_elements;
    if constexpr (Archive::is_saving::value) {
        // only float buffers holding their descriptors are encoded
        if (m_data_type == DescriptorDataType::TYPE_32F && m_buffer && count > 0 && m_buffer->getSize() >= count * sizeof(float))
            storage = g_storage.load();
    }
    if (version >= 1)
        ar & storage;
    if (storage == static_cast<uint8_t>(Storage::FLOAT32)) {
        ar & m_buffer;
        ar & m_nb_descriptors;
        ar & m_data_type;
        ar & m_nb_elements;
        ar & m_descriptor_type;
        return;
    }
    ar & m_nb_descriptors;
    ar & m_data_type;
    ar & m_nb_elements;
    ar & m_descriptor_type;
    const size_t n = size_t(m_nb_descriptors) * m_nb_elements;
    if constexpr (Archive::is_saving::value) {
        const float* values = static_cast<const float*>(m_buffer->data());
        if (storage == static_cast<uint8_t>(Storage::FLOAT16)) {
            std::vector<uint16_t> halves(n);
            for (size_t i = 0; i < n; ++i) halves[i] = toHalfImpl(values[i]);
            ar & halves;
        }
        else {
            // one scale per descriptor: largest magnitude maps to 127
            std::vector<float> scales(m_nb_descriptors);
            std::vector<int8_t> codes(n);
            for (uint32_t d = 0; d < m_nb_descriptors; ++d) {
                const float* x = values + size_t(d) * m_nb_elements;
                float peak = 0.f;
                for (uint32_t e = 0; e < m_nb_elements; ++e) peak = std::max(peak, std::fabs(x[e]));
                scales[d] = peak / 127.f;
                const float inv = peak > 0.f ? 127.f / peak : 0.f;
                for (uint32_t e = 0; e < m_nb_elements; ++e)
                    codes[size_t(d) * m_nb_elements + e] = int8_t(std::lround(std::clamp(x[e] * inv, -127.f, 127.f)));
            }
            ar & scales;
            ar & codes;
        }
    }
    else {
        m_buffer = org::bcom::xpcf::utils::make_shared<BufferInternal>(uint32_t(n * sizeof(float)));
        float* values = static_cast<float*>(m_buffer->data());
        if (storage == static_cast<uint8_t>(Storage::FLOAT16)) {
            std::vector<uint16_t> halves;
            ar & halves;
            if (halves.size() != n)
                throw std::runtime_error("DescriptorBuffer: FLOAT16 payload size does not match the descriptor count");
            for (size_t i = 0; i < n; ++i) values[i] = fromHalfImpl(halves[i]);
        }
        else if (storage == static_cast<uint8_t>(Storage::INT8)) {
            std::vector<float> scales;
            std::vector<int8_t> codes;
            ar & scales;
            ar & codes;
            if (scales.size() != m_nb_descriptors || codes.size() != n)
                throw std::runtime_error("DescriptorBuffer: INT8 payload size does not match the descriptor count");
            for (size_t i = 0; i < n; ++i) values[i] = float(codes[i]) * scales[i / m_nb_elements];
        }
        else
            throw std::runtime_error("DescriptorBuffer: unknown descriptor storage in the archive");
        m_data_type = DescriptorDataType::TYPE_32F;
    }
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
