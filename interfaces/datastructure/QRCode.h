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

#ifndef QRCODE_H
#define QRCODE_H

#include <datastructure/Trackable2D.h>

// Definition of QRCode Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
    * @class QRCode
    * @brief <B>This class defines a QR code datastructure.</B>
    */
class SOLARFRAMEWORK_API QRCode : virtual public Trackable2D {
    public:
        ///
        /// @brief QRCode default constructor
        ///
        QRCode() = default;

        ///
        /// @brief QRCode constructor
        /// with decoding code and size of QR code image
        /// @param[in] url url of the trackable object
        /// @param[in] size size (width and height) of the QR code image
        /// @param[in] code decoding code of QRCode
        ///
        QRCode(const std::string & url, const Sizef & size, const std::string & code);

        ///
        /// @brief Returns the type of the Trackable object
        /// @return TrackableType the type of the instance
        ///
        TrackableType getType() const override;

        /// @brief Set deconding code of QRCode
        /// @param[in] code the decoding code
        void setCode(const std::string & code);

        /// @brief Returns the decoding code
        /// @return the decoding code
        std::string getCode() const;

    private:
        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar,  const unsigned int version);

    private:
        std::string m_code; // the decoding code

    public:
        template <typename JsonType>
        friend void to_json(JsonType& j, const QRCode& marker)
        {
            j["url"] = marker.m_url;
            j["transform3D"] = marker.m_transform3D;
            j["size"]["width"] = marker.m_size.width;
            j["size"]["height"] = marker.m_size.height;
            j["code"] = marker.m_code;
        }
        template <typename JsonType>
        friend void from_json(JsonType& j, QRCode& marker)
        {
            marker.m_url = j.at("url");
            marker.m_transform3D = j.at("transform3D");
            marker.m_size.width = j["size"]["width"].template get<float>();
            marker.m_size.height = j["size"]["height"].template get<float>();
            marker.m_code = j.at("code");
        }
};

DECLARESERIALIZE(QRCode);

}
} // end of namespace SolAR

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::QRCode);

#endif // QRCODE_H
