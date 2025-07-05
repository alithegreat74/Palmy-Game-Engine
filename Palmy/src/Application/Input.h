#pragma once
#include <unordered_map>
#include "../Event/KeyEvent.h"
#include "../Event/MouseEvent.h"
#include "KeyCodes.h"
namespace Palmy
{
	class Input {
	public:
		//Uninitialized the constructors so we make sure there wont be an instance of the Input class
		Input() = delete;
		Input(const Input&) = delete;
		Input(Input&&) = delete;
		static void Init(void* window);
		//Keyboard inputs
		static bool GetKeyDown(KeyCode keyCode);
		static bool GetKeyUp(KeyCode keyCode);
		//Mouse Inputs
		static bool GetMouseButtonDown(KeyCode buttonCode);
		static bool GetMouseButtonUp(KeyCode buttonCode);
	private:
		inline static void* s_Window;
	};
}