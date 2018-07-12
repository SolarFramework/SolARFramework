#include <iostream>
#include <utility>

#include "api/sink/ThirdPartyConnector.h"
#include "SharedCircularBuffer.hpp"

XPCF_DEFINE_FACTORY_CREATE_INSTANCE(SolAR::ThirdPartyConnector);

namespace xpcf = org::bcom::xpcf;

namespace SolAR {

ThirdPartyConnector::ThirdPartyConnector()
    : IThirdPartyConnector(),ComponentBase(xpcf::toUUID<ThirdPartyConnector>())
    , m_buffer( 1 ) //Replace with parameter passed to constructor when supported by XPCF
{
    addInterface<IThirdPartyConnector>(this);
}


ThirdPartyConnector::~ThirdPartyConnector()
{
}

void ThirdPartyConnector::set( const SRef<Pose>& pose, const SRef<Image>& image )
{
    m_buffer.push( std::make_pair(pose, image ) );
}

void ThirdPartyConnector::get( SRef<Pose>& pose, SRef<Image>& image )
{
    connectorDataType output = m_buffer.pop();
    pose = output.first;
    image = output.second;
}

bool ThirdPartyConnector::tryGet( SRef<Pose>& pose, SRef<Image>& image )
{
    connectorDataType output;
    bool popSuccessful = false;
    if( m_buffer.tryPop( output ) )
    {
        pose = output.first;
        image = output.second;
        popSuccessful = true;
    }
    return popSuccessful;
}


}  // end of namespace SolAR
