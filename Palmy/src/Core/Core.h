#pragma once
#include "Log.h"


#ifndef WINDOWS
	#error Palmy Only Supports Windows
#endif // !WINDOWS


#define ENGINE_ASSERT(X,...) if(!X){ENGINE_ERROR(__VA_ARGS__);__debugbreak;}

#define ENGINE_BIND(X) [this](auto&&... args) { return X(std::forward<decltype(args)>(args)...); }

