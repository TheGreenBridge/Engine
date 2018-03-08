#pragma once
#include "Event.h"
#include "types\KeyPressedEvent.h"

namespace engine {	namespace messaging {
	class EventHandler {
	public:
		virtual bool onEvent(Event *e);
		virtual bool onEvent(KeyPressedEvent *e);
	};

	class EventListener {
	public:
		void onEvent(Event *event);
	};
}}
