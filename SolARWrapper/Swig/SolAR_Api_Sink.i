%module solar_api_sink
%{
#include "api/sink/ISinkPoseImage.h"
#include "api/sink/ISinkPoseTextureBuffer.h"
#include "api/sink/ISinkReturnCode.h"
%}

%include "Swig.i"

%import (module="XPCF.Api") "XPCF_Api.i"
%import (module="SolAR.Core") "SolAR_Core.i"
%import (module="SolAR.Datastructure") "SolAR_Datastructure.i"

%typemap(csimports) SWIGTYPE
%{
    using XPCF.Api;
    using SolAR.Core;
    using SolAR.Datastructure;
%}

///

%shared_ptr(SolAR::api::sink::ISinkPoseImage)
%shared_ptr(SolAR::api::sink::ISinkPoseTextureBuffer)

///

%ignore SolAR::api::sink::operator |;
%ignore SolAR::api::sink::operator &;
%ignore SolAR::api::sink::operator ^;
%ignore SolAR::api::sink::operator ~;
%ignore SolAR::api::sink::operator |=;
%ignore SolAR::api::sink::operator &=;
%ignore SolAR::api::sink::operator ^=;
%include "api/sink/ISinkReturnCode.h"

//#include "ISinkReturnCode.h"
%include "api/sink/ISinkPoseImage.h"

//#include "ISinkReturnCode.h"
%include "api/sink/ISinkPoseTextureBuffer.h"
