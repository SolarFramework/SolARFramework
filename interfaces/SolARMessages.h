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

#ifndef SOLARMESSAGES_H
#define SOLARMESSAGES_H

namespace SolAR {

enum class FrameworkReturnCode:long{

    _STOP=1, /** means stop the process */
  _SUCCESS=0, /** Successfull operation */

  // error codes
    _ERROR_=-1,               /** unknown error, better stop!! */

  // for ISolARImage
    _ERROR_LOAD_IMAGE=-10,    /** Cannot load Image */
    _ERROR_ACCESS_IMAGE=-11,  /** Cannot acces Image */
};

}  // end of namespace Argo

#endif // SOLARMESSAGES_H
