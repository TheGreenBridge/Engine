#include "InputContext.h"
#include "../utils/FileUtils.h"
#include "../utils/xmlreader/rapidxml.hpp"
#include "../utils/Log.h"
#include <sstream>


namespace engine {	namespace input {
	using namespace rapidxml;

	InputContext::InputContext(std::string contextName) : _name(contextName) {
		/*stateMap.insert(std::make_pair(INPUTBUTTON::arrow_left, STATE::player_left));
		stateMap.insert(std::make_pair(INPUTBUTTON::arrow_down, STATE::player_down));
		stateMap.insert(std::make_pair(INPUTBUTTON::arrow_right, STATE::player_right));
		stateMap.insert(std::make_pair(INPUTBUTTON::arrow_up, STATE::player_up));

		stateMap.insert(std::make_pair(INPUTBUTTON::space, STATE::camera_up));
		stateMap.insert(std::make_pair(INPUTBUTTON::a, STATE::camera_left));
		stateMap.insert(std::make_pair(INPUTBUTTON::d, STATE::camera_right));
		stateMap.insert(std::make_pair(INPUTBUTTON::c, STATE::camera_down));
		stateMap.insert(std::make_pair(INPUTBUTTON::w, STATE::camera_forward));
		stateMap.insert(std::make_pair(INPUTBUTTON::s, STATE::camera_backward));

		actionMap.insert(std::make_pair(INPUTBUTTON::n, ACTION::change_camera_debug));
		actionMap.insert(std::make_pair(INPUTBUTTON::m, ACTION::change_camera_3rdperson));
		
		
		rangeMap.insert(std::make_pair(INPUTAXIS::mouse_x, RANGE::camera_x));
		rangeMap.insert(std::make_pair(INPUTAXIS::mouse_x, RANGE::camera_y));*/

		m_converters = new RangeConverter("");
		std::string text = FileUtils::read_file("res/inputmapping/default_input_context.xml");
		xml_document<> doc;
		doc.parse<0>(&text[0]);
		std::string nodename(doc.first_node()->name());
		xml_node<> *root = doc.first_node("inputcontext");		
		xml_node<> *node = root->first_node("mapping")->first_node("states");
		for (xml_node<> *state = node->first_node("state"); state; state = state->next_sibling()) {		
			std::stringstream sInput(state->first_attribute("input")->value());
			std::stringstream sOutput(state->first_attribute("output")->value());		
			int input, output;		
			sInput >> input;
			sOutput >> output;
			stateMap.insert(std::make_pair((INPUTBUTTON)input, (STATE)output));
		}
		node = root->first_node("mapping")->first_node("actions");
		for (xml_node<> *action = node->first_node("action"); action; action = action->next_sibling()) {
			std::stringstream sInput(action->first_attribute("input")->value());
			std::stringstream sOutput(action->first_attribute("output")->value());
			int input, output;
			sInput >> input;
			sOutput >> output;
			actionMap.insert(std::make_pair((INPUTBUTTON)input, (ACTION)output));
		}
	}

	InputContext::~InputContext() {
		delete m_converters;
	}

	bool InputContext::MapButtonToAction(INPUTBUTTON button, ACTION& out) const {
		std::map<INPUTBUTTON, ACTION>::const_iterator it = actionMap.find(button);
		if (it == actionMap.end()) return false;
		out = it->second;
		return true;
	}

	bool InputContext::MapButtonToState(INPUTBUTTON button, STATE& out) const {
		std::map<INPUTBUTTON, STATE>::const_iterator it = stateMap.find(button);
		if (it == stateMap.end()) return false;
		out = it->second;
		return true;
	}

	bool InputContext::MapAxisToRange(INPUTAXIS axis, RANGE& out) const {
		std::map<INPUTAXIS, RANGE>::const_iterator it = rangeMap.find(axis);
		if (it == rangeMap.end()) return false;
		out = it->second;
		return true;
	}
}}