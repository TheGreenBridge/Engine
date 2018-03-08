#pragma once

#include "../Event.h"

namespace engine {	

	class KeyPressedEvent : public Event {
	private:
		char m_key;
	public:
		KeyPressedEvent(char key) : Event(EventType::EVENT_INPUT), m_key(key) { }
		char getKey() { return m_key; }
	};

}