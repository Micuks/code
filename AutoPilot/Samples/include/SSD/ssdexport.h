#ifndef _SSD_EXPORT
#define _SSD_EXPORT

#ifdef SSD_STATIC
	#define SSDEXPORT
	#define SSDIMPORT
#else
	#ifdef _MSC_VER
	#    define SSDEXPORT __declspec(dllexport)
	#    define SSDIMPORT __declspec(dllimport)
	#elif defined(__GNUC__)
	#    define SSDEXPORT __attribute__((visibility("default")))
	#    define SSDIMPORT
	#else
	#    define SSDEXPORT
	#    define EXPIMP_TEMPLATE
	#pragma warning Unknown dynamic link import/export semantics.
	#endif
#endif

#endif// _SSD_EXPORT
