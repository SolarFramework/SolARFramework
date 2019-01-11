/**
 * @copyright Copyright (c) 2017 b<>com http://www.b-com.com/
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

#ifndef ISINKRETURNCODE_H
#define ISINKRETURNCODE_H

namespace SolAR {
namespace api {
namespace sink {

enum class SinkReturnCode: int {

    _ERROR= -1,
    _NOTHING = 0,
    _NEW_IMAGE= 0x01,
    _NEW_POSE= 0x02,
    _NEW_POSE_AND_IMAGE = 0x03,
};

inline SinkReturnCode operator|(SinkReturnCode a, SinkReturnCode b)
{return static_cast<SinkReturnCode>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));}

inline SinkReturnCode operator &(SinkReturnCode a, SinkReturnCode b)
{return static_cast<SinkReturnCode> (static_cast<unsigned int>(a) & static_cast<unsigned int>(b));}

inline SinkReturnCode operator ^(SinkReturnCode a, SinkReturnCode b)
{return static_cast<SinkReturnCode> (static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b));}

inline SinkReturnCode operator ~(SinkReturnCode a)
{return static_cast<SinkReturnCode> (~static_cast<unsigned int>(a));}

inline SinkReturnCode operator|=(SinkReturnCode &a, SinkReturnCode b)
{a = static_cast<SinkReturnCode>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b)); return a;}

inline SinkReturnCode operator&=(SinkReturnCode &a, SinkReturnCode b)
{a = static_cast<SinkReturnCode>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b)); return a;}

inline SinkReturnCode operator^=(SinkReturnCode &a, SinkReturnCode b)
{a = static_cast<SinkReturnCode>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b)); return a;}

}
}
}
#endif // ISINKRETURNCODE_H
