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

#ifndef ISOURCERETURNCODE_H
#define ISOURCERETURNCODE_H

namespace SolAR {
namespace api {
namespace source {

enum class SourceReturnCode: int {

    _NOT_IMPLEMENTED= -2,
    _ERROR= -1,
    _NOTHING = 0,
    _NEW_IMAGE= 0x01,
    _NEW_POSE= 0x02,
    _NEW_POSE_AND_IMAGE = 0x03,
};

inline SourceReturnCode operator|(SourceReturnCode a, SourceReturnCode b)
{return static_cast<SourceReturnCode>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));}

inline SourceReturnCode operator &(SourceReturnCode a, SourceReturnCode b)
{return static_cast<SourceReturnCode> (static_cast<unsigned int>(a) & static_cast<unsigned int>(b));}

inline SourceReturnCode operator ^(SourceReturnCode a, SourceReturnCode b)
{return static_cast<SourceReturnCode> (static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b));}

inline SourceReturnCode operator ~(SourceReturnCode a)
{return static_cast<SourceReturnCode> (~static_cast<unsigned int>(a));}

inline SourceReturnCode operator|=(SourceReturnCode &a, SourceReturnCode b)
{a = static_cast<SourceReturnCode>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b)); return a;}

inline SourceReturnCode operator&=(SourceReturnCode &a, SourceReturnCode b)
{a = static_cast<SourceReturnCode>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b)); return a;}

inline SourceReturnCode operator^=(SourceReturnCode &a, SourceReturnCode b)
{a = static_cast<SourceReturnCode>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b)); return a;}

}
}
}
#endif // ISourceReturnCode_H
