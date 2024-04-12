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

/** @file */

#ifndef SOLAR_GLOBALDESCRIPTOR_H
#define SOLAR_GLOBALDESCRIPTOR_H

#include <core/Messages.h>
#include <core/SerializationDefinitions.h>
#include <core/SolARFrameworkDefinitions.h>
#include <datastructure/DescriptorBuffer.h>

namespace SolAR {
namespace datastructure {

/**
 * @enum global image descriptor type of the frame
*/
enum class GlobalDescriptorType {
    NETVLAD, /**< NetVLAD image descriptor */
};

/**
 * @enum data type of the global image descriptor associated with the frame 
*/
enum class GlobalDescriptorDataType : size_t {
    TYPE_8U = 1,  /**< each global descriptor is stored in one byte. */
    TYPE_32F = 4, /**< each global descriptor is stored in four bytes. */
};

/**
 * @brief map from global descriptor type to expected size and data type 
*/
const static std::map<GlobalDescriptorType, std::pair<size_t, GlobalDescriptorDataType>> globalDescriptorToLengthType =
{
    {GlobalDescriptorType::NETVLAD, {4096, GlobalDescriptorDataType::TYPE_32F}}
};

/**
 * @class global image descriptor
*/
class SOLARFRAMEWORK_API GlobalDescriptor {
public:
    /**
     * @brief default constructor 
    */
    GlobalDescriptor() = default;

    /**
     * @brief set data
     * @param[in] type: global descriptor type 
     * @param[in] dtype: data type of global descriptor 
     * @param[in] buffer: input buffer 
     * @param[in] len: length of the descriptor (number of elements)
     * @return FrameworkReturnCode::_SUCCESS if succeeded, otherwise FrameworkReturnCode::_ERROR_
    */
    FrameworkReturnCode setData(GlobalDescriptorType type, GlobalDescriptorDataType dtype, unsigned char* buffer, size_t len);

    /**
     * @brief length of the descriptor, i.e. number of elements contained in the global descriptor
     * @return length 
    */
    size_t length() const;
    /**
     * @brief pointer to the descriptor buffer
     * @return data pointer to the descriptor buffer 
    */
    unsigned char* data() const;
    
    /**
     * @brief get descriptor type 
     * @return the type of global descriptor  
    */
    GlobalDescriptorType getType() const;
    
    /**
     * @brief get descriptor data type 
     * @return the data type of the global descriptor 
    */
    GlobalDescriptorDataType getDataType() const;

private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version);

private:
    GlobalDescriptorType m_type;
    GlobalDescriptorDataType m_dataType;
    SRef<BufferInternal> m_buffer;
    size_t m_length = 0;
};

DECLARESERIALIZE(GlobalDescriptor);

}
}

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::GlobalDescriptor);

#endif // SOLAR_GLOBALDESCRIPTOR_H
