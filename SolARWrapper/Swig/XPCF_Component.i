%module xpcf_component
%{
#include "xpcf/component/ComponentBase.h"
#include "xpcf/component/ComponentFactory.h"
#include "xpcf/component/ConfigurableBase.h"
%}

%include "Swig.i"

%import (module="XPCF.Core") "XPCF_Core.i"
%import (module="XPCF.Api") "XPCF_Api.i"

%typemap(csimports) SWIGTYPE
%{
    using XPCF.Core;
    using XPCF.Api;
%}

///

%shared_ptr(org::bcom::xpcf::ComponentBase)

///

%include "xpcf/component/ComponentFactory.h"

//%include "xpcf/component/ComponentFactory.i"
%include "xpcf/component/ComponentBase.h"

//%include "xpcf/component/ComponentBase.i"
//%include "xpcf/component/ConfigurableBase.h"
