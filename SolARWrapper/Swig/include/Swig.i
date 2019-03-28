// Fix warnings
//%include "std_except.i" // Typemaps used by the STL wrappers that throw exceptions
//%include "director.swg" // support for director classes

// Common
%include "stdint.i" // SWIG library file for ISO C99 types: 7.18 Integer types <stdint.h>
%include "exception.i" // SWIG library file providing language independent exception handling
%include "swiginterface.i" // SWIG interface feature and typemaps implementation
%include "swigtype_inout.i" // support for input/output arguments
%include "typemaps.i" // Pointer and reference handling typemap library
%include "wchar.i" // Typemaps for the wchar_t type
%include "attribute.i" // convert a pair of set/get methods into a "native" attribute

// STD
%include "stl.i" // Initial STL definition
%include "std_array.i" // SWIG typemaps for std::array<T, N>
%include "std_auto_ptr.i" // allow to handle functions returning std::auto_ptr<>
%include "std_common.i" // define size_t 
//%include "std_complex.i" // Typemaps for handling std::complex<float> and std::complex<double>
%include "std_deque.i"
%include "std_except.i" // Typemaps used by the STL wrappers that throw exceptions
%include "std_map.i" // SWIG typemaps for std::map< K, T, C >
%include "std_pair.i" // SWIG typemaps for std::pair
//%include "std_shared_ptr.i" // boost_shared_ptr using std
%include "std_string.i" // Typemaps for std::string and const std::string&
%include "std_vector.i" // SWIG typemaps for std::vector<T>
%include "std_wstring.i" // Typemaps for std::wstring and const std::wstring&

// C#
%include "arrays_csharp.i" // two approaches to marshaling arrays
//%include "complex.i" // Typemaps for handling std::complex<float> and std::complex<double>
%include "csharp.swg" // C# typemaps
%include "csharphead.swg" // Support code for exceptions and strings if ...
%include "csharpkw.swg" // Warnings for C# keywords
//%include "director.swg" // support for director classes
%include "enums.swg" // C/C++ enums to be wrapped by proper C# enums
//%include "enumsimple.swg" // backwards compatible: Enums declared within a C++ class were wrapped by constant integers
//%include "enumtypesafe.swg" // Converts enum into class

// BOOST
%include "boost_intrusive_ptr.i" // SWIG_INTRUSIVE_PTR_TYPEMAPS SWIG_INTRUSIVE_PTR_TYPEMAPS_NO_WRAP  
%include "boost_shared_ptr.i" // SWIG_SHARED_PTR_TYPEMAPS 

// To use non-const std::string references
%apply const std::string & {std::string &};


%{
#include <xpcf/xpcf.h>
%}

%exception {
	try {
		$action
	}
	SWIG_CATCH_UNKNOWN // catch generic exception
}

/*
%exception {
	try {
		$action
	}
	catch(org::bcom::xpcf::Exception& e) {
		SWIG_exception(SWIG_RuntimeError, e.what());
	}
	SWIG_CATCH_STDEXCEPT // catch std::exception
	catch (...) {
		SWIG_exception(SWIG_UnknownError, "Unknown exception");
	}
}
*/

//%rename("%(camelcase)s") ""; //TODO
