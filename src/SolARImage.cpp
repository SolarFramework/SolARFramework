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

#include "SolARImage.h"
#include <vector>
#include <map>

namespace SolAR {

template <class T>
class SolARImageContainer {
    SolARImageContainer() = default;
    ~SolARImageContainer() = default;
    void initialize(SolARImage::DataType type);
};


class SolARImage::SolARImageInternal {
public:
    SolARImageInternal() = default;
    SolARImageInternal(uint32_t size);
    SolARImageInternal(void* data, uint32_t size);
    ~SolARImageInternal() = default;
    void setSize(uint32_t size);
    inline uint32_t getSize() { return m_bufferSize; }
    void setData(void * data, uint32_t size);
    inline void* data() { return m_storageData.data(); }
    inline const void* data() const  { return m_storageData.data(); }

private:
    std::vector<uint8_t> m_storageData;
    uint32_t m_bufferSize = 0;
};

SolARImage::SolARImageInternal::SolARImageInternal(uint32_t size)
{
    setSize(size);
}

SolARImage::SolARImageInternal::SolARImageInternal(void* data,uint32_t size)
{
   setData(data,size);
}

void SolARImage::SolARImageInternal::setSize(uint32_t size)
{
    m_bufferSize = size;
    if (m_bufferSize == 0) { // invalid size
        return;
    }
    m_storageData.reserve(m_bufferSize);
    memset(m_storageData.data(),0,m_bufferSize);
}

void SolARImage::SolARImageInternal::setData(void * data, uint32_t size)
{
    if (m_bufferSize < size) {
        setSize(size);
    }
    m_storageData.insert(m_storageData.begin(), static_cast<uint8_t *>(data), static_cast<uint8_t *>(data) + m_bufferSize-1);
}


static std::map<SolARImage::ImageLayout,uint32_t> layoutChannelMapInfos = {{SolARImage::ImageLayout::LAYOUT_RGB,3},
                                                                           {SolARImage::ImageLayout::LAYOUT_GRB,3},
                                                                           {SolARImage::ImageLayout::LAYOUT_BGR,3},
                                                                           {SolARImage::ImageLayout::LAYOUT_GREY,1},
                                                                           {SolARImage::ImageLayout::LAYOUT_RGBA,4},
                                                                           {SolARImage::ImageLayout::LAYOUT_RGBX,4}};

static std::map<SolARImage::DataType,uint32_t> typeSizeMapInfos = {{SolARImage::DataType::TYPE_8U,8},
                                                                      {SolARImage::DataType::TYPE_16U,16},
                                                                      {SolARImage::DataType::TYPE_32U,32},
                                                                      {SolARImage::DataType::TYPE_64U,64}};
//Add stride notion
// Hypothese : pas de bits per component : only full format image YUV444, RGB888, RGB 555 but not YUV420, RGB565 and so on or YUV422 with splatting

uint32_t SolARImage::computeImageBufferSize()
{
    return m_width * m_height * m_nbChannels * (m_nbBitsPerComponent/8);
}

SolARImage::SolARImage(enum ImageLayout imgLayout, enum PixelOrder pixOrder, DataType type):m_layout(imgLayout),m_pixOrder(pixOrder),m_type(type),m_internalImpl(new SolARImageInternal())
{
    m_nbChannels = layoutChannelMapInfos.at(m_layout);
    m_nbBitsPerComponent = typeSizeMapInfos.at(m_type);
    m_nbPlanes = 1;
    if (m_pixOrder == PixelOrder::PER_CHANNEL) {
        m_nbPlanes = m_nbChannels;
    }
}

SolARImage::SolARImage(uint32_t width, uint32_t height, enum ImageLayout imgLayout, enum PixelOrder pixOrder, DataType type):SolARImage(imgLayout,pixOrder,type)
{
    setSize(width,height);
}

// initialize image from external pointer data.
// note : data is copied to take full ownership and ensure deallocation will occur in the same scope allocation was made

SolARImage::SolARImage(void* imageData, uint32_t width, uint32_t height, enum ImageLayout imgLayout, enum PixelOrder pixOrder, DataType type):SolARImage(width, height, imgLayout, pixOrder,type)
{
    m_internalImpl->setData(imageData,computeImageBufferSize());
}

// reserve new space depending on the image layers and bitspercomponent infos
// TODO handle bad size error : add return code
void SolARImage::setSize(uint32_t width, uint32_t height)
{
    m_width = width;
    m_height = height;
    m_internalImpl->setSize(computeImageBufferSize());
}

uint32_t SolARImage::getSize()
{
    return m_internalImpl->getSize();
}


void* SolARImage::data()
{
    return m_internalImpl->data();
}


const void* SolARImage::data() const
{
    return m_internalImpl->data();
}

//image creation from opencv conversion ... : howto handle memory allocation locality : factory ?
// conversion from/to opencv for instance : how to handle the T* type while bound to void* ?
}


