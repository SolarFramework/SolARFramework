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

#include "datastructure/QRCode.h"
#include "xpcf/core/helpers.h"
#include <boost/serialization/export.hpp>

namespace SolAR {
namespace datastructure {

QRCode::QRCode(const std::string & url, const Sizef & size, const std::string & code) :
    Trackable(url), Trackable2D(url, size), m_code(code)
{
    LOG_DEBUG("QRCode constructor: url = {}, width = {}, height = {}, code = {}",
              url, size.width, size.height, code);
}

TrackableType QRCode::getType() const {
    return TrackableType::QRCODE_MARKER;
}

void QRCode::setCode(const std::string & code) {
    m_code = code;
}

std::string QRCode::getCode() const {
    return m_code;
}

template<typename Archive>
void QRCode::serialize(Archive &ar, const unsigned int /* version */) {

    ar.template register_type<QRCode>();
    ar & boost::serialization::base_object<Trackable2D>(*this);
    ar & m_code;
}

IMPLEMENTSERIALIZE(QRCode);

}
}

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::QRCode)
BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::QRCode)
