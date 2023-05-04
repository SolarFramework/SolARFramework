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

#include <boost/serialization/vector.hpp>
#include <boost/algorithm/string.hpp>

#include <OpenImageIO/imageio.h>
#include <OpenImageIO/filesystem.h>
#include <OpenImageIO/imagebufalgo.h>

namespace xpcf  = org::bcom::xpcf;
using namespace org::bcom::xpcf;

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::Image);

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

Image::Image(void* imageData, uint32_t width, uint32_t height, enum ImageLayout imgLayout, enum PixelOrder pixOrder,
             DataType type, ImageEncoding encoding):Image(width, height, imgLayout, pixOrder,type)
{
    if (encoding == ENCODING_NONE) {
        m_internalImpl->setData(imageData, computeImageBufferSize());
    }
    else {
        // JPEG or PNG decoding
        OIIO::Filesystem::IOMemReader memreader(imageData, computeImageBufferSize());

        std::string filename;
        switch (encoding)
        {
            case ENCODING_JPEG:
                filename="in.jpg";
                break;
            case ENCODING_PNG:
                filename = "in.png";
                break;
            default:
                filename="in.jpg";
                break;
        }

        auto in = OIIO::ImageInput::open (filename, nullptr, &memreader);
        const OIIO::ImageSpec & spec = in->spec();

        OIIO::imagesize_t buffersize = spec.image_bytes(true);
        unsigned char* pixels = new unsigned char [buffersize];
        in->read_image(OIIO::TypeDesc::UNKNOWN, pixels);

        m_internalImpl = utils::make_shared<ImageInternal>();
        m_internalImpl->setData(pixels, spec.image_bytes(true));
        in->close();
    }
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
}

void Image::setImageEncodingQuality(uint8_t encodingQuality)
{
    if (encodingQuality <= 100) {
        m_imageEncodingQuality = encodingQuality;
    }
	else
	{
		std::cout << "Warning: Image encoding quality cannot be more than 100 for JPEG. Set to 70 by default.";
		m_imageEncodingQuality = 70;
	}
}

static std::map<Image::DataType,OIIO::TypeDesc> SolAR2OIIOType = {{Image::DataType::TYPE_8U, OIIO::TypeDesc::UINT8},
                                                                  {Image::DataType::TYPE_16U, OIIO::TypeDesc::INT16},
                                                                  {Image::DataType::TYPE_32U, OIIO::TypeDesc::FLOAT},
                                                                  {Image::DataType::TYPE_64U, OIIO::TypeDesc::DOUBLE}};

static std::map<OIIO::TypeDesc,Image::DataType> OIIO2SolARType = {{OIIO::TypeDesc::UINT8, Image::DataType::TYPE_8U},
                                                                  {OIIO::TypeDesc::INT8, Image::DataType::TYPE_8U},
                                                                  {OIIO::TypeDesc::UINT16, Image::DataType::TYPE_16U},
                                                                  {OIIO::TypeDesc::INT16, Image::DataType::TYPE_16U},
                                                                  {OIIO::TypeDesc::UINT32, Image::DataType::TYPE_32U},
                                                                  {OIIO::TypeDesc::INT32, Image::DataType::TYPE_32U},
                                                                  {OIIO::TypeDesc::UINT64, Image::DataType::TYPE_64U},
                                                                  {OIIO::TypeDesc::INT64, Image::DataType::TYPE_64U},
                                                                  {OIIO::TypeDesc::FLOAT, Image::DataType::TYPE_32U},
                                                                  {OIIO::TypeDesc::DOUBLE, Image::DataType::TYPE_64U}};

static std::map<std::vector<std::string>,Image::ImageLayout> OIIO2SolARLayout = {{{"R","G","B"}, Image::ImageLayout::LAYOUT_RGB},
                                                                                 {{"B","G","R"}, Image::ImageLayout::LAYOUT_BGR},
                                                                                 {{"G"}, Image::ImageLayout::LAYOUT_GREY},
                                                                                 {{"R","G","B","A"}, Image::ImageLayout::LAYOUT_RGBA}};
