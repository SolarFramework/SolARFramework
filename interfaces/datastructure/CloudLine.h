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

#ifndef SOLAR_CLOUDLINE_H
#define SOLAR_CLOUDLINE_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

#include "xpcf/api/IComponentIntrospect.h"
#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"
#include "datastructure/DescriptorBuffer.h"
#include <mutex>

 // Definition of CloudLine Class //
 // part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
 * @class CloudLine
 * @brief <B>A 3D line stored in a cloud of lines.</B>
 */

class SOLARFRAMEWORK_API CloudLine : public Edge3Df
{
public:
	CloudLine() = default;
	~CloudLine() {};

	CloudLine(Edge3Df & line3D, double reproj_error, std::map<unsigned, unsigned> & visibilityMap);

	CloudLine(Edge3Df & line3D, double reproj_error, std::map<unsigned, unsigned> & visibilityMap, SRef<DescriptorBuffer> descriptor);

	double getReprojError() { return m_reproj_error; }

	const std::map<unsigned, unsigned> & getVisibility() const;

	void visibilityAddKeypoint(unsigned keyframe_id, unsigned keyline_id);

	SRef<DescriptorBuffer> getDescriptor() { return m_descriptor; }

private:
	std::map<unsigned, unsigned> m_visibility;
	
	double m_reproj_error;

	SRef<DescriptorBuffer> m_descriptor;
};

}
}

#endif // SOLAR_CLOUDLINE_H
