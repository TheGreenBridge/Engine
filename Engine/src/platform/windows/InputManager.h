#pragma once

/// <summary>base class for an event </summary>
///

#include "../../systems/System.h"
#include "../../input/MappedInput.h"
#include "../../input/InputMapper.h"
#include <map>

namespace engine {	

	using namespace engine::input;
	// forward declaration
	struct Event;
	
	class InputManager : public ISystem{
	private:
		
	public:
		InputMapper mapper;
		bool KEYS[1024];

		InputManager();

		void update(const F32 dTime);
		void onEvent(Event *in_event);

		//void registerCallback(InputCallback callback);

		void startUp();
		void shutDown();


	};
}
