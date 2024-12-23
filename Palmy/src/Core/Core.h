#pragma once
#include "Log.h"


#ifndef WINDOWS
	#error Palmy Only Supports Windows
#endif // !WINDOWS


#define ENGINE_ASSERT(X,...) if(!X){ENGINE_ERROR(__VA_ARGS__);__debugbreak;}

#define ENGINE_BIND(X) std::bind(&X,std::placeholders::_1)
#define ENGINE_BIND(X,I) std::bind(&X,I,std::placeholders::_1)
