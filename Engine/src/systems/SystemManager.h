#pragma once

#include <vector>
#include <memory/allocator/LinearAllocator.h>

/// <summary>
/// This is the Manager for all systems
/// </summary>
/// <remarks>
///	is responsible for:
/// # bus system for messaging
///	# memory allocation for the systems
/// </remarks>

/*
(Sumi) Thoughts

default Systems

InputManager;
AnimationManager;
RenderManager;
CollisionManager;
AudioManager;

EntityManager;


*/

namespace engine {
	class ISystem;
	struct Event;
	
	using namespace engine::memory;

	class SystemManager {
	private: 
		std::vector<ISystem*> m_systems;
		LinearAllocator m_allocator;
	public:
		
		SystemManager();
		~SystemManager();
	
		void update();

		void registerSystem(ISystem & system);
		void deregisterSystem(ISystem * system);  // No Implementation
		void postEvent(Event *e);
		void* requestMemory(size_t size);

		template<typename T>
		T* requestMemory(size_t N);

		

		void testManager();
	};
}
