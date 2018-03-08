#include "System.h"
//#include "messageing\Event.h"

#include "SystemManager.h"
#include "../utils/Log.h"


#define MEMORY_SIZE 10*1024 // 10 KiB

namespace engine {
	using namespace engine::memory;
	SystemManager::SystemManager() :
		m_allocator(1000*1024)
	{
		LOG("IN SystemManager Konstruktor");
		m_allocator.logStates();
	}

	SystemManager::~SystemManager() {

	}

	void SystemManager::update() {
		//for (int i = 0; i < m_systems.size; i++) {
		//	m_systems[i]->update();
		//}
	}

	void SystemManager::postEvent(Event *e) {
		for (size_t i = 0; i < m_systems.size(); i++) {
			m_systems[i]->onEvent(e);
		}
		//for (std::vector<ISystem*>::iterator it = m_systems.begin(); it != m_systems.end(); ++it) {
		//	(*it)->onEvent(e);						
		//}
	}


	void SystemManager::registerSystem(ISystem & system) {
		LOG("Registered System");
		m_systems.push_back(&system);
		system.setSystemManager(this);
	}

	void SystemManager::deregisterSystem(ISystem * system) {

	}

	void* SystemManager::requestMemory(size_t size) {
		return m_allocator.allocate(size);
	}

	template <typename T>
	T* SystemManager::requestMemory(size_t N) {
		union {
			void* as_void;
			T* as_T;
		};
		as_void = m_allocator.allocate(sizeof(T)*N);
		return as_T;
	}

	void SystemManager::testManager() {
		// To test the SystemManager for bugs
		
		m_allocator.logStates();
	}
}