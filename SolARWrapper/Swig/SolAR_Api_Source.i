%module solar_api_source
%{
#include "api/source/ISourceImage.h"
#include "api/source/ISourceReturnCode.h"
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

%shared_ptr(SolAR::api::source::ISourceImage)

///

%ignore SolAR::api::source::operator |;
%ignore SolAR::api::source::operator &;
%ignore SolAR::api::source::operator ^;
%ignore SolAR::api::source::operator ~;
%ignore SolAR::api::source::operator |=;
%ignore SolAR::api::source::operator &=;
%ignore SolAR::api::source::operator ^=;
%include "api/source/ISourceReturnCode.h"

//#include "ISourceReturnCode.h"
%include "api/source/ISourceImage.h"
