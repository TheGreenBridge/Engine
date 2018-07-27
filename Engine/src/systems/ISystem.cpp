#include "SystemManager.h"
#include "messageing\Event.h"
#include "ISystem.h"

#include "../utils/Log.h"


namespace engine {
	
	void ISystem::postEvent(Event *e) const {
		if (m_pManager == nullptr) LOG("SystemManager is nullptr");
		else m_pManager->postEvent(e);
	}

	void ISystem::setSystemManager(SystemManager *manager) {
		m_pManager = manager;
	}

	void* ISystem::requestMemory(size_t size) const	{
		return m_pManager->requestMemory(size);
	}

	template <typename T>
	T* ISystem::requestMemory(size_t N) {
		union {
			void* as_void;
			T* as_T;
		};
		as_void = m_pManager->requestMemory(sizeof(T)*N);
		return as_T;
	}
}
	

