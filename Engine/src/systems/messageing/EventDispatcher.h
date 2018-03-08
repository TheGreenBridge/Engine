#pragma once
#include "Event.h"
#include "EventHandler.h"

namespace engine {
	
	// Function Pointer Interface
	//typedef bool(*callback_function)(Event);

	namespace messaging {
		class EventDispatcher {
		private:
			Event *m_event;
		public:
			EventDispatcher(Event *event) : m_event(event) { }
			void dispatch(EventType type, bool(*callback_function)(Event*)) {
				if (m_event->handled) true;
				if (m_event->getType() == type) {
					m_event->handled = callback_function(m_event);
				}
			}
		};
}}
