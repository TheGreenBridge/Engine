#pragma once
namespace engine { 
		enum class EventType {
			EVENT_COLLISION,
			EVENT_DRAWCALL,
			EVENT_INPUT,
			EVENT_KEY_PRESSED,
			EVENT_KEY_RELEASED,

			// ANIMATION
			EVENT_ANIMATION,
		};

		struct Event {
		private: 
			EventType type;
		public: 
			bool handled;

			Event(EventType type): type(type){}
			EventType getType() { return type; }
		};

}


