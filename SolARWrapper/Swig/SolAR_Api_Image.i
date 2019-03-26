%module solar_api_image
%{
#include "api/image/IImageConvertor.h"
#include "api/image/IImageFilter.h"
#include "api/image/IImageLoader.h"
#include "api/image/IPerspectiveController.h"
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

%shared_ptr(SolAR::api::image::IImageConvertor)
%shared_ptr(SolAR::api::image::IImageFilter)
%shared_ptr(SolAR::api::image::IImageLoader)
%shared_ptr(SolAR::api::image::IPerspectiveController)

///

%include "api/image/IImageConvertor.h"

%include "api/image/IImageFilter.h"

%include "api/image/IImageLoader.h"

%include "api/image/IPerspectiveController.h"