static std::map<Image::ImageLayout,std::vector<std::string>> SolAR2OIIOLayout = {{Image::ImageLayout::LAYOUT_RGB, {"R","G","B"}},
                                                                                 {Image::ImageLayout::LAYOUT_BGR, {"B","G","R"}},
                                                                                 {Image::ImageLayout::LAYOUT_GREY, {"G"}},
                                                                                 {Image::ImageLayout::LAYOUT_RGBA, {"R","G","B","A"}},
                                                                                 {Image::ImageLayout::LAYOUT_RGBX, {"R","G","B","A"}}};


FrameworkReturnCode Image::save(std::string imagePath) const
{
    Image::ImageEncoding encoding;
    if (boost::algorithm::ends_with(imagePath, ".jpg") || boost::algorithm::ends_with(imagePath, ".jpeg"))
        encoding = ENCODING_JPEG;
    else if (boost::algorithm::ends_with(imagePath, ".png"))
        encoding = ENCODING_PNG;
    else
    {
       std::cout << "Try to encode an image with an unkown suffix. Only .jpeg, .jpg and .png are accepted." << std::endl;
       return FrameworkReturnCode::_ERROR_;
    }

    OIIO::TypeDesc type;
    if (SolAR2OIIOType.find(m_type) != SolAR2OIIOType.end())
        type = SolAR2OIIOType.at(m_type);
    else
        type = OIIO::TypeDesc::UNKNOWN;

    OIIO::ImageSpec spec = OIIO::ImageSpec(m_size.width, m_size.height, m_nbChannels, type);

    spec.nchannels = m_nbChannels;
    if (SolAR2OIIOLayout.find(m_layout) != SolAR2OIIOLayout.end())
        spec.channelnames = SolAR2OIIOLayout.at(m_layout);

    spec.attribute ("oiio:ColorSpace", "sRGB");

    switch (encoding)
    {
        case ENCODING_JPEG:
            spec.attribute ("Compression","jpeg:" + std::to_string(m_imageEncodingQuality));
            break;
        case ENCODING_PNG:
            if (m_imageEncodingQuality==0)
                spec.attribute ("png:compressionLevel", 0);
            else if (m_imageEncodingQuality>=100)
                spec.attribute ("png:compressionLevel", 9);
            else
            {
                // PNG encoding quality should be defined between 0 and 9.
                spec.attribute ("png:compressionLevel", (int)floor(m_imageEncodingQuality/10.0f));
            }
            break;
        default:
            break;
    }

    OIIO::ImageBuf sourceBuf = OIIO::ImageBuf(spec, m_internalImpl->data());

    // Convert to BGR or GRB to RGB channel format
    if (m_layout == Image::ImageLayout::LAYOUT_BGR)
        sourceBuf = OIIO::ImageBufAlgo::channels(sourceBuf, 3, { 2, 1, 0 });

    sourceBuf.write(imagePath);

    return FrameworkReturnCode::_SUCCESS;
}

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

        // ImageSpec describing the image we want to write.
        OIIO::ImageSpec spec;
        if (SolAR2OIIOType.find(m_type) != SolAR2OIIOType.end())
            spec = OIIO::ImageSpec(m_size.width, m_size.height, m_nbChannels);
        else
            spec = OIIO::ImageSpec(m_size.width, m_size.height, m_nbChannels, SolAR2OIIOType.at(m_type));

        if (SolAR2OIIOLayout.find(m_layout) != SolAR2OIIOLayout.end())
            spec.channelnames=SolAR2OIIOLayout.at(m_layout);

        std::vector<unsigned char> file_buffer;  // bytes will go here
        OIIO::Filesystem::IOVecOutput encodingBuffer (file_buffer);  // I/O proxy object;

        std::string filename;
        switch (m_imageEncoding)
        {
            case ENCODING_JPEG:
                filename="out.jpeg";
                spec.attribute ("Compression","jpeg:" + std::to_string(m_imageEncodingQuality));
                break;
            case ENCODING_PNG:
                filename = "out.png";
                if (m_imageEncodingQuality==0)
                    spec.attribute ("png:compressionLevel", 0);
                else if (m_imageEncodingQuality>=100)
                    spec.attribute ("png:compressionLevel", 9);
                else
                {
                    // PNG encoding quality should be defined between 0 and 9.
                    spec.attribute ("png:compressionLevel", (int)floor(m_imageEncodingQuality/10.0f));
                }
                break;
            default:
                filename = "out";
        }

        auto out = OIIO::ImageOutput::create (filename, &encodingBuffer);
        if (!out)
            std::cout << "ImageOutput::create : " << OIIO::geterror() << std::endl;

        if (!out->supports("ioproxy"))
        {
            std::cout << "Decoding image to a buffer based on OIIO::ioporxy is not supported for this image format. Save image in raw format.)";
            ar & m_internalImpl;
            return;
        }
        out->open (filename, spec);

        if (!out->write_image (SolAR2OIIOType[m_type], m_internalImpl->data()))
        {
            std::cout << "Error while writing the " << filename << " image to the serialization buffer. " << std::endl << OIIO::geterror() << std::endl;
            return;
        }
        out->close ();

        ar & file_buffer;
    }
    else {
        ar & m_internalImpl;
    }
}

FrameworkReturnCode Image::load(std::string imagePath)
{
    auto in = OIIO::ImageInput::open(imagePath);
    if (!in)
    {
        std::cout << "Cannot load the image " << imagePath << " due to the following error: " << OIIO::geterror() << std::endl;
        return FrameworkReturnCode::_ERROR_;
    }

    const OIIO::ImageSpec spec = in->spec();
    m_size.width = spec.width;
    m_size.height = spec.height;
    m_nbChannels = spec.nchannels;

    OIIO::imagesize_t buffersize = spec.image_bytes(true);
    unsigned char* pixels = new unsigned char [buffersize];
    in->read_image(OIIO::TypeDesc::UNKNOWN, pixels);

    if (OIIO2SolARType.find(spec.format) != OIIO2SolARType.end())
    {
       m_type = OIIO2SolARType.at(spec.format);
       m_nbBitsPerComponent = typeSizeMapInfos.at(m_type);
    }
    else
    {
        std::cout << "Format " << spec.format << "is not supported when loading an image from a file" << std::endl;
        return FrameworkReturnCode::_ERROR_LOAD_IMAGE;
    }
    m_nbPlanes = 1;

    switch (spec.nchannels)
    {
        case 1:
            m_layout = Image::LAYOUT_GREY;
            m_nbChannels = 1;
            break;
        case 3:
        case 4:
            if (OIIO2SolARLayout.find(spec.channelnames) != OIIO2SolARLayout.end())
                m_layout = OIIO2SolARLayout.at(spec.channelnames);
            else
            {
                std::cout << "Try to decode an image with unsupported channels. Only RGB, GRB, BGR, RGBA and Grey are supported";
                FrameworkReturnCode::_ERROR_LOAD_IMAGE;
            }
            m_nbChannels = (unsigned int)spec.nchannels;
            break;
        default:
           std::cout << "Error: Try to decode an image with " << spec.nchannels << " channels. Only 1, 3 or 4 channels are supported";
           FrameworkReturnCode::_ERROR_LOAD_IMAGE;
    }

    m_internalImpl = utils::make_shared<ImageInternal>();
    m_internalImpl->setData(pixels, spec.image_bytes(true));
    in->close();

    return FrameworkReturnCode::_SUCCESS;
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
         std::vector<unsigned char> decodingBuffer;
         ar & decodingBuffer;

         OIIO::Filesystem::IOMemReader memreader(decodingBuffer.data(), decodingBuffer.size());

         std::string filename;
         switch (m_imageEncoding)
         {
             case ENCODING_JPEG:
                 filename="in.jpg";
                 break;
             case ENCODING_PNG:
                 filename = "in.png";
                 break;
             default:
                 filename="in.jpg";
                 break;
         }

         auto in = OIIO::ImageInput::open (filename, nullptr, &memreader);
         const OIIO::ImageSpec & spec = in->spec();

         OIIO::imagesize_t buffersize = spec.image_bytes(true);
         unsigned char* pixels = new unsigned char [buffersize];
         in->read_image(OIIO::TypeDesc::UNKNOWN, pixels);

         m_internalImpl = utils::make_shared<ImageInternal>();
         m_internalImpl->setData(pixels, spec.image_bytes(true));
         in->close();
     }
     else {
         ar & m_internalImpl;
     }
}

