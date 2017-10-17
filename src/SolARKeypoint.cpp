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

#include "SolARKeypoint.h"
#include <cstddef> //TO DO: remove with a complete implementation
namespace SolAR {

SolARKeypoint::~SolARKeypoint(){

}

SolARKeypoint::SolARKeypoint( float x,
                              float  	y,
                              float  	size,
                              float  	angle,
                              float  	response,
                              int  	octave,
                              int  	class_id ):m_x(x),m_y(y),m_size(size),m_angle(angle), m_response(response), m_octave(octave){


}
void SolARKeypoint::init( float  x,
            float  	y,
            float  	size,
            float  	angle,
            float  	response,
            int  	octave,
            int  	class_id ){

    m_x=x;
    m_y=y;
    m_size=size;
    m_angle=angle;
    m_response=response;
    m_octave=octave;
    m_class_id=class_id;

}
}
