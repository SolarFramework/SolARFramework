%module xpcf_collection
%{
#include "xpcf/collection/ICollection.h"
#include "xpcf/collection/IEnumerable.h"
#include "xpcf/collection/IEnumerator.h"
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

%typemap(csimports) org::bcom::xpcf::IEnumerator
%{
	using System.Collections;
	using System.Collections.Generic;
	using XPCF.Core;
	using XPCF.Api;
	using XPCF.Properties;
%}
%extend org::bcom::xpcf::IEnumerator
{
	%typemap(csinterfaces) org::bcom::xpcf::IEnumerator %{global::System.IDisposable, IEnumerator<$typemap(cstype, T)>%}
	%proxycode %{
		public $typemap(cstype, T) Current { get { return current(); } }
		object IEnumerator.Current { get { return current(); } }
	%}
}
%rename(MoveNext) org::bcom::xpcf::IEnumerator::moveNext();
%rename(Reset) org::bcom::xpcf::IEnumerator::reset();
%ignore org::bcom::xpcf::IEnumerator::operator==;
%ignore org::bcom::xpcf::Iterator::operator=;
%ignore org::bcom::xpcf::Iterator::operator++;
%include "xpcf/collection/IEnumerator.h"

//%include "xpcf/collection/IEnumerator.i"
%typemap(csimports) org::bcom::xpcf::IEnumerable
%{
	using System.Collections;
	using System.Collections.Generic;
	using XPCF.Core;
	using XPCF.Api;
	using XPCF.Properties;
%}
%extend org::bcom::xpcf::IEnumerable
{
	%typemap(csinterfaces) org::bcom::xpcf::IEnumerable %{global::System.IDisposable, IEnumerable<$typemap(cstype, T)>%}
	%proxycode %{
		public IEnumerator<$typemap(cstype, T)> GetEnumerator() { return getEnumerator(); }
		IEnumerator IEnumerable.GetEnumerator() { return getEnumerator(); }
	%}
}
#pragma SWIG nowarn=320
%include "xpcf/collection/IEnumerable.h"

//%include "xpcf/collection/IEnumerable.i"
%include "xpcf/collection/ICollection.h"

///

%define ENUMERABLE(NAME, TYPE)
%shared_ptr(org::bcom::xpcf::IEnumerator<TYPE>)
%rename(NAME ## Enumerator) org::bcom::xpcf::IEnumerator<TYPE>;
%template(NAME ## Enumerator) org::bcom::xpcf::IEnumerator<TYPE>;
%rename(NAME ## Enumerable) org::bcom::xpcf::IEnumerable<TYPE>;
%template(NAME ## Enumerable) org::bcom::xpcf::IEnumerable<TYPE>;
%enddef

ENUMERABLE(UUID,				org::bcom::xpcf::uuids::uuid)
ENUMERABLE(ComponentMetadata,	SRef<org::bcom::xpcf::ComponentMetadata>)
ENUMERABLE(InterfaceMetadata,	SRef<org::bcom::xpcf::InterfaceMetadata>)
ENUMERABLE(Property,			SRef<org::bcom::xpcf::IProperty>)
ENUMERABLE(ModuleMetadata,		SRef<org::bcom::xpcf::ModuleMetadata>)