FrameworkReturnCode Image::rotate(RotateQuantity degrees)
{
    OIIO::TypeDesc type;
    if (SolAR2OIIOType.find(m_type) != SolAR2OIIOType.end())
        type = SolAR2OIIOType.at(m_type);
    else
        type = OIIO::TypeDesc::UNKNOWN;

    OIIO::ImageSpec spec = OIIO::ImageSpec(m_size.width, m_size.height, m_nbChannels, type);

    spec.nchannels = m_nbChannels;
    if (SolAR2OIIOLayout.find(m_layout) != SolAR2OIIOLayout.end())
        spec.channelnames = SolAR2OIIOLayout.at(m_layout);

    spec.attribute ("oiio:ColorSpace", "sRGB");

    OIIO::ImageBuf sourceBuf = OIIO::ImageBuf(spec, m_internalImpl->data());

    // Convert to BGR or GRB to RGB channel format
    if (m_layout == Image::ImageLayout::LAYOUT_BGR)
        sourceBuf = OIIO::ImageBufAlgo::channels(sourceBuf, 3, { 2, 1, 0 });

    OIIO::ImageBuf rotatedBuf;
    bool rotateSuccess = false;
    switch (degrees) {
    case RotateQuantity::DEGREE_90:
        rotateSuccess = OIIO::ImageBufAlgo::rotate90(rotatedBuf, sourceBuf);
        break;
    case RotateQuantity::DEGREE_180:
        rotateSuccess = OIIO::ImageBufAlgo::rotate180(rotatedBuf, sourceBuf);
        break;
    case RotateQuantity::DEGREE_270:
        rotateSuccess = OIIO::ImageBufAlgo::rotate270(rotatedBuf, sourceBuf);
        break;
    default:
        // not supported by OpenImageIO
        std::cout << "Image rotation which is not 90, 180 or 270 degrees is not supported" << std::endl;
        return FrameworkReturnCode::_ERROR_;
    }

    if (!rotateSuccess)
        return FrameworkReturnCode::_ERROR_;
    
    if (rotatedBuf.has_error())
    {
        std::cout << "error: " << rotatedBuf.geterror() << std::endl;
        return FrameworkReturnCode::_ERROR_;
    }

    if (degrees == RotateQuantity::DEGREE_90 || degrees == RotateQuantity::DEGREE_270)
        setSize(m_size.height, m_size.width);

    std::vector<unsigned char> result;
    result.resize (m_size.width * m_size.height * m_nbBitsPerComponent * m_nbChannels);

    if (!rotatedBuf.get_pixels(OIIO::ROI::All(), type, &result[0]))
        return FrameworkReturnCode::_ERROR_;
    m_internalImpl->setData(&result[0], m_internalImpl->getBufferSize());
    return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode Image::rotate90() 
{
    return rotate(Image::RotateQuantity::DEGREE_90);
}

FrameworkReturnCode Image::rotate180()
{
    return rotate(Image::RotateQuantity::DEGREE_180);
}

FrameworkReturnCode Image::rotate270()
{
    return rotate(Image::RotateQuantity::DEGREE_270);
}

IMPLEMENTSERIALIZE(Image);
}
}


