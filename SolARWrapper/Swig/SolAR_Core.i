%module solar_core
%{
#include "core/Log.h"
#include "core/Messages.h"
#include "core/SolARFramework.h"
#include "core/SolARFrameworkDefinitions.h"
%}

%include "Swig.i"

%typemap(csimports) SWIGTYPE
%{
%}

///

%rename(CharList) std::vector<char const *>;
%template(CharList) std::vector<char const *>;

///

%ignore SolAR::getSolARFrameworkVersion(); //TODO Missing implementation
%include "core/SolARFramework.h"

%include "core/SolARFrameworkDefinitions.h"

//%include "SolARFrameworkDefinitions.i"
%ignore SolAR::Log::logger();
%include "core/Log.h"

//%include "Log.i"
%include "core/Messages.h"
