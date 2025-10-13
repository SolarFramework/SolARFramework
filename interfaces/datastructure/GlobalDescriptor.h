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
#include <optional>

namespace SolAR {
namespace datastructure {

/**
 * @enum global image descriptor type
*/
enum class GlobalDescriptorType {
    NETVLAD, /**< NetVLAD image descriptor */
    BOQ, /**< Bag-Of-QUeries image descriptor */
    UNDEFINED,
};

/// @brief Return the text definition (string) of a GlobalDescriptorType object
/// @param[in] globalDescriptorType the global descriptor type
/// @return the text definition (string)
static std::string toString(const GlobalDescriptorType globalDescriptorType)
{
    std::string textDefinition = "";

    switch (globalDescriptorType) {
        case GlobalDescriptorType::NETVLAD:
            textDefinition = "NETVLAD";
            break;
        case GlobalDescriptorType::BOQ:
            textDefinition = "BOQ";
            break;
        case GlobalDescriptorType::UNDEFINED:
            textDefinition = "UNDEFINED";
            break;
        default:
            textDefinition = "Unknown value";
            break;
    }

    return textDefinition;
}

/// @brief Return the GlobalDescriptorType object from a text definition (string)
/// @param[in] textDefinition the text definition (string)
/// @return the global descriptor type
static std::optional<GlobalDescriptorType> parseGlobalDescriptorType(const std::string textDefinition)
{
    if (textDefinition == "NETVLAD") return GlobalDescriptorType::NETVLAD;
    if (textDefinition == "BOQ") return GlobalDescriptorType::BOQ;
    if (textDefinition == "UNDEFINED") return GlobalDescriptorType::UNDEFINED;

    LOG_ERROR("Unknown global descriptor type: {}", textDefinition);

    return {};
}


/**
 * @enum data type of the global image descriptor 
*/
enum class GlobalDescriptorDataType : size_t {
    TYPE_8U = 1,  /**< each global descriptor is stored in one byte. */
    TYPE_32F = 4, /**< each global descriptor is stored in four bytes. */
};

/// @brief Return the text definition (string) of a GlobalDescriptorDataType object
/// @param[in] globalDescriptorDataType the global descriptor data type
/// @return the text definition (string)
static std::string toString(const GlobalDescriptorDataType globalDescriptorDataType)
{
    std::string textDefinition = "";

    switch (globalDescriptorDataType) {
        case GlobalDescriptorDataType::TYPE_8U:
                textDefinition = "TYPE_8U";
                break;
        case GlobalDescriptorDataType::TYPE_32F:
                textDefinition = "TYPE_32F";
                break;
        default:
                textDefinition = "Unknown value";
                break;
    }

    return textDefinition;
}

/**
 * @class global image descriptor
*/
class SOLARFRAMEWORK_API GlobalDescriptor {
public:
    /**
     * @brief builder of global descriptor 
     * @param[in] type global descriptor type 
     * @param[in] buffer data pointer 
     * @return GlobalDescriptor object if success, otherwise std::nullopt 
    */
    static std::optional<GlobalDescriptor> build(GlobalDescriptorType type, unsigned char* buffer);

    /**
     * @brief build shared ref of global descriptor
     * @param[in] type global descriptor type 
     * @param[in] buffer data pointer 
     * @return shared ref of GlobalDescriptor if success, otherwise nullptr
    */
    static SRef<GlobalDescriptor> buildSharedRef(GlobalDescriptorType type, unsigned char* buffer);

    /**
     * @brief length of the descriptor, i.e. number of elements stored in the global descriptor
     * @return number of elements in the global descriptor 
    */
    size_t getLength() const;

    /**
     * @brief const pointer to the descriptor buffer
     * @return const pointer to the descriptor buffer 
    */
    const unsigned char* data() const;

    /**
     * @brief non-const pointer to the descriptor buffer
     * @return non-const pointer to data buffer 
    */
    unsigned char* data();

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

    /**
     * @brief check if content is valid
     * @return boolean
    */
    bool isValid(); 

private:
    /**
     * @brief default constructor 
    */
    GlobalDescriptor() = default;

    /**
     * @brief constructor with input arguments
     * @param[in] type: global descriptor type 
     * @param[in] dtype: data type of global descriptor 
     * @param[in] buffer: input buffer 
     * @param[in] len: length of the descriptor (number of elements)
    */
    GlobalDescriptor(GlobalDescriptorType type, GlobalDescriptorDataType dtype, unsigned char* buffer, size_t len);

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
