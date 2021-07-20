#ifndef _LIB_EXPORT
#define _LIB_EXPORT

#ifdef _MSC_VER
#    define LIBEXPORT __declspec(dllexport)
#    define LIBIMPORT __declspec(dllimport)
#elif defined(__GNUC__)
#    define LIBEXPORT __attribute__((visibility("default")))
#    define LIBIMPORT
#else
#    define LIBEXPORT
#    define EXPIMP_TEMPLATE
#pragma warning Unknown dynamic link import/export semantics.
#endif 

#endif// _LIB_EXPORT
