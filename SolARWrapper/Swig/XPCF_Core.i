%module xpcf_core
%{
#include "xpcf/core/Exception.h"
#include "xpcf/core/refs.h"
#include "xpcf/core/Result.h"
#include "xpcf/core/uuid.h"
#include "xpcf/xpcf_api_define.h"
#include "xpcf/core/XPCFErrorCode.h"
%}

%include "Swig.i"

%typemap(csimports) SWIGTYPE
%{
%}

///

%include "xpcf/xpcf_api_define.h"

%rename (UUID) boost::uuids::uuid;
namespace boost {namespace uuids {class uuid{};}}
%csmethodmodifiers boost::uuids::uuid::ToString %{public override%};
%extend boost::uuids::uuid
{
	%proxycode
	%{
		public static implicit operator UUID(string uuidString) {return new UUID(uuidString);}
		public static implicit operator string(UUID uuid) {return uuid.ToString();}
	%}
	uuid(const char* uuidString) {return new boost::uuids::uuid(org::bcom::xpcf::toUUID(uuidString));}
	const std::string ToString() {return boost::uuids::to_string(*self);}
}
%ignore org::bcom::xpcf::toUUID(const char * uuidString);
%ignore org::bcom::xpcf::toUUID(const std::string & uuidString);
%include "xpcf/core/uuid.h"

namespace boost {namespace movelib {}}
%include "xpcf/core/refs.h"
#define SRef boost::shared_ptr
#define SPtr boost::shared_ptr

%include "xpcf/core/XPCFErrorCode.h"

//%include "xpcf/core/XPCFErrorCode.i"
%include "xpcf/core/Result.h"

///

//%include "xpcf/core/uuid.i"
//%include "xpcf/core/xpcf_api_define.i"
//%include "xpcf/core/XPCFErrorCode.i"

%ignore std::runtime_error;
namespace std{class runtime_error {};}
%ignore org::bcom::xpcf::Exception::Exception(const std::string & what, XPCFErrorCode errCode = XPCFErrorCode::_FAIL);
%ignore org::bcom::xpcf::AccessDeniedException::AccessDeniedException(const std::string & what);
%ignore org::bcom::xpcf::IllegalStateException::IllegalStateException(const std::string & what);
%ignore org::bcom::xpcf::ModuleException::ModuleException(const std::string & what, XPCFErrorCode errCode = XPCFErrorCode::_FAIL);
%ignore org::bcom::xpcf::NotImplementedException::NotImplementedException(const std::string & what);
%ignore org::bcom::xpcf::NullPointerException::NullPointerException(const std::string & what);
%ignore org::bcom::xpcf::TimeoutException::TimeoutException(const std::string & what);
%ignore org::bcom::xpcf::UUIDNotFoundException::UUIDNotFoundException(const std::string & what, XPCFErrorCode errCode = XPCFErrorCode::_FAIL);
%ignore org::bcom::xpcf::ComponentNotFoundException::ComponentNotFoundException(const std::string & what);
%ignore org::bcom::xpcf::InterfaceNotImplementedException::InterfaceNotImplementedException(const std::string & what);
%ignore org::bcom::xpcf::ModuleNotFoundException::ModuleNotFoundException(const std::string & what);
%include "xpcf/core/Exception.h"
