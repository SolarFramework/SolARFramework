%module xpcf_api
%{
#include "xpcf/api/ComponentMetadata.h"
#include "xpcf/api/IComponentIntrospect.h"
#include "xpcf/api/IComponentManager.h"
#include "xpcf/api/IConfigurable.h"
#include "xpcf/module/IModuleIndex.h"
#include "xpcf/api/IModuleManager.h"
#include "xpcf/api/InterfaceMetadata.h"
#include "xpcf/api/ModuleMetadata.h"
#include "xpcf/xpcf.h"
%}

%include "Swig.i"

%import (module="XPCF.Core") "XPCF_Core.i"
%import (module="XPCF.Collection") "XPCF_Collection.i"
%import (module="XPCF.Properties") "XPCF_Properties.i"
%import (module="XPCF.Traits") "XPCF_Traits.i"

%typemap(csimports) SWIGTYPE
%{
    using XPCF.Core;
    using XPCF.Collection;
    using XPCF.Properties;
    using XPCF.Traits;
%}

///

%shared_ptr(org::bcom::xpcf::ComponentMetadata)
%shared_ptr(org::bcom::xpcf::IComponentIntrospect)
%shared_ptr(org::bcom::xpcf::IComponentManager)
%shared_ptr(org::bcom::xpcf::IConfigurable)
%shared_ptr(org::bcom::xpcf::IModuleManager)
%shared_ptr(org::bcom::xpcf::InterfaceMetadata)
%shared_ptr(org::bcom::xpcf::ModuleMetadata)

///

%ignore org::bcom::xpcf::InterfaceMetadata::InterfaceMetadata(const InterfaceMetadata & other);
%ignore org::bcom::xpcf::InterfaceMetadata::operator=;
%ignore org::bcom::xpcf::InterfaceMetadata::operator==;
//%nodefaultctor org::bcom::xpcf::InterfaceMetadata;
%include "xpcf/api/InterfaceMetadata.h"

//%include "xpcf/api/InterfaceMetadata.i"
namespace boost{namespace filesystem{}}
%ignore org::bcom::xpcf::ComponentMetadata::ComponentMetadata(const ComponentMetadata & other);
%ignore org::bcom::xpcf::ComponentMetadata::operator=;
%ignore org::bcom::xpcf::ComponentMetadata::operator==;
%include "xpcf/api/ComponentMetadata.h"

//%include "xpcf/api/ComponentMetadata.i"
%ignore org::bcom::xpcf::IModuleIndex; //TODO Multiple inheritance
//%interface_impl(org::bcom::xpcf::IModuleIndex);
//%shared_ptr(org::bcom::xpcf::IModuleIndex)
//TODO: Change constructor, and add 4 methods
%include "xpcf/module/IModuleIndex.h"

//%include "xpcf/api/IModuleIndex.i"
//%include "xpcf/api/InterfaceMetadata.i"
%ignore org::bcom::xpcf::ModuleMetadata::getFullPath() const;
%include "xpcf/api/ModuleMetadata.h"

//%include "xpcf/api/InterfaceMetadata.i"
%ignore org::bcom::xpcf::IComponentIntrospect::getMetadata;
%include "xpcf/api/IComponentIntrospect.h"
%rename(queryInterface) org::bcom::xpcf::IComponentIntrospect::queryInterface<org::bcom::xpcf::IComponentIntrospect>;
%template(queryInterface) org::bcom::xpcf::IComponentIntrospect::queryInterface<org::bcom::xpcf::IComponentIntrospect>;

//%include "xpcf/api/IComponentIntrospect.i"
//%include "xpcf/api/InterfaceMetadata.i"
//%include "xpcf/api/ComponentMetadata.i"
//%include "xpcf/api/ModuleMetadata.i"
%include "xpcf/api/IComponentManager.h"

//%include "xpcf/api/IComponentIntrospect.i"
%include "xpcf/api/IConfigurable.h"

//%include "xpcf/api/IComponentIntrospect.i"
//%include "xpcf/api/ModuleMetadata.i"
%include "xpcf/api/IModuleManager.h"

//%include "xpcf/api/IComponentManager.i"
//%include "xpcf/api/IConfigurable.i"
%include "xpcf/xpcf.h"
