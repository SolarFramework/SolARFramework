%module solar_api_input_devices
%{
#include "api/input/devices/ICamera.h"
#include "api/input/devices/ICameraCalibration.h"
#include "api/input/devices/IIMU.h"
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

%shared_ptr(SolAR::api::input::devices::ICamera)
%shared_ptr(SolAR::api::input::devices::ICameraCalibration)
%shared_ptr(SolAR::api::input::devices::IIMU)

///

%include "api/input/devices/ICamera.h"

%include "api/input/devices/ICameraCalibration.h"

%include "api/input/devices/IIMU.h"
