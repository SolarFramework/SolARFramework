%module solar_api_example
%{
#include "api/example/IInterface1.h"
#include "api/example/IInterface2.h"
%}

%include "Swig.i"

%import (module="XPCF.Api") "XPCF_Api.i"
%import (module="SolAR.Core") "SolAR_Core.i"

%typemap(csimports) SWIGTYPE
%{
    using XPCF.Api;
    using SolAR.Core;
%}

///

%shared_ptr(SolAR::api::example::IInterface1)
%shared_ptr(SolAR::api::example::IInterface2)

///

%include "api/example/IInterface1.h"

%include "api/example/IInterface2.h"
