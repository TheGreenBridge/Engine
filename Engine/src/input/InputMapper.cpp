#include "InputMapper.h"
#include "../utils/Log.h"

namespace engine {	namespace input {

	InputMapper::InputMapper() {
		InputContext *context = new InputContext("gameplay");
		m_inputContexts.insert(std::make_pair("gameplay",context));
		pushContext("gameplay");
	}

	InputMapper::~InputMapper() {
		for (std::map<std::string, InputContext*>::iterator it = m_inputContexts.begin(); it != m_inputContexts.end(); ++it)
			delete it->second;
	}

	void InputMapper::dispatch() {
		// When empty nothing happens
		
		if (m_currentMappedInput.states.empty() && 
			m_currentMappedInput.actions.empty() && 
			m_currentMappedInput.ranges.empty()) return; 

		//LOG("Theres input");

		MappedInput input = m_currentMappedInput;
		for (std::multimap<int, InputCallback>::const_iterator iter = m_callbackTable.begin(); iter != m_callbackTable.end(); ++iter)
			(iter->second)(input);
		
	}

	void InputMapper::clear()
	{
		m_currentMappedInput.actions.clear();
		m_currentMappedInput.states.clear();
		m_currentMappedInput.ranges.clear();
	}

	void InputMapper::setRawButtonState(INPUTBUTTON button, bool pressed, bool previouslypressed)
	{
		ACTION action;
		STATE state;

		// Pressed the first time -> ACTION
		if (pressed && !previouslypressed)
		{
			if (MapButtonToAction(button, action))
			{
				m_currentMappedInput.actions.insert(action);
				return;
			}
		}

		// Pressed -> STATE
		if (pressed)
		{
			if (MapButtonToState(button, state))
			{
				m_currentMappedInput.states.insert(state);
				return;
			}
		}

		MapAndEatButton(button);
	}

	void InputMapper::setRawAxisValue(INPUTAXIS axis, F32 value)
	{
		for (std::list<InputContext*>::const_iterator iter = m_activeContexts.begin(); iter != m_activeContexts.end(); ++iter)
		{
			const InputContext* context = *iter;

			RANGE range;
			if (context->MapAxisToRange(axis, range))
			{
				m_currentMappedInput.ranges[range] = context->GetConversions().convert(range, value);
				break;
			}
		}
	}

	void InputMapper::pushContext(const std::string& name)
	{
		std::map<std::string, InputContext*>::iterator iter = m_inputContexts.find(name);
		if (iter == m_inputContexts.end())
			throw std::exception("Invalid input context pushed");

		m_activeContexts.push_front((iter->second));
	}

	void InputMapper::popContext()
	{
		if (m_activeContexts.empty())
			throw std::exception("Cannot pop input context, no contexts active!");

		m_activeContexts.pop_front();
	}

	bool InputMapper::MapButtonToAction(INPUTBUTTON button, ACTION& action) const {
		for (std::list<InputContext*>::const_iterator iter = m_activeContexts.begin(); iter != m_activeContexts.end(); ++iter)
		{
			const InputContext* context = *iter;

			if (context->MapButtonToAction(button, action))
				return true;
		}

		return false;
	}

	bool InputMapper::MapButtonToState(INPUTBUTTON button, STATE& state) const {
		for (std::list<InputContext*>::const_iterator iter = m_activeContexts.begin(); iter != m_activeContexts.end(); ++iter)
		{
			const InputContext* context = *iter;

			if (context->MapButtonToState(button, state))
				return true;
		}

		return false;
	}

	void InputMapper::MapAndEatButton(INPUTBUTTON button){
		ACTION action;
		STATE state;

		if (MapButtonToAction(button, action))
			m_currentMappedInput.EatAction(action);

		if (MapButtonToState(button, state))
			m_currentMappedInput.EatState(state);
	}

	void InputMapper::addCallback(InputCallback callback, int priority) {
		m_callbackTable.insert(std::make_pair(priority, callback));
	}

}}