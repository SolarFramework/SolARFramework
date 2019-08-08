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

namespace SolAR {
namespace datastructure {

/**
* @class DescriptorBuffer
* @brief <B>A buffer to store a set of descriptors.</B>
*
* This class provides an descriptor buffer structure
*/
class SOLARFRAMEWORK_API DescriptorBuffer{

public :
    enum DescriptorType{
        AKAZE, /**<AKAZE descriptor, assumes 32 elements per descriptor stores as one byte per element */
        SIFT,  /**<SIFT descriptor, assumes 128 elements per descriptor stores as four bytes per element*/
        SURF_64 , /**<SURF descriptor, assumes 64 elements per descriptor stores as four bytes per element*/
        SURF_128, /**<SURF descriptor, assumes 128 elements per descriptor stores as four bytes per element*/
        ORB, /**<ORB descriptor, assumes 32 elements per descriptor stores as one byte per element */
        SBPATTERN /**<Squared Binary Pattern descriptor, assumes nxn elements per descriptor stores as one byte per element, n is the size of the pattern */
    };

    enum DataType {
        TYPE_8U =1, /**< each descriptor element is stored in one byte. */
        TYPE_32F =4 /**< each descriptor element is stored in four bytes. */
	} ;

    /** @brief  DescriptorBuffer
	*  @param descriptorData: pointer to an existing array structure
    *  @param descriptor_type: enum to describe the descriptors vector
    *  @param data_type: number of bits per descriptor element
    *  @param nb_elements: number of elements per descriptor
    *  @param nb_descriptors: the number of descriptors stored in the buffer
	* The data are copied to get full ownership of the memory allocation.
	*/
    DescriptorBuffer( unsigned char* descriptorData, DescriptorType descriptor_type, DataType data_type, uint32_t nb_elements, uint32_t nb_descriptors);

    /** @brief  DescriptorBuffer
    *  @param descriptor_type: enum to describe the descriptors vector
    *  @param data_type: number of bits per descriptor element
    *  @param nb_elements: number of elements per descriptor
    *  @param nb_descriptors: the number of descriptors stored in the buffer
    * The data are copied to get full ownership of the memory allocation.
    */
    DescriptorBuffer( DescriptorType descriptor_type, DataType data_type, uint32_t nb_elements, uint32_t nb_descriptors);


    /** @brief  DescriptorBuffer
	* default constructor
	*/
    DescriptorBuffer();

	/** @brief  return the number of descriptors stored in the structure
	*/
    uint32_t getNbDescriptors() const {
        return m_nb_descriptors;
    }

	/** @brief  return the type of descriptor 
	*/
    DescriptorType getDescriptorType() const {
        return m_descriptor_type;
    }

    /** @brief  return the number of elements per descriptor
    */
    uint32_t getNbElements() const {
        return m_nb_elements;
    }

	/** @brief  return the internal storage type of descriptor
	*/
    DataType getDescriptorDataType() const
    {
        return m_data_type;
    }

    /** @brief  return the descriptor size in bytes
	*/
    uint32_t getDescriptorByteSize() const
    {
        return m_nb_elements * m_data_type;
    }

    //TO DO: access to a single Descriptor
   // Descriptor getADescriptor(uint32_t idDescriptor);

    /** @brief  return the descriptor data
    */
    void* data();

    /** @brief  return the descriptor data
    */
    const void* data() const;

private:
    std::vector<uint8_t> m_buffer;
    uint32_t m_nb_descriptors;
    DataType m_data_type;
    uint32_t m_nb_elements;
    DescriptorType m_descriptor_type;
};

}
}

#endif //SOLAR_DESCRIPTORS_H
