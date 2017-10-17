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

#ifndef SOLARIMAGE_H
#define SOLARIMAGE_H

#include "XPCF_definitions.h"
#include "SolARFrameworkDefinitions.h"

#include <memory>
namespace SolAR {

struct SolARSize {
    uint32_t width;
    uint32_t height;
};

struct SolARRectangle {
    uint32_t startX;
    uint32_t startY;
    SolARSize size;
};

//Add stride notion
// Hypothese : pas de bits per component : only full format image YUV444, RGB888, RGB 555 but not YUV420, RGB565 and so on or YUV422 with splatting
class SOLARFRAMEWORK_API SolARImage {

    ///
    /// \brief ~SolARImage
    ///
    ///
public:
    //static_assert(std::is_same<T, double>::value || std::is_same<T, float>::value || std::is_same<T, uint8_t>::value,"type not allowed for SolARImage");
    enum DataType {
        TYPE_8U,
        TYPE_16U,
        TYPE_32U,//NOTE :: openvx handles differently "descriptors" or "pyramids" and images : they do not represent the same thing in openvx
        // openvx image handles only integer types !!!
        TYPE_64U
    };

    enum ImageLayout {
        LAYOUT_RGB=0,          /**< means 3 channels per pixel : Red, Green, Blue */
        LAYOUT_GRB,            /**< means 3 channels per pixel : Green,Red, Blue (this is opencv model)*/
        LAYOUT_BGR,            /**< means 3 channels per pixel : Green,Red, Blue (this is opencv model)*/
        LAYOUT_GREY,           /**< means 1 channel per pixel  : grey color*/
        LAYOUT_RGBA,          /**< means 4 channels per pixel : Red, Green, Blue and Alpha channel*/
        LAYOUT_RGBX,           /**< means 4 channels per pixel : Red, Green, Blue and transparency */
        LAYOUT_UNDEFINED
    };

    enum ColorSpace {
        SPACE_RGB_709=0,          /**< means 3 channels per pixel : Red, Green, Blue */
        SPACE_GREY,           /**< means 1 channel per pixel  : grey color*/
        SPACE_UNDEFINED
    };

    // channel info ?
    // black and white
    // BitsPerComponent<dimension f(nb channels)>
    enum PixelOrder {
        INTERLEAVED=0,          /**< means 3 channels per pixel : Red, Green, Blue */
        PER_CHANNEL
    };

    /// \brief SolARImage
    /// \param pixLayout: defined by ImageLayout
    /// \param pixOrder: defined if the data are stored interleaved RGB,RGB or as a planar representation RRR,GGG,BBB
    /// \param type: defined by DataType
    SolARImage(enum ImageLayout pixLayout, enum PixelOrder pixOrder, DataType type);

    /// \brief  SolARImage
    /// \param width: width of the image
    /// \param height: height of the image
    /// \param pixLayout: defined by ImageLayout
    /// \param pixOrder: defined if the data are stored interleaved RGB,RGB or as a planar representation RRR,GGG,BBB
    /// \param type: defined by DataType
    SolARImage(uint32_t width, uint32_t height, enum ImageLayout pixLayout, enum PixelOrder pixOrder, DataType type);

    /// \brief  SolARImage built from a raw data pointer
    /// \param imageData: pointer to the raw data
    /// \param width: width of the image
    /// \param height: height of the image
    /// \param pixLayout: defined by ImageLayout
    /// \param pixOrder: defined if the data are stored interleaved RGB,RGB or as a planar representation RRR,GGG,BBB
    /// \param type: defined by DataType
    SolARImage(void* imageData, uint32_t width, uint32_t height, enum ImageLayout pixLayout, enum PixelOrder pixOrder, DataType type);

    /// \brief  ~SolARImage
    ~SolARImage() = default;

    /// \brief  reserves new space depending on the image layers and bitspercomponent infos
    /// \param width: width of the image
    /// \param height: height of the image
    void setSize(uint32_t width, uint32_t height);

    /// \brief  get bytes size of underlying storage
    uint32_t getSize();

    //never use this accessor to delete the underlying data !
    // use to wrap internal buffer data in other framework image wrapper for instance cv::Mat

    /// \brief never use this accessor to delete the underlying data !
    void* data();

    /// \brief never use this accessor to delete the underlying data !y
    const void* data() const;

    /// \brief extracts a subregion for tiling for interleaved data representation only
    /// \param region: defines the regoion to extract as a rectangle
    /// \param channel: assumes planar representation of the image
    SRef<SolARImage> extractRegion(SolARRectangle region); // to handle in a splitter/extractor component, must not be handled in the image itself

    /// \brief extracts a subregion for tiling for a single plane inside a multiplanar image
    /// \param region: defines the regoion to extract as a rectangle
    /// \param channel: assumes planar representation of the image
    SRef<SolARImage> extractRegion(SolARRectangle region, uint32_t channel);

    /// \brief returns the image layout
    inline enum ImageLayout getImageLayout() const  { return m_layout; }

    /// \brief returns the pixel order
    inline enum PixelOrder getPixelOrder() const { return m_pixOrder; }

    /// \brief returns the dataType
    inline enum DataType getDataType() const { return m_type; }

    /// \brief returns the number of channels
    inline uint32_t getNbChannels() const { return m_nbChannels; }

    /// \brief returns the amount of bit per component
    inline uint32_t getNbBitsPerComponent() const { return m_nbBitsPerComponent; }

    /// \brief  returns height of the image
    inline uint32_t getWidth() const  { return m_width; }

    /// \brief  returns height of the image
    inline uint32_t getHeight() const { return m_height; }

private:
    class SolARImageInternal;
    SRef<SolARImageInternal> m_internalImpl;

    uint32_t computeImageBufferSize();
    uint32_t m_width;
    uint32_t m_height;
    enum ImageLayout m_layout;
    enum PixelOrder m_pixOrder;
    enum DataType m_type;
    uint32_t m_nbChannels;
    uint32_t m_nbPlanes;
    uint32_t m_nbBitsPerComponent;
};
//image creation from opencv conversion ... : howto handle memory allocation locality : factory ?
// conversion from/to opencv for instance : how to handle the T* type while bound to void* ?
}

#endif
