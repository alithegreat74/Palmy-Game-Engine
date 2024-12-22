#pragma once
#include "Log.h"


#ifndef WINDOWS
	#error Palmy Only Supports Windows
#endif // !WINDOWS


#define ENGINE_ASSERT(X,...) if(!X){ENGINE_ERROR(__VA_ARGS__);__debugbreak;}

#define BIND_EVENT_FUNCTION(FUNC,TYPE,EVENT) EventHandler::Handle<TYPE>([&](const TYPE& event) { return FUNC(event); },EVENT);
