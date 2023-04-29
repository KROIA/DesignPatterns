#pragma once

// Library metainfo
#define UTILITIES_LIB_VERSION "00.00.00"
#define   UTILITIES_LIB_AUTOR "Alex Krieg"
#define    UTILITIES_LIB_DATE __DATE__

#ifdef _DEBUG 
#define UTILITIES_LIB_BUILD_TYPE "Debug"
#else
#define UTILITIES_LIB_BUILD_TYPE "Release"
#endif

#ifndef BUILD_STATIC
# if defined(UTILITIES_LIB)
#  define UTILITIES_EXPORT __declspec(dllexport)
# else
#  define UTILITIES_EXPORT __declspec(dllimport)
# endif
#else
# define UTILITIES_EXPORT
#endif

#ifndef __GNUC__
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif



namespace Utilities
{
	struct Info
	{
		UTILITIES_EXPORT static const char* version;
		UTILITIES_EXPORT static const char* autor;
		UTILITIES_EXPORT static const char* date;
		UTILITIES_EXPORT static const char* buildType;
	};


	class ObjectManager;
	class Object;
}