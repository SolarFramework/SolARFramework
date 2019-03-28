%module xpcf_properties
%{
#include "xpcf/properties/IProperty.h"
#include "xpcf/properties/IPropertyMap.h"
%}

%include "Swig.i"

%import (module="XPCF.Core") "XPCF_Core.i"
%import (module="XPCF.Collection") "XPCF_Collection.i"

%typemap(csimports) SWIGTYPE
%{
    using XPCF.Core;
    using XPCF.Collection;
%}

///

%shared_ptr(org::bcom::xpcf::IProperty)
%shared_ptr(org::bcom::xpcf::IPropertyMap)

///

%include "xpcf/properties/IProperty.h"

//%include "xpcf/properties/IProperty.i"
//TODO
/*
%apply bool & INOUT { bool & wrappedValue };
%apply signed char & INOUT { signed char & wrappedValue };
%apply unsigned char & INOUT { unsigned char & wrappedValue };
%apply short & INOUT { short & wrappedValue };
%apply unsigned short & INOUT { unsigned short & wrappedValue };
%apply int & INOUT { int & wrappedValue };
%apply unsigned int & INOUT { unsigned int & wrappedValue };
%apply long & INOUT { long & wrappedValue };
%apply unsigned long & INOUT { unsigned long & wrappedValue };
%apply long long & INOUT { long long & wrappedValue };
%apply unsigned long long & INOUT { unsigned long long & wrappedValue };
%apply float & INOUT { float & wrappedValue };
%apply double & INOUT { double & wrappedValue };
*/

%ignore org::bcom::xpcf::IPropertyMap::wrapInteger;
%ignore org::bcom::xpcf::IPropertyMap::wrapUnsignedInteger;
%ignore org::bcom::xpcf::IPropertyMap::wrapLong;
%ignore org::bcom::xpcf::IPropertyMap::wrapUnsignedLong;
%ignore org::bcom::xpcf::IPropertyMap::wrapFloat;
%ignore org::bcom::xpcf::IPropertyMap::wrapDouble;
%ignore org::bcom::xpcf::IPropertyMap::wrapString;
%ignore org::bcom::xpcf::IPropertyMap::wrapUnicodeString;
%ignore org::bcom::xpcf::IPropertyMap::wrapStructure;

%ignore org::bcom::xpcf::IPropertyMap::wrapIntegerVector;
%ignore org::bcom::xpcf::IPropertyMap::wrapUnsignedIntegerVector;
%ignore org::bcom::xpcf::IPropertyMap::wrapLongVector;
%ignore org::bcom::xpcf::IPropertyMap::wrapUnsignedLongVector;
%ignore org::bcom::xpcf::IPropertyMap::wrapFloatVector;
%ignore org::bcom::xpcf::IPropertyMap::wrapDoubleVector;
%ignore org::bcom::xpcf::IPropertyMap::wrapStringVector;
%ignore org::bcom::xpcf::IPropertyMap::wrapUnicodeStringVector;
%ignore org::bcom::xpcf::IPropertyMap::wrapStructureVector;

%include "xpcf/properties/IPropertyMap.h"
