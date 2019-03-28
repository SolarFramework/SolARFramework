%module solar_api_solver_map
%{
#include "api/solver/map/IBundler.h"
#include "api/solver/map/IKeyframeSelector.h"
#include "api/solver/map/IMapFilter.h"
#include "api/solver/map/IMapper.h"
#include "api/solver/map/ITriangulator.h"
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

%shared_ptr(SolAR::api::solver::map::IBundler)
%shared_ptr(SolAR::api::solver::map::IKeyframeSelector)
%shared_ptr(SolAR::api::solver::map::IMapFilter)
%shared_ptr(SolAR::api::solver::map::IMapper)
%shared_ptr(SolAR::api::solver::map::ITriangulator)

%rename(IntList) std::vector<int>;
%template(IntList) std::vector<int>;
%rename(PairUIntUInt) std::pair<unsigned int, unsigned int>;
%template(PairUIntUInt) std::pair<unsigned int, unsigned int>;

///

%include "api/solver/map/IBundler.h"

%include "api/solver/map/IKeyframeSelector.h"

%include "api/solver/map/IMapFilter.h"

%include "api/solver/map/IMapper.h"

%include "api/solver/map/ITriangulator.h"
