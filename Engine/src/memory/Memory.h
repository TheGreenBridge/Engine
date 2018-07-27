#pragma once

#include <EngineCore.h>

#define NEW_MEM new

template<typename T>
T* allocate()
{
	auto mem = engine::Engine::m_memoryMgr.allocate(sizeof(T));
	return new(mem.ptr) T;
}