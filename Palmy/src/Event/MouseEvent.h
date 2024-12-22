#pragma once
#include "Event.h"

namespace Palmy {
	class MouseEvent :public Event {
	public:
		virtual EventCategory GetCategory()const override { return EventCategory::MouseEvent; }
	};

	class MouseClickedEvent :public MouseEvent {
	public:
		MouseClickedEvent(int buttonCode) :
			m_ButtonCode(buttonCode){}
		virtual EventType GetEventType()const override { return EventType::MouseClick; }
		virtual std::string ToString()const override {
			return "Mouse Button " + std::to_string(m_ButtonCode) + " Clicked";
		}
		static EventType GetStaticEventType() { return EventType::MouseClick; }
	private:
		int m_ButtonCode;
	};
	class MouseMovedEvent :public MouseEvent {
		MouseMovedEvent(float xPos,float yPos):
			m_XPosition(xPos),m_YPosition(yPos){}
		virtual EventType GetEventType()const override { return EventType::MouseMoved; }
		virtual std::string ToString()const override {
			return "Mouse moved to {" + std::to_string(m_XPosition) + ", " + std::to_string(m_YPosition) + "}";
		}
		static EventType GetStaticEventType() { return EventType::MouseMoved; }
	private:
		float m_XPosition, m_YPosition;
	};

	class MouseScrolledEvent :public MouseEvent {
	public:
		MouseScrolledEvent(float distance) :
			m_Distance(distance) {}
		virtual EventType GetEventType()const override { return EventType::MouseClick; }
		virtual std::string ToString()const override {
			return "Mouse scrolled by" + std::to_string(m_Distance) + " distance";
		}
		static EventType GetStaticEventType() { return EventType::MouseClick; }
	private:
		int m_Distance;
	};

}