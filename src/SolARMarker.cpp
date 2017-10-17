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

#include "SolARMarker.h"
#include <iostream>
#include <utility>


namespace SolAR {


SolARMarker::SolARMarker(){

};

SolARMarker::SolARMarker(std::vector<std::pair<float, float>>&edges_temp){
edges = edges_temp;
}

SolARMarker::~SolARMarker(){

}

double SolARMarker::getArea(){
    if(edges.size()!=4)
        return 0.f;
    double d0  = std::sqrt((edges[1].first -edges[0].first)   * (edges[1].first -edges[0].first)+
                           (edges[1].second -edges[0].second) * (edges[1].second -edges[0].second));

    double d1  = std::sqrt((edges[2].first -edges[0].first)   * (edges[2].first -edges[0].first) +
                           (edges[2].second -edges[0].second) * (edges[2].second -edges[0].second));

    return (d0*d1);
}

void  SolARMarker::generate7x7Marker(std::string& fileToWrite){
 /*
    UNDER REFLEXION
*/
}

int  SolARMarker::rotate(SRef<SolARImage>in,SRef<SolARImage>out){
    /*
       UNDER REFLEXION
   */
    return 0;
}
int  SolARMarker::hammDistMarker(SRef<SolARImage> bits){
    /*
       UNDER REFLEXION
   */
    return 0;
}
int  SolARMarker::mat2id(SRef<SolARImage>bits){
    /*
       UNDER REFLEXION
   */
    return 0;

}
int  SolARMarker::getMarkerId(SRef<SolARImage>in, int &nRotations){
    /*
       UNDER REFLEXION
   */
    return 0;

}

}  // end of namespace Solar
