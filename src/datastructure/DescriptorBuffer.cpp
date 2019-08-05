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

    DescriptorBuffer::DescriptorBuffer(){
     m_descriptor_type = DescriptorBuffer::DescriptorType::SIFT;
     m_nb_elements = 128;
     m_data_type = DataType::TYPE_32F;
     m_nb_descriptors= 0;
    }

    DescriptorBuffer::DescriptorBuffer( unsigned char* descriptorData, enum DescriptorType descriptor_type, DataType data_type, uint32_t nb_elements, uint32_t nb_descriptors){
      m_descriptor_type = descriptor_type;
      m_nb_descriptors= nb_descriptors;
      m_data_type = data_type;
      m_nb_elements = nb_elements;
      //allocate buffer and fill buffer
      auto size = m_nb_descriptors * m_nb_elements * m_data_type;
      m_buffer.resize(size);
      m_buffer.insert(m_buffer.begin(), static_cast<uint8_t *>(descriptorData), static_cast<uint8_t *>(descriptorData) + size);
    }

    DescriptorBuffer::DescriptorBuffer( enum DescriptorType descriptor_type, DataType data_type, uint32_t nb_elements, uint32_t nb_descriptors){
      m_descriptor_type = descriptor_type;
      m_nb_descriptors= nb_descriptors;
      m_data_type = data_type;
      m_nb_elements = nb_elements;
      //allocate buffer
      m_buffer.resize(m_nb_descriptors * m_nb_elements * m_data_type);
    }

    void* DescriptorBuffer::data()
    {
        return m_buffer.data();
    }

    const void* DescriptorBuffer::data() const
    {
        return m_buffer.data();
    }

}
}
