%module solar_api_solver_pose
%{
#include "api/solver/pose/I2D3DCorrespondencesFinder.h"
#include "api/solver/pose/I2Dto3DTransformDecomposer.h"
//#include "api/solver/pose/I2Dto3DTransformDecomposerValidation.h" //TODO Wrong Namespace
#include "api/solver/pose/I2DTransformFinder.h"
#include "api/solver/pose/I3DTransformFinderFrom2D2D.h"
#include "api/solver/pose/I3DTransformFinderFrom2D3D.h"
#include "api/solver/pose/I3DTransformSACFinderFrom2D3D.h"
#include "api/solver/pose/IHomographyValidation.h"
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

%shared_ptr(SolAR::api::solver::pose::I2D3DCorrespondencesFinder)
%shared_ptr(SolAR::api::solver::pose::I2Dto3DTransformDecomposer)
//%shared_ptr(SolAR::api::solver::pose::I2Dto3DTransformDecomposerValidation) //TODO Wrong Namespace
%shared_ptr(SolAR::api::solver::pose::I2DTransformFinder)
%shared_ptr(SolAR::api::solver::pose::I3DTransformFinderFrom2D2D)
%shared_ptr(SolAR::api::solver::pose::I3DTransformFinderFrom2D3D)
%shared_ptr(SolAR::api::solver::pose::I3DTransformSACFinderFrom2D3D)
%shared_ptr(SolAR::api::solver::pose::IHomographyValidation)

///

%include "api/solver/pose/I2D3DCorrespondencesFinder.h"

%include "api/solver/pose/I2Dto3DTransformDecomposer.h"

//%include "api/solver/pose/I2Dto3DTransformDecomposerValidation.h" //TODO Wrong Namespace

%include "api/solver/pose/I2DTransformFinder.h"

%include "api/solver/pose/I3DTransformFinderFrom2D2D.h"

%include "api/solver/pose/I3DTransformFinderFrom2D3D.h"

%include "api/solver/pose/I3DTransformSACFinderFrom2D3D.h"

%include "api/solver/pose/IHomographyValidation.h"
