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

#ifndef IMAGEMARKER_H
#define IMAGEMARKER_H

#include <datastructure/Image.h>
#include <datastructure/Trackable2D.h>

// Definition of ImageMarker Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
    * @class ImageMarker
    * @brief <B>This class defines a fiducial marker datastructure.</B>
    */
class SOLARFRAMEWORK_API ImageMarker : virtual public Trackable2D {
    public:
        ///
        /// @brief ImageMarker default constructor
        ///
        ImageMarker() = default;

        ///
        /// @brief ImageMarker constructor
        /// with image and size of image marker
        /// @param[in] url: url of the trackable object
        /// @param[in] size: size (width and height) of the fiducial marker image
        /// @param[in] image: the image representing the marker
        ///
        ImageMarker(const std::string & url, const Sizef & size, const SRef<Image> image);

        // Class methods

        ///
        /// @brief Returns the type of the Trackable object
        /// @return TrackableType: the type of the instance
        ///
        TrackableType getType() const override;

        /// @brief Sets the image of the image marker
        /// @param[in] image: the image representing the marker
        void setImage(const SRef<Image> image);

        /// @brief Returns the image of the image marker
        /// @result the image representing the marker
        SRef<Image> getImage() const;

        /// @brief Provide the position of 2D corners in image coordinate system
        /// @param[out] imageCorners the 2D corners of the marker in image coordinate system
        /// @return FrameworkReturnCode::_SUCCESS if sucessful, eiher FrameworkRetunrnCode::_ERROR_.
        FrameworkReturnCode getImageCorners(std::vector<SolAR::datastructure::Point2Df> & imageCorners) const;

    private:
        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version);

    private:
        SRef<Image> m_image; // image of the image marker

    public:
        template <typename JsonType>
        friend void to_json(JsonType& j, const ImageMarker& marker)
        {
            j["url"] = marker.m_url;
            j["transform3D"] = marker.m_transform3D;
            j["size"]["width"] = marker.m_size.width;
            j["size"]["height"] = marker.m_size.height;
        }
        template <typename JsonType>
        friend void from_json(JsonType& j, ImageMarker& marker)
        {
            marker.m_url = j.at("url");
            marker.m_transform3D = j.at("transform3D");
            marker.m_size.width = j["size"]["width"].template get<float>();
            marker.m_size.height = j["size"]["height"].template get<float>();
        }
};

DECLARESERIALIZE(ImageMarker);

}
} // end of namespace SolAR

#endif // IMAGEMARKER_H
