#pragma once



#ifndef BUILD_STATIC
# if defined(DESIGN_PATTERNS_LIB)
#  define DESIGN_PATTERNS_EXPORT __declspec(dllexport)
# else
#  define DESIGN_PATTERNS_EXPORT __declspec(dllimport)
# endif
#else
# define DESIGN_PATTERNS_EXPORT
#endif