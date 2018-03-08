#pragma once

#include "../Event.h"

namespace engine {

	class AnimationEvent : public Event {
	private:
		unsigned int ID;
		bool state;
	public:
		AnimationEvent(unsigned int ID, bool state) : Event(EventType::EVENT_ANIMATION), ID(ID), state(state) { }
		unsigned int getID() { return ID; }
		bool getState() { return state; }
	};

}