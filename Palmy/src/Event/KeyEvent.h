#pragma once
#include "Event.h"
#include <iostream>
namespace Palmy {

	class KeyEvent :public Event {
	public:
		KeyEvent(int keycode) :
			m_KeyCode(keycode)
		{

		}
		inline virtual int GetKey()const { return m_KeyCode; }
		virtual EventCategory GetCategory()const override { return EventCategory::KeyEvent; }
	protected:
		int m_KeyCode;
	};

	class KeyPressedEvent:public KeyEvent {
	public:
		KeyPressedEvent(int keycode) :
			KeyEvent(keycode) {}

		virtual EventType GetEventType()const override { return EventType::KeyPressed; }
		virtual std::string ToString()const override {
			return "KeyCode " + std::to_string(m_KeyCode) + "pressed";
		}
		static EventType GetStaticEventType(){ return EventType::KeyPressed; }
	};

	class KeyReleasedEvent :public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) :
			KeyEvent(keycode) {}

		virtual EventType GetEventType()const override { return EventType::KeyReleased; }
		virtual std::string ToString()const override {
			return "KeyCode " + std::to_string(m_KeyCode) + "released";
		}
		static EventType GetStaticEventType() { return EventType::KeyReleased; }
	};
}