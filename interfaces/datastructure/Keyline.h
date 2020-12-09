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

#ifndef SOLAR_KEYLINE_H
#define SOLAR_KEYLINE_H

#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/GeometryDefinitions.h"

// Definition of Keyline Class //
// part of SolAR namespace //

namespace SolAR {
namespace datastructure {

/**
 * @class Keyline
 * @brief <B>A 2D Keyline.</B>
 *
 * This class provides Keyline definition.
 */

class SOLARFRAMEWORK_API Keyline : public Point2Df
{
public:
	Keyline() = default;

	Keyline(float x,
			float y,
			float startPointX,
			float startPointY,
			float sPointInOctaveX,
			float sPointInOctaveY,
			float endPointX,
			float endPointY,
			float ePointInOctaveX,
			float ePointInOctaveY,
			float lineLength,
			float size,
			float angle,
			float response,
			int   numOfPixels,
			int   octave,
			int   class_id);

	~Keyline();


	void init(  float x,
				float y,
				float startPointX,
				float startPointY,
				float sPointInOctaveX,
				float sPointInOctaveY,
				float endPointX,
				float endPointY,
				float ePointInOctaveX,
				float ePointInOctaveY,
				float lineLength,
				float size,
				float angle,
				float response,
				int   numOfPixels,
				int   octave,
				int   class_id);

	inline float getStartPointX() const { return m_startPointX; }

    inline float getStartPointY() const { return m_startPointY; }

	inline float getSPointInOctaveX() const { return m_sPointInOctaveX; }

	inline float getSPointInOctaveY() const { return m_sPointInOctaveY; }

	inline float getEndPointX() const { return m_endPointX; }

    inline float getEndPointY() const { return m_endPointY; }

	inline float getEPointInOctaveX() const { return m_ePointInOctaveX; }

	inline float getEPointInOctaveY() const { return m_ePointInOctaveY; }

	inline float getLineLength() const { return m_lineLength; }

	inline float getSize() const { return m_size; }

	inline float getAngle() const { return m_angle; }

	inline float getResponse() const { return m_response; }

	inline int getNumOfPixels() const { return m_numOfPixels; }

	inline int getOctave() const { return m_octave; }

	inline int getClassId() const { return m_class_id; }

private:
	float	m_startPointX;
	float	m_startPointY;
	float	m_sPointInOctaveX;
	float	m_sPointInOctaveY;
	float	m_endPointX;
	float	m_endPointY;
	float	m_ePointInOctaveX;
	float	m_ePointInOctaveY;
	float	m_lineLength;
	float	m_size;
	float	m_angle;
	float	m_response;
	int		m_numOfPixels;
	int		m_octave;
	int		m_class_id;
};
}
}

#endif // SOLAR_KEYLINE_H
