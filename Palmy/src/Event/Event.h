#pragma once

#include <string>
#include <functional>

namespace Palmy {

	enum EventCategory {
		MouseEvent,
		KeyEvent,
		WindowEvent
	};
	enum EventType
	{
		MouseMoved, MouseClick, MouseResized,
		WindowResized,WindowClosed,
		KeyPressed,KeyReleased
	};


	class Event {
	public:
		virtual EventType GetEventType()const = 0;
		virtual EventCategory GetCategory()const = 0;
		virtual std::string ToString()const = 0;
		bool m_Handled = false;
	private:
	};


	class EventHandler {
	public:
		EventHandler() = delete;
		template<typename T>
		static bool Handle(std::function<bool(const T&)> function, T& e)
		{
			e.m_Handled |= function(e);
			return true;
		}
	};
}
