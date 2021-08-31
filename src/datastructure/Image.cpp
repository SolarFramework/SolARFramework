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

#include "datastructure/Image.h"
#include <vector>
#include <map>

#include "xpcf/core/helpers.h"

#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>;

namespace xpcf  = org::bcom::xpcf;
using namespace org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

/**
 * @class Image::ImageInternal
 * @brief <B>A 2D image buffer.</B>.
 *
 */
class Image::ImageInternal {
public:
    ImageInternal() = default;
    explicit ImageInternal(uint32_t size);
    explicit ImageInternal(void* data, uint32_t size);
    ~ImageInternal() = default;
    void setBufferSize(uint32_t size);
    inline uint32_t getBufferSize() { return m_bufferSize; }
    void setData(void * data, uint32_t size);
    inline void* data() { return m_storageData.data(); }
    inline const void* data() const  { return m_storageData.data(); }

private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version);

private:
    std::vector<uint8_t> m_storageData;
    uint32_t m_bufferSize = 0;
};

DECLARESERIALIZE(Image::ImageInternal);

Image::ImageInternal::ImageInternal(uint32_t size)
{
    setBufferSize(size);
}

Image::ImageInternal::ImageInternal(void* data,uint32_t size)
{
   setData(data,size);
}

void Image::ImageInternal::setBufferSize(uint32_t size)
{
    m_bufferSize = size;
    if (m_bufferSize == 0) { // invalid size
        return;
    }
    m_storageData.reserve(m_bufferSize);
    m_storageData.resize(m_bufferSize);
    //memset(m_storageData.data(),0,m_bufferSize); // Normally not useful
}

void Image::ImageInternal::setData(void * data, uint32_t size)
{
    if (m_bufferSize < size) {
        setBufferSize(size);
    }
    m_storageData.insert(m_storageData.begin(), static_cast<uint8_t *>(data), static_cast<uint8_t *>(data) + m_bufferSize);
}

template<typename Archive>
void Image::ImageInternal::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {

    ar & m_storageData;
    ar & m_bufferSize;
}

IMPLEMENTSERIALIZE(Image::ImageInternal);

static std::map<Image::ImageLayout,uint32_t> layoutChannelMapInfos = {{Image::ImageLayout::LAYOUT_RGB,3},
                                                                           {Image::ImageLayout::LAYOUT_GRB,3},
                                                                           {Image::ImageLayout::LAYOUT_BGR,3},
                                                                           {Image::ImageLayout::LAYOUT_GREY,1},
                                                                           {Image::ImageLayout::LAYOUT_RGBA,4},
                                                                           {Image::ImageLayout::LAYOUT_RGBX,4}};

static std::map<Image::DataType,uint32_t> typeSizeMapInfos = {{Image::DataType::TYPE_8U,8},
                                                                      {Image::DataType::TYPE_16U,16},
                                                                      {Image::DataType::TYPE_32U,32},
                                                                      {Image::DataType::TYPE_64U,64}};
//Add stride notion
// Hypothese : pas de bits per component : only full format image YUV444, RGB888, RGB 555 but not YUV420, RGB565 and so on or YUV422 with splatting

uint32_t Image::computeImageBufferSize()
{
    return m_size.width * m_size.height * m_nbChannels * (m_nbBitsPerComponent/8);
}

Image::Image(enum ImageLayout imgLayout, enum PixelOrder pixOrder, DataType type):m_layout(imgLayout),m_pixOrder(pixOrder),m_type(type),m_internalImpl(new ImageInternal())
{
    m_nbChannels = layoutChannelMapInfos.at(m_layout);
    m_nbBitsPerComponent = typeSizeMapInfos.at(m_type);
    m_nbPlanes = 1;
    if (m_pixOrder == PixelOrder::PER_CHANNEL) {
        m_nbPlanes = m_nbChannels;
    }
}

Image::Image(uint32_t width, uint32_t height, enum ImageLayout imgLayout, enum PixelOrder pixOrder, DataType type):Image(imgLayout,pixOrder,type)
{
    setSize(width,height);
}

// initialize image from external pointer data.
// note : data is copied to take full ownership and ensure deallocation will occur in the same scope allocation was made

Image::Image(void* imageData, uint32_t width, uint32_t height, enum ImageLayout imgLayout, enum PixelOrder pixOrder, DataType type):Image(width, height, imgLayout, pixOrder,type)
{
    m_internalImpl->setData(imageData,computeImageBufferSize());
}

SRef<Image> Image::copy() const
{
    // NB : maybe we should consider redefining the image copy constructor
    return xpcf::utils::make_shared<Image>(m_internalImpl->data(), m_size.width, m_size.height, m_layout, m_pixOrder, m_type);
}

// reserve new space depending on the image layers and bitspercomponent infos
// TODO handle bad size error : add return code
void Image::setSize(uint32_t width, uint32_t height)
{
    m_size.width = width;
    m_size.height = height;
    m_internalImpl->setBufferSize(computeImageBufferSize());
}

// reserve new space depending on the image layers and bitspercomponent infos
// TODO handle bad size error : add return code
void Image::setSize(Sizei size)
{
    m_size = size;
    m_internalImpl->setBufferSize(computeImageBufferSize());
}


uint32_t Image::getBufferSize()
{
    return m_internalImpl->getBufferSize();
}


void* Image::data()
{
    return m_internalImpl->data();
}


const void* Image::data() const
{
    return m_internalImpl->data();
}

template<typename Archive>
void Image::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {

    ar & m_size;
    ar & m_layout;
    ar & m_pixOrder;
    ar & m_type;
    ar & m_nbChannels;
    ar & m_nbPlanes;
    ar & m_nbBitsPerComponent;

    ar & m_internalImpl;
}

IMPLEMENTSERIALIZE(Image);
//image creation from opencv conversion ... : howto handle memory allocation locality : factory ?
// conversion from/to opencv for instance : how to handle the T* type while bound to void* ?
}
}

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::Image)
//BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::Image)
BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::Image::ImageInternal)
//BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::Image::ImageInternal)
BOOST_CLASS_TYPE_INFO(
SolAR::datastructure::Image::ImageInternal,
boost::serialization::extended_type_info_typeid<SolAR::datastructure::Image::ImageInternal>
)
