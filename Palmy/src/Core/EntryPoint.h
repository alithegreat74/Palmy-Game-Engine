#pragma once

#include <iostream>
#include <Palmy.h>


extern Palmy::Application* Palmy::Create();

int main(int argc, char** argv) {
	Palmy::Log::Init();
	auto application = Palmy::Create();
	application->Run();
	delete application;
	return 0;
}
