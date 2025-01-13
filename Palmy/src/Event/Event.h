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
		MouseMoved, MouseClick, MouseScroll,
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

	template<typename T>
	using EventFunction = std::function<bool(const T&)>;

	class EventHandler {
	public:
		EventHandler() = delete;
		template<typename T>
		static bool Handle(const EventFunction<T>& function, Event& e)
		{
			if (e.GetEventType() != T::GetStaticEventType())
				return false;

			e.m_Handled |= function(static_cast<T&>(e));
			return true;
		}
	};
}
