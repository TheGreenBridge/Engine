#pragma once

#include "InputContext.h"
#include <set>
#include <list>
#include <functional>

namespace engine {	namespace input {

	struct MappedInput {
		std::set<ACTION> actions;
		std::set<STATE> states;
		std::map<RANGE, F32> ranges;

		bool find(STATE state) { return states.find(state) != states.end(); }
		bool find(ACTION action) { return actions.find(action) != actions.end(); }

		// Consumption helpers
		void EatAction(ACTION action) { actions.erase(action); }
		void EatState(STATE state) { states.erase(state); }
		void EatRange(RANGE range)
		{
			std::map<RANGE, F32>::iterator iter = ranges.find(range);
			if (iter != ranges.end())
				ranges.erase(iter);
		}
	};

	//typedef void(*InputCallback)(MappedInput& inputs);
	typedef std::function<void(MappedInput &inputs)> InputCallback;

	class InputMapper {
	private:
		std::map<std::string, InputContext*> m_inputContexts;
		std::list<InputContext*> m_activeContexts;
		std::multimap<int, InputCallback> m_callbackTable;
		MappedInput m_currentMappedInput;

		// Helper functions
		bool MapButtonToAction(INPUTBUTTON button, ACTION& action) const;
		bool MapButtonToState(INPUTBUTTON button, STATE& state) const;
		void MapAndEatButton(INPUTBUTTON button);

	public:
		InputMapper();
		~InputMapper();

		void clear();
		void setRawButtonState(INPUTBUTTON button, bool pressed, bool previouslypressed);
		void setRawAxisValue(INPUTAXIS axis, F32 value);

		void addCallback(InputCallback callback, int priority);
	
		void pushContext(const std::string& contextName);
		void popContext();
		
		void dispatch();
	};

}}