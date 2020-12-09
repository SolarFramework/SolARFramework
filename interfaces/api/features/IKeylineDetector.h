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

#ifndef SOLAR_IKEYLINEDETECTOR_H
#define SOLAR_IKEYLINEDETECTOR_H

#include "core/Messages.h"
#include "datastructure/Image.h"
#include "datastructure/KeyLine.h"

#include "xpcf/api/IComponentIntrospect.h"

namespace SolAR {
using namespace datastructure;
namespace api {
namespace features {

/**
 * @class IKeylineDetector
 * @brief <B>Detects the keylines from an image.</B>
 * <TT>UUID: e60589f3-46fe-40c3-b624-389e08682751</TT>
 *
 * This class provides a method to detect the keylines from an image using different kind of method (LSD, MSLD, ...).
 */

class IKeylineDetector : virtual public org::bcom::xpcf::IComponentIntrospect
{
public:
	enum class KeylineDetectorType
	{
		LSD,
		MSLD
	};

	IKeylineDetector() = default;

	~IKeylineDetector() = default;

	virtual void setType(KeylineDetectorType type) = 0;

	virtual KeylineDetectorType getType() = 0;

	virtual void detect(const SRef<Image> image, std::vector<Keyline> & keylines) = 0;
};
}
}
}

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::features::IKeylineDetector,
							"e60589f3-46fe-40c3-b624-389e08682751",
							"IKeylineDetector",
							"SolAR::api::features::IKeylineDetector");

#endif // SOLAR_IKEYLINEDETECTOR_H