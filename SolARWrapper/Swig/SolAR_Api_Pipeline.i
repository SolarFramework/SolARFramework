%module solar_api_pipeline
%{
#include "api/pipeline/IPipeline.h"
%}

%include "Swig.i"

%import (module="XPCF.Api") "XPCF_Api.i"
%import (module="SolAR.Core") "SolAR_Core.i"
%import (module="SolAR.Datastructure") "SolAR_Datastructure.i"
%import (module="SolAR.Api.Sink") "SolAR_Api_Sink.i"
%import (module="SolAR.Api.Source") "SolAR_Api_Source.i"

%typemap(csimports) SWIGTYPE
%{
    using XPCF.Api;
    using SolAR.Core;
    using SolAR.Datastructure;
    using SolAR.Api.Sink;
    using SolAR.Api.Source;
%}

///

%shared_ptr(SolAR::api::pipeline::IPipeline)

///

%include "api/pipeline/IPipeline.h"
