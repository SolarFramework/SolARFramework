%module xpcf_module
%{
#include "xpcf/module/ModuleFactory.h"
%}

%include "Swig.i"

%import (module="XPCF.Core") "XPCF_Core.i"
%import (module="XPCF.Component") "XPCF_Component.i"
%import (module="XPCF.Api") "XPCF_Api.i"

%typemap(csimports) SWIGTYPE
%{
    using XPCF.Core;
    using XPCF.Component;
    using XPCF.Api;
%}

///

%include "xpcf/module/ModuleFactory.h"
