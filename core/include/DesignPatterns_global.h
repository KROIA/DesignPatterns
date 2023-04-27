#pragma once

#define DESIGN_PATTERNS_LIB_VERSION "00.00.00"
#define   DESIGN_PATTERNS_LIB_AUTOR "Alex Krieg"
#define    DESIGN_PATTERNS_LIB_DATE __DATE__



#ifdef _DEBUG 
#define DESIGN_PATTERNS_LIB_BUILD_TYPE "Debug"
#else
#define DESIGN_PATTERNS_LIB_BUILD_TYPE "Release"
#endif


#ifndef BUILD_STATIC
# if defined(DESIGN_PATTERNS_LIB)
#  define DESIGN_PATTERNS_EXPORT __declspec(dllexport)
# else
#  define DESIGN_PATTERNS_EXPORT __declspec(dllimport)
# endif
#else
# define DESIGN_PATTERNS_EXPORT
#endif

namespace DesignPatterns
{
	struct DESIGN_PATTERNS_EXPORT Info
	{
		static const char* version;
		static const char* autor;
		static const char* date;
		static const char* buildType;
	};


	class ObjectManager;
	class Object;
}