/// <summary>
///	This is the manager to handle all input
/// </summaray>
/// <remarks>
/// TASKS
///  # handles Input types of the platform
///  # what to do when input comes
/// </remarks>

// Class Header
#include "InputManager.h"

// MESSAGING
#include "../../systems/messageing/EventDispatcher.h"
#include "../../systems/messageing/types/KeyPressedEvent.h"

#include "../../systems/messageing/Event.h"

// DEBUG
#include "../../utils/Log.h"
#include "../../input/RawInput.h"


namespace engine {	

	using namespace engine::messaging;

	InputManager::InputManager() {
		for (int i = 0; i < 1024; i++) KEYS[i] = false;
		RawInput::setInputManager(this);
	}

	void InputManager::update(const F32 dTime) {
		
	}

	bool onKeyPressed(Event *in_event) {
		KeyPressedEvent *kpe = static_cast<KeyPressedEvent*> (in_event);
		LOG("Key Pressed is ");// +in_event->getKey());
		return true;
	}

	bool onKeyReleased(Event *in_event) {
		LOG("Key Released ");// +in_event->getKey());
		return true;
	}

	void InputManager::onEvent(Event *in_event) {
		//EventDispatcher dispatcher(in_event);
		////bool(*functionptr)(Event*) = onKeyPressed;
		//dispatcher.dispatch(EventType::EVENT_KEY_PRESSED, onKeyPressed);
		//dispatcher.dispatch(EventType::EVENT_KEY_RELEASED, onKeyReleased);

		switch (in_event->getType()) {
		case EventType::EVENT_INPUT:
		{KeyPressedEvent *kpe = static_cast<KeyPressedEvent*> (in_event); 
			//LOG("Key Released ", kpe->getKey());
		}
			break;	
		case EventType::EVENT_COLLISION:
			
			LOG("Collision detected!");
			break;
		
		/*case EventType::EVENT_KEY_RELEASED:
			KeyPressedEvent *kpe2 = static_cast<KeyPressedEvent*> (in_event);
			LOG("Key Released ", kpe2->getKey());
			break;*/
		}

	}	

	void InputManager::startUp() {

	}
	void InputManager::shutDown() {

	}
}
