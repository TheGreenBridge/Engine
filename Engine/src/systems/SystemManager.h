//------------------------------------------------------
// File name:		SystemManager.h
// Author:			Christian Sommerauer
// Last Update:		09.04.2018
// Description:		Storage and entry point for systems
//------------------------------------------------------

#ifndef __SYSTEM_MANAGER_H__
#define __SYSTEM_MANAGER_H__
#pragma once

#include <vector>

#include <memory\allocator\LinearAllocator.h>
#include <utils\Time.h>
#include <common\types.h>

/// <summary>
/// This is the Manager for all systems
/// </summary>
/// <remarks>
///	is responsible for:
/// # bus system for messaging
///	# memory allocation for the systems
/// </remarks>

namespace engine {

	// Forward Declarations
	class ISystem;
	struct Event;
	
	using namespace engine::memory;

	class SystemManager {
	private: 
		std::vector<ISystem*> m_Systems;
		LinearAllocator m_Allocator;
		Time m_Time;
		U32 m_FPSCounter;
		U32 m_FPS;
		bool isActivated;
	public:
		
		SystemManager();
		~SystemManager();

		void startUp();
		void shutDown();
	
		void update();

		void registerSystem(ISystem & system);
		void deregisterSystem(ISystem * system);  // No Implementation
		void postEvent(Event *e);
		void* requestMemory(size_t size);

		template<typename T>
		T* requestMemory(size_t N);
		void testManager();

		U64 getDeltaTime() const;
		F32 getDeltaTimef() const;
		U32 getFPS() const;
	};
}

#endif //__SYSTEM_MANAGER_H__