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


#ifndef SOLAR_BUFFERINTERNAL_H
#define SOLAR_BUFFERINTERNAL_H
#include <cstdint>

#include <core/SerializationDefinitions.h>

namespace SolAR {
namespace datastructure {

/**
 * @class BufferInternal
 * @brief <B>A Buffer used to store any data such as descriptors.</B>
 */

class BufferInternal {
public:
    BufferInternal() = default;

    explicit BufferInternal(uint32_t size)
    {
        setSize(size);
    }

    BufferInternal(void* data, uint32_t size)
    {
       setData(data,size);

    }
    ~BufferInternal() = default;
    void setSize(uint32_t size)
    {
        m_bufferSize = size;
        if (m_bufferSize == 0) { // invalid size
            return;
        }
        // The reserve + memset do no really create the elements.
        m_storageData.resize(m_bufferSize);
        /*
        m_storageData.reserve(m_bufferSize);
        memset(m_storageData.data(),0,m_bufferSize);
        */
    }

    inline uint32_t getSize() { return m_bufferSize; }

    void setData (void * data, uint32_t size){
        if (m_bufferSize < size) {
            setSize(size);
        }
        m_storageData.insert(m_storageData.begin(), static_cast<uint8_t *>(data), static_cast<uint8_t *>(data) + m_bufferSize);
    }

    void appendData (const void * data, uint32_t size){
        uint32_t endOffset = m_bufferSize;
        setSize(m_bufferSize + size);
        auto startIt = std::next(m_storageData.begin(), endOffset);
        m_storageData.insert(startIt, static_cast<const uint8_t *>(data), static_cast<const uint8_t *>(data) + size);
    }

    inline void* data() { return m_storageData.data(); }
    inline const void* data() const  { return m_storageData.data(); }

private:
	friend class boost::serialization::access;
	template<class Archive>
    void serialize(Archive &ar, [[maybe_unused]] const unsigned int version) {
		ar & m_storageData;
		ar & m_bufferSize;
	}

private:
    std::vector<uint8_t> m_storageData;
    uint32_t m_bufferSize = 0;

};

}
}

#endif // SOLAR_BUFFERINTERNAL_H
