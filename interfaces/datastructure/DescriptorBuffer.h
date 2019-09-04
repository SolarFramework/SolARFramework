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

namespace SolAR {
namespace datastructure {

enum DescriptorDataType {
    TYPE_8U =1, /**< each descriptor element is stored in one byte. */
    TYPE_32F =4 /**< each descriptor element is stored in four bytes. */
} ;

// Note: a DescriptorType is based on one DataType only.
// i.e. AKAZE is always a TYPE_8U
enum DescriptorType{
    AKAZE, /**<AKAZE descriptor, assumes 32 elements per descriptor stores as one byte per element */
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

class DescriptorBase {
public:
    DescriptorBase(void * startAddress, uint32_t length, DescriptorType type);
    DescriptorBase(DescriptorBase && desc) :
        m_baseAddress(std::exchange(desc.m_baseAddress, nullptr)),
        m_length(std::exchange(desc.m_length, 0)),
        m_dataType(std::exchange(desc.m_dataType, DescriptorDataType::TYPE_8U)) {}

    DescriptorBase& operator= ( DescriptorBase && desc)
    {
        m_baseAddress = std::exchange(desc.m_baseAddress, nullptr);
        m_length = std::exchange(desc.m_length, 0);
        m_dataType = std::exchange(desc.m_dataType, DescriptorDataType::TYPE_8U);
        return *this;
    }

    uint32_t length() const { return m_length; }
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
class Descriptor {
public:
    Descriptor(T * startAddress, uint32_t length, DescriptorType type):m_length(length),m_baseAddress(startAddress), m_type(type) {}

    Descriptor(Descriptor && desc) :
        m_baseAddress(std::exchange(desc.m_baseAddress, nullptr)),
        m_length(std::exchange(desc.m_length, 0)) {}

    Descriptor& operator= ( Descriptor && desc)
    {
        m_baseAddress = std::exchange(desc.m_baseAddress, nullptr);
        m_length = std::exchange(desc.m_length, 0);
        return *this;
    }

    uint32_t length() const { return m_length; }
    const T* data() const { return m_baseAddress; }
    DescriptorType type() const { return m_type; }

    static constexpr DescriptorDataType sDataType = inferDescriptorDataType<T>();

private:
    T * m_baseAddress;
    uint32_t m_length;
    DescriptorType m_type;
};

using Descriptor8U = Descriptor<uint8_t>;
using Descriptor32F = Descriptor<float>;

/**
* @class DescriptorBuffer
* @brief <B>A buffer to store a set of descriptors.</B>
*
* This class provides an descriptor buffer structure
*/
class SOLARFRAMEWORK_API DescriptorBuffer{

public :
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

    DescriptorBuffer( const Descriptor8U & desc);
    DescriptorBuffer( const Descriptor32F & desc);

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
    inline uint32_t getNbDescriptors(void){
        return m_nb_descriptors;
    }

    /** @brief  return the type of descriptor
    */
    inline enum DescriptorType getDescriptorType(){
        return m_descriptor_type;
    }

    /** @brief  return the number of elements per descriptor
    */
    inline uint32_t getNbElements(void){
        return m_nb_elements;
    }

    /** @brief  return the internal storage type of descriptor
    */
    inline enum DescriptorDataType getDescriptorDataType()
    {
        return m_data_type;
    }

    /** @brief  return the descriptor size in bytes
    */
    inline uint32_t getDescriptorByteSize(void)
    {
        return m_nb_elements * m_data_type;
    }

    void append(const Descriptor8U & descriptor);
    void append(const Descriptor32F & descriptor);
    void append(const DescriptorBase & descriptor);

    DescriptorBase getDescriptor(uint32_t index);

    //TO DO: access to a single Descriptor
    // Descriptor getADescriptor(uint32_t idDescriptor);
    template <DescriptorDataType datatype, typename T = typename inferType<datatype>::InnerType>
    Descriptor<T> getDescriptor(uint32_t index);

    void* data();

    const void* data() const;

private:
    bool deduceProperties(const DescriptorType & type);
    SRef<BufferInternal> m_buffer;
    uint32_t m_nb_descriptors;
    DescriptorDataType m_data_type;
    uint32_t m_nb_elements;
    DescriptorType m_descriptor_type;
};

template <DescriptorDataType datatype, typename T> Descriptor<T> DescriptorBuffer::getDescriptor(uint32_t index)
{
    static_assert (std::is_same<std::uint8_t,T>::value || std::is_same<std::float_t, T>::value,
                   "getDescriptor() only works for T = uint8_t or T = float" );
    T* pDescriptor = static_cast<T*>(data());
    return Descriptor<T>(&pDescriptor[index], m_nb_elements, m_descriptor_type);
}



template <DescriptorDataType datatype, typename T = typename DescriptorBuffer::inferType<datatype>::InnerType>
Descriptor<T> getDescriptor(const SRef<DescriptorBuffer> buffer, uint32_t index)
{
    static_assert (std::is_same<std::uint8_t,T>::value || std::is_same<std::float_t, T>::value,
                   "getDescriptor() only works for T = uint8_t or T = float" );
    if (buffer->getDescriptorDataType() != sizeof (T)) {
        // throw exception
    }
    T* pDescriptor = static_cast<T*>(buffer->data());
    return Descriptor<T>(&pDescriptor[index], buffer->getNbElements(), buffer->getDescriptorType());
}

}
}

#endif //SOLAR_DESCRIPTORS_H
