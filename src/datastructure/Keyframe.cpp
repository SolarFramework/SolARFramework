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

#include "datastructure/Keyframe.h"
#include <fstream>
#include "xpcf/core/helpers.h"
#include <utility>
#include <string>
#include <iostream>
#include <cstddef> //TO DO: remove with a complete implementation


//using namespace std;
namespace SolAR {
namespace datastructure {

const uint32_t& Keyframe::getId() const
{
	return m_id;
}

void Keyframe::setId(const uint32_t& id_keyframe)
{
	m_id = id_keyframe;
}

void Keyframe::setTimestamp(const double t)
{
   m_timestamp = t;
}

double Keyframe::getTimestamp()
{
    return m_timestamp;
}

void Keyframe::readProbamap()
{
    //char iobuf[4096];
    std::ifstream myfile("/home/mgonzalez/Code/Cluster_SLAM/SemanticData/probamap"+std::to_string(m_timestamp)+".bin", std::ios::binary);
    //cout << "Reading probamap " << std::to_string((int)timestamp) << endl;
    std::string line;
    int mH = 480;
    int mW = 640;
    int mC = 13;

    if(myfile.is_open())
    {
        float probaValue;
    
        m_probamap = new Eigen::MatrixXd(mH*mC, mW);
        for(int hc=0;hc < mH*mC;hc++)
        {
            for(int w=0;w<mW;w++)
            {   
                myfile.read(reinterpret_cast<char*>(&probaValue), sizeof(probaValue)); // binary input
                 
                (*m_probamap)(hc,w) = probaValue;
            
            }
        }
        myfile.close();
        std::cout << "Probamap read" << std::endl;
    }
    else
    {
       std::cout << "Could not read proba map: " << "/home/mgonzalez/Code/Cluster_SLAM/SemanticData/probamap"+std::to_string(m_timestamp)+".bin" << std::endl;
       m_probamap =  NULL;
    }
	/*

    std::ifstream fileIdMap("/home/mgonzalez/Code/Cluster_SLAM/SemanticData/id_mask"+std::to_string(mTimeStamp)+".bin", ios::binary);
    //cout << "Reading id map " << std::to_string((int)timestamp) << endl;
    mH = 480;
    mW = 640;

    if(fileIdMap.is_open())
    {
        int id;
    
        mvIdMap = new Eigen::MatrixXi(mH, mW);
        for(int h=0;h < mH;h++)
        {
            

            for(int w=0;w<mW;w++)
            {   
                fileIdMap.read(reinterpret_cast<char*>(&id), sizeof(id)); // binary input
                 
                (*mvIdMap)(h,w) = id;
               
            
            }
          
            

        }
        fileIdMap.close();
    }
    else
    {
       cout << "Could not read id map" << endl;
       mvProbaMap =  NULL;
    }*/
}

template<typename Archive>
void Keyframe::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {
	ar & boost::serialization::base_object<Frame>(*this);
	ar & boost::serialization::base_object<PrimitiveInformation>(*this);
	ar & m_id;
}

IMPLEMENTSERIALIZE(Keyframe);

}
}
