#pragma once
#include "Event.h"

namespace Palmy {
	class WindowEvent :public Event {
	public:
		virtual EventCategory GetCategory()const override { return EventCategory::WindowEvent; }
	};

	class WindowResizedEvent :public WindowEvent {
	public:
		WindowResizedEvent(float width, float height) :
			m_Width(width), m_Height(height) {}
		virtual EventType GetEventType()const override { return EventType::WindowResized; }
		virtual std::string ToString()const override {
			return "Window Resized To {" + std::to_string(m_Width) + ", " + std::to_string(m_Height) + "}";
		}
		static EventType GetStaticEventType() { return EventType::WindowResized; }
	public:
		float m_Width, m_Height;
	};
	
	class WindowClosedEvent :public WindowEvent {
	public:
		virtual EventType GetEventType()const override { return EventType::WindowClosed; }
		virtual std::string ToString()const override {
			return "Window Closed";
		}
		static EventType GetStaticEventType() { return EventType::WindowClosed; }
	};
}