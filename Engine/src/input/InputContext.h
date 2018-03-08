#pragma once

#include <map>
#include <common\types.h>
#include <string>

#include "inputconstants.h"
#include "rawinputconstants.h"
#include "RangeConverter.h"


//typedef std::string Action;
//typedef std::string State;
//typedef std::string Range;

namespace engine {	namespace input {

	class InputContext {
	private:
		std::string _name;
	
		std::map<INPUTBUTTON, ACTION> actionMap;
		std::map<INPUTBUTTON, STATE> stateMap;
		std::map<INPUTAXIS, RANGE> rangeMap;

		RangeConverter* m_converters;

	public:
		InputContext(std:: string contextName);
		~InputContext();

		bool MapButtonToAction(INPUTBUTTON button, ACTION& out) const;
		bool MapButtonToState(INPUTBUTTON button, STATE& out) const;
		bool MapAxisToRange(INPUTAXIS axis, RANGE& out) const;

		const RangeConverter& GetConversions() const
		{
			return *m_converters;
		}
	};
}}