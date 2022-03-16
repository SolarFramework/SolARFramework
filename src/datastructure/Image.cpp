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
#include <boost/serialization/vector.hpp>

//#include "opencv2/imgcodecs.hpp"
#include <opencv2/opencv.hpp>

namespace xpcf  = org::bcom::xpcf;
using namespace org::bcom::xpcf;

namespace SolAR {
namespace datastructure {

ImageInternal::ImageInternal(uint32_t size)
{
    setBufferSize(size);
}

ImageInternal::ImageInternal(void* data,uint32_t size)
{
   setData(data,size);
}

void ImageInternal::setBufferSize(uint32_t size)
{
    m_bufferSize = size;
    if (m_bufferSize == 0) { // invalid size
        return;
    }
    m_storageData.reserve(m_bufferSize);
    m_storageData.resize(m_bufferSize);
}

void ImageInternal::setData(void * data, uint32_t size)
{
    setBufferSize(size);

    m_storageData.clear();
    m_storageData.insert(m_storageData.begin(), static_cast<uint8_t *>(data), static_cast<uint8_t *>(data) + m_bufferSize);
}

template<typename Archive>
void ImageInternal::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version)
{
    ar & m_storageData;
    ar & m_bufferSize;
}

IMPLEMENTSERIALIZE(ImageInternal);

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

void Image::setImageEncoding(enum ImageEncoding encoding)
{
    m_imageEncoding = encoding;

    // JPEG: set quality to 95 by default
    if (m_imageEncoding == ENCODING_JPEG) {
        m_imageEncodingQuality = 95;
    }
    // PNG: set quality to 9 by default
    if (m_imageEncoding == ENCODING_PNG) {
        m_imageEncodingQuality = 9;
    }
}

void Image::setImageEncodingQuality(uint8_t encodingQuality)
{
    // JPEG quality between 0 and 100
    if (m_imageEncoding == ENCODING_JPEG) {
        if (encodingQuality <= 100) {
            m_imageEncodingQuality = encodingQuality;
        }
    }
    // PNG quality between 0 and 9
    else if (m_imageEncoding == ENCODING_PNG) {
        if (encodingQuality <= 9) {
            m_imageEncodingQuality = encodingQuality;
        }
    }
}

static std::map<std::tuple<uint32_t,std::size_t,uint32_t>,int> solar2cvTypeConvertMap =
{
    {std::make_tuple(8,1,3),CV_8UC3},
    {std::make_tuple(8,1,1),CV_8UC1},
    {std::make_tuple(16,1,1),CV_16UC1}
};

static std::map<int,std::pair<Image::ImageLayout,Image::DataType>> cv2solarTypeConvertMap =
{
    {CV_8UC3,{Image::ImageLayout::LAYOUT_BGR,Image::DataType::TYPE_8U}},
    {CV_8UC1,{Image::ImageLayout::LAYOUT_GREY,Image::DataType::TYPE_8U}},
    {CV_16UC1,{Image::ImageLayout::LAYOUT_GREY,Image::DataType::TYPE_16U}}
};

template<class Archive>
void Image::save(Archive & ar, const unsigned int version) const
{
    ar & m_size;
    ar & m_layout;
    ar & m_pixOrder;
    ar & m_type;
    ar & m_nbChannels;
    ar & m_nbPlanes;
    ar & m_nbBitsPerComponent;

    ar & m_imageEncoding;

    if ((m_imageEncoding == ENCODING_JPEG) || (m_imageEncoding == ENCODING_PNG)) {
        // JPEG or PNG encoding
        uint32_t image_size = m_size.width * m_size.height * m_nbChannels * (m_nbBitsPerComponent/8);
        cv::Mat imgCV(m_size.height, m_size.width,
                      solar2cvTypeConvertMap.at(std::forward_as_tuple(m_nbBitsPerComponent,1,m_nbChannels)),
                      m_internalImpl->data());

		std::vector<uchar> encodingBuffer;
        std::vector<int> param(2);

        if (m_imageEncoding == ENCODING_JPEG) {
            param[0] = cv::IMWRITE_JPEG_QUALITY;
            param[1] = m_imageEncodingQuality;
            cv::imencode(".jpg", imgCV, encodingBuffer, param);
        }
        else {
            param[0] = cv::IMWRITE_PNG_COMPRESSION;
            param[1] = m_imageEncodingQuality;
            cv::imencode(".png", imgCV, encodingBuffer, param);
        }
        ar & encodingBuffer;
    }
    else {
        ar & m_internalImpl;
    }
}

template<class Archive>
void Image::load(Archive & ar, const unsigned int version)
{
    ar & m_size;
    ar & m_layout;
    ar & m_pixOrder;
    ar & m_type;
    ar & m_nbChannels;
    ar & m_nbPlanes;
    ar & m_nbBitsPerComponent;

    ar & m_imageEncoding;

    if ((m_imageEncoding == ENCODING_JPEG) || (m_imageEncoding == ENCODING_PNG)) {
        // JPEG or PNG decoding
        std::vector<uchar> decodingBuffer;
        ar & decodingBuffer;
//        std::cout << "===> Encoded image size = " << decodingBuffer.size() << std::endl;
        cv::Mat imageDecode = cv::imdecode(decodingBuffer, 1);
//        std::cout << "===> Decoded image size = " << imageDecode.total() * imageDecode.elemSize() << std::endl;

//        cv::imshow("Image after decoding", imageDecode);
//        cv::waitKey(0);

        m_internalImpl = utils::make_shared<ImageInternal>();
        m_internalImpl->setData(imageDecode.ptr(), imageDecode.total() * imageDecode.elemSize());
    }
    else {
        ar & m_internalImpl;
    }
}

IMPLEMENTSERIALIZE(Image);
//image creation from opencv conversion ... : howto handle memory allocation locality : factory ?
// conversion from/to opencv for instance : how to handle the T* type while bound to void* ?
}
}

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::Image)
//BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::Image)
BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::ImageInternal)
//BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::ImageInternal)
BOOST_CLASS_TYPE_INFO(
SolAR::datastructure::ImageInternal,
boost::serialization::extended_type_info_typeid<SolAR::datastructure::ImageInternal>
)
