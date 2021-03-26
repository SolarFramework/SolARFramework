/**
 * @copyright Copyright (c) 2020 B-com http://www.b-com.com/
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

#include "datastructure/ImageMarker.h"

#include "core/Log.h"

#include "xpcf/core/helpers.h"

namespace SolAR {
namespace datastructure {

// Construct a new ImageMarker from a binary pattern and a size (width and height)
ImageMarker::ImageMarker(const std::string & url,
                         const Sizef & size,
                         const SRef<Image> image) :
                        Trackable(url), Trackable2D(url, size), m_image(image) {
    LOG_DEBUG("ImageMarker constructor: url = {}, width = {}, height = {}",
              url, size.width, size.height);
}

// Class methods

// Returns the type (class name) of the trackable object
TrackableType ImageMarker::getType() const {
    return IMAGE_MARKER;
}

// Sets the binary pattern of the fiducial marker
void ImageMarker::setImage(const SRef<Image> image) {
    m_image = image;
}

// Returns the binary pattern of the fiducial marker
SRef<Image> ImageMarker::getImage() const {
    return m_image;
}

FrameworkReturnCode ImageMarker::getImageCorners(std::vector<Point2Df> & imageCorners) const
{
    imageCorners.clear();
    if (!m_image)
    {
        LOG_DEBUG("Marker image has not been loaded");
        return FrameworkReturnCode::_ERROR_LOAD_IMAGE;
    }
    imageCorners.push_back(Point2Df(0.0f, 0.0f));
    imageCorners.push_back(Point2Df(m_image->getWidth(), 0.0f));
    imageCorners.push_back(Point2Df(m_image->getWidth(), m_image->getHeight()));
    imageCorners.push_back(Point2Df(0.0f, m_image->getHeight()));

    return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode ImageMarker::getWorldCorners(std::vector<Point3Df> & worldCorners) const
{
    worldCorners.clear();
    worldCorners.push_back(Point3Df(-m_size.width/2.0f, -m_size.height/2.0f, 0.0f));
    worldCorners.push_back(Point3Df(m_size.width/2.0f, -m_size.height/2.0f, 0.0f));
    worldCorners.push_back(Point3Df(m_size.width/2.0f, m_size.height/2.0f, 0.0f));
    worldCorners.push_back(Point3Df(-m_size.width/2.0f, m_size.height/2.0f, 0.0f));

    return FrameworkReturnCode::_SUCCESS;
}

template<typename Archive>
void ImageMarker::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
    ar & m_image;
}

IMPLEMENTSERIALIZE(ImageMarker);

}
}
