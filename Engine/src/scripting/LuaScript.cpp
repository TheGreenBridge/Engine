#include "LuaScript.h"
#include <iostream>

#define SCRIPT_PATH "res/entities/"

LuaScript::LuaScript(const std::string& file)
{
	L = luaL_newstate();
	luaL_openlibs(L);
	level = 0;

	if (luaL_dofile(L, (/*SCRIPT_PATH +*/ file).c_str()) ) {
		LOG_ERROR("script not loaded");
		L = 0;
	}
}

LuaScript::~LuaScript()
{
	if (L) lua_close(L);
	
}

void LuaScript::printError(const std::string& variableName, const std::string& reason) {
	std::cout << "Error: can't get [" << variableName << "]. " << reason << std::endl;
}

void LuaScript::callFunction(const std::string & functionName)
{
	lua_getglobal(L, functionName.c_str());
	lua_call(L, 0, 0);
}


