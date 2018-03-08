#pragma once

#include"state.h"


#ifdef PLATFORM_WINDOWS
	#ifdef GB_CORE_DLL
		#define GB_API __declspec(dllexport)
	#else
		#define GB_API __declspec(dllimport)
	#endif
#else
	#define GB_API
#endif


