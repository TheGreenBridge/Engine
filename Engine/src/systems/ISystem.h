#pragma once

///<summary>
/// Interface for a System
///</summary>

#include <common/types.h>

// MAKROS
#define REQUEST_MEMORY(type, N) static_cast<type*>(requestMemory(sizeof(type)*N)) 

namespace engine {
	// forward declaration
	class SystemManager;
	struct Event;

	class ISystem {
	protected:
		SystemManager *m_pManager;
		bool isInitialized = false;
		
	public:
		virtual void onEvent(engine::Event *event) = 0;

		virtual void update(const F32 dTime) = 0;

		virtual void startUp() = 0;

		virtual void shutDown() = 0;

		void setSystemManager(SystemManager *manager);

		void postEvent(engine::Event *e) const;

		void* requestMemory(size_t size) const;

		template<typename T>
		T* requestMemory(size_t N);
	};

	
}
