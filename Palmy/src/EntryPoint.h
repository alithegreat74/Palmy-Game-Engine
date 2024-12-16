#pragma once

#include <iostream>
#include "Application.h"

extern Palmy::Application* Palmy::Create();

int main(int argc, char** argv) {
	auto application = Palmy::Create();
	std::cout << "Hello World!\n";
	application->Run();
	delete application;
	return 0;
}
