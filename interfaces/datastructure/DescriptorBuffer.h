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

#ifndef SOLAR_DESCRIPTORS_H
#define SOLAR_DESCRIPTORS_H

#include <utility>
#include <map>
#include <cstdint>

#include "xpcf/core/refs.h"
#include "core/SolARFrameworkDefinitions.h"
#include "BufferInternal.hpp"

#include <type_traits>
#include <core/SerializationDefinitions.h>

namespace SolAR {
namespace datastructure {

enum DescriptorDataType {
    TYPE_8U =1, /**< each descriptor element is stored in one byte. */
    TYPE_32F =4 /**< each descriptor element is stored in four bytes. */
} ;

// Note: a DescriptorType is based on one DataType only.
// i.e. AKAZE is always a TYPE_8U
enum DescriptorType{
    AKAZE, /**<AKAZE descriptor, assumes 61 elements per descriptor stores as one byte per element */
    SIFT,  /**<SIFT descriptor, assumes 128 elements per descriptor stores as four bytes per element*/
    SURF_64 , /**<SURF descriptor, assumes 64 elements per descriptor stores as four bytes per element*/
    SURF_128, /**<SURF descriptor, assumes 128 elements per descriptor stores as four bytes per element*/
    ORB, /**<ORB descriptor, assumes 32 elements per descriptor stores as one byte per element */
    SBPATTERN /**<Squared Binary Pattern descriptor, assumes nxn elements per descriptor stores as one byte per element, n is the size of the pattern */
};

template <class T> inline static constexpr DescriptorDataType inferDescriptorDataType();

template <> inline constexpr DescriptorDataType inferDescriptorDataType<uint8_t>()
{
    return DescriptorDataType::TYPE_8U;
}

template <> inline constexpr DescriptorDataType inferDescriptorDataType<float>()
{
    return DescriptorDataType::TYPE_32F;
}

template<DescriptorDataType>
struct inferType
{
    typedef void InnerType;
};

// Specialization for double: U -> double
template<>
struct inferType<DescriptorDataType::TYPE_8U>
{
    typedef uint8_t InnerType;
};

// Specialization for double: U -> double
template<>
struct inferType<DescriptorDataType::TYPE_32F>
{
    typedef float InnerType;
};

class SOLARFRAMEWORK_API DescriptorView {
public:
    DescriptorView(void * startAddress, uint32_t length, DescriptorType type);
    DescriptorView(const DescriptorView & desc) = default;
    DescriptorView(DescriptorView && desc) :
        m_baseAddress(std::exchange(desc.m_baseAddress, nullptr)),
        m_length(std::exchange(desc.m_length, 0)),
        m_dataType(std::exchange(desc.m_dataType, DescriptorDataType::TYPE_8U)) {}

    DescriptorView& operator= ( const DescriptorView & desc) = default;

    DescriptorView& operator= ( DescriptorView && desc)
    {
        m_baseAddress = std::exchange(desc.m_baseAddress, nullptr);
        m_length = std::exchange(desc.m_length, 0);
        m_dataType = std::exchange(desc.m_dataType, DescriptorDataType::TYPE_8U);
        return *this;
    }

    uint32_t length() const { return m_length; }
	void* data() { return m_baseAddress; }
    const void* data() const { return m_baseAddress; }
    const DescriptorType & type() const { return m_type; }
    const DescriptorDataType & dataType() const { return m_dataType; }

private:
    DescriptorDataType m_dataType;
    void * m_baseAddress;
    uint32_t m_length;
    DescriptorType m_type;
};



template<typename T>
class DescriptorViewTemplate {
public:
    DescriptorViewTemplate(T * startAddress, uint32_t length, DescriptorType type):m_length(length),m_baseAddress(startAddress), m_type(type) {}
    DescriptorViewTemplate(const DescriptorViewTemplate & desc) = default;
    DescriptorViewTemplate(DescriptorViewTemplate && desc) :
        m_baseAddress(std::exchange(desc.m_baseAddress, nullptr)),
        m_length(std::exchange(desc.m_length, 0)) {}

    DescriptorViewTemplate& operator= (const DescriptorViewTemplate & desc) = default;
    DescriptorViewTemplate& operator= ( DescriptorViewTemplate && desc)
    {
        m_baseAddress = std::exchange(desc.m_baseAddress, nullptr);
        m_length = std::exchange(desc.m_length, 0);
        return *this;
    }

    uint32_t length() const { return m_length; }
    const T* data() const { return m_baseAddress; }
	T* data() { return m_baseAddress; }
    DescriptorType type() const { return m_type; }

    static constexpr DescriptorDataType sDataType = inferDescriptorDataType<T>();

private:
    T * m_baseAddress;
    uint32_t m_length;
    DescriptorType m_type;
};

using DescriptorView8U = DescriptorViewTemplate<uint8_t>;
using DescriptorView32F = DescriptorViewTemplate<float>;

class DescriptorBuffer;
class SOLARFRAMEWORK_API DescriptorBufferIterator {
public:
    DescriptorBufferIterator(const SRef<DescriptorBuffer> & desc);

    void operator++() {
        if (m_index < m_nbDescriptors) {
            m_index ++;
        }
    }

    inline DescriptorView operator *();
    bool operator !=(const DescriptorBufferIterator & desc) {
        return (m_index != m_nbDescriptors);
    }

private:
    SRef<DescriptorBuffer> m_buffer;
    uint32_t m_index = 0;
    uint32_t m_nbDescriptors;
};

/**
* @class DescriptorBuffer
* @brief <B>A buffer to store a set of descriptors.</B>
*
* This class provides an descriptor buffer structure
*/
class SOLARFRAMEWORK_API DescriptorBuffer{

public :
    DescriptorBuffer( const DescriptorView8U & desc);
    DescriptorBuffer( const DescriptorView32F & desc);
    DescriptorBuffer( const DescriptorView & desc);

