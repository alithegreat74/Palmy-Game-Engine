#pragma once

#include <iostream>


extern Palmy::Application* Palmy::Create();

int main(int argc, char** argv) {
	Palmy::Log::Init();
	auto application = Palmy::Create();
	delete application;
	return 0;
}