    /** @brief  DescriptorBuffer
    *  @param descriptor_type: enum to describe the descriptors vector
    *  @param nb_descriptors: the number of descriptors stored in the buffer
    *  @note the data type and the number of elements are deduced from the descriptor type, except for SBPATTERN.
    * For SBPATTERN descriptors, use another constructor to provide the number of elements !
    * The data are copied to get full ownership of the memory allocation.
    */
    DescriptorBuffer( DescriptorType descriptor_type, uint32_t nb_descriptors);

    /** @brief  DescriptorBuffer
    *  @param descriptorData: pointer to an existing array structure
    *  @param descriptor_type: enum to describe the descriptors vector
    *  @param nb_descriptors: the number of descriptors stored in the buffer
    * The data are copied to get full ownership of the memory allocation.
    */
    DescriptorBuffer( unsigned char* descriptorData, DescriptorType descriptor_type, uint32_t nb_descriptors);

    /** @brief  DescriptorBuffer
    *  @param descriptorData: pointer to an existing array structure
    *  @param descriptor_type: enum to describe the descriptors vector
    *  @param data_type: number of bits per descriptor element
    *  @param nb_elements: number of elements per descriptor
    *  @param nb_descriptors: the number of descriptors stored in the buffer
    * The data are copied to get full ownership of the memory allocation.
    */
    DescriptorBuffer( unsigned char* descriptorData, DescriptorType descriptor_type, DescriptorDataType data_type, uint32_t nb_elements, uint32_t nb_descriptors);


    /** @brief  DescriptorBuffer
    *  @param descriptor_type: enum to describe the descriptors vector
    *  @param data_type: number of bits per descriptor element
    *  @param nb_elements: number of elements per descriptor
    *  @param nb_descriptors: the number of descriptors stored in the buffer
    * The data are copied to get full ownership of the memory allocation.
    */
    DescriptorBuffer( DescriptorType descriptor_type, DescriptorDataType data_type, uint32_t nb_elements, uint32_t nb_descriptors);

    /** @brief  DescriptorBuffer
    * default constructor
    */
    DescriptorBuffer();

    ~DescriptorBuffer() = default;

    /** @brief  return the number of descriptors stored in the structure
    */
    inline uint32_t getNbDescriptors(void) const{
        return m_nb_descriptors;
    }

    /** @brief  return the type of descriptor
    */
    inline enum DescriptorType getDescriptorType() const{
        return m_descriptor_type;
    }

    /** @brief  return the number of elements per descriptor
    */
    inline uint32_t getNbElements(void) const{
        return m_nb_elements;
    }

    /** @brief  return the internal storage type of descriptor
    */
    inline enum DescriptorDataType getDescriptorDataType() const
    {
        return m_data_type;
    }

    /** @brief  return the descriptor size in bytes
    */
    inline uint32_t getDescriptorByteSize(void) const
    {
        return m_nb_elements * m_data_type;
    }

    void append(const DescriptorView & descriptor);
    void append(const DescriptorView8U & descriptor);
    void append(const DescriptorView32F & descriptor);

	DescriptorBuffer convertTo(DescriptorDataType type) const;
	DescriptorBuffer operator+ (const DescriptorBuffer &desc) const;
	DescriptorBuffer operator* (float fac) const;
	DescriptorBuffer operator/ (float div) const;


    DescriptorView getDescriptor(uint32_t index) const;

    //TO DO: access to a single Descriptor
    // Descriptor getADescriptor(uint32_t idDescriptor);
    template <DescriptorDataType datatype, typename T = typename inferType<datatype>::InnerType>
    DescriptorViewTemplate<T> getDescriptor(uint32_t index);

    void* data();

    const void* data() const;

private:
    bool deduceProperties(const DescriptorType & type);

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version);

private:
    SRef<BufferInternal> m_buffer;
    uint32_t m_nb_descriptors;
    DescriptorDataType m_data_type;
    uint32_t m_nb_elements;
    DescriptorType m_descriptor_type;
};
DECLARESERIALIZE(DescriptorBuffer);


inline DescriptorBufferIterator begin(const SRef<DescriptorBuffer> & ref)
{
    return DescriptorBufferIterator(ref);
}

inline DescriptorBufferIterator end(const SRef<DescriptorBuffer> & ref)
{
    return DescriptorBufferIterator(ref);
}

template <DescriptorDataType datatype, typename T> DescriptorViewTemplate<T> DescriptorBuffer::getDescriptor(uint32_t index)
{
    static_assert (std::is_same<std::uint8_t,T>::value || std::is_same<std::float_t, T>::value,
                   "getDescriptor() only works for T = uint8_t or T = float" );
    T* pDescriptor = static_cast<T*>(data());
    return DescriptorViewTemplate<T>(&pDescriptor[index * m_nb_elements], m_nb_elements, m_descriptor_type);
}

template <DescriptorDataType datatype, typename T = typename inferType<datatype>::InnerType>
DescriptorViewTemplate<T> getDescriptor(const SRef<DescriptorBuffer> buffer, uint32_t index)
{
    static_assert (std::is_same<std::uint8_t,T>::value || std::is_same<std::float_t, T>::value,
                   "getDescriptor() only works for T = uint8_t or T = float" );
    if (buffer->getDescriptorDataType() != sizeof (T)) {
        // throw exception
    }
    T* pDescriptor = static_cast<T*>(buffer->data());
    return DescriptorViewTemplate<T>(&pDescriptor[index * buffer->getNbElements()], buffer->getNbElements(), buffer->getDescriptorType());
}

}
}

#endif //SOLAR_DESCRIPTORS_H
