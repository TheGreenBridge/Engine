#include "LinearAllocator.h"

#include <utils/Log.h>
#include <common/state.h>

#include <stdlib.h>

namespace engine {	namespace memory {
	LinearAllocator::LinearAllocator(size_t size) {
		
		m_pBegin = malloc(size);
		// To increment size * 8 
		m_pLimit = static_cast<char*>(m_pBegin) + size;
		m_freeStorage = size;
		m_allocSize = size;
	#ifdef DEBUG
			LOG("Allocated Bytes", size);
	#endif
		m_pCurrentLocation = m_pBegin;
	}

	LinearAllocator::~LinearAllocator() {
	#ifdef DEBUG	
			LOG("Allocator destroyed!!");
	#endif
		std::free(m_pBegin);
	}

	void *LinearAllocator::allocate(size_t size) {
		if (size < m_freeStorage) {
			void *pMark = m_pCurrentLocation;
			// To increment size * 8 
			m_pCurrentLocation = static_cast<char*>(m_pCurrentLocation) + size;
			m_freeStorage -= size;
	#ifdef DEBUG	
			printf("Address of x is %p\n", (void *)pMark);
			LOG("Requested Memory in Bytes", size);
	#endif
			return pMark;
		}
		else {
	#ifdef DEBUG	
			LOG("Allocator", "Could not allocate memory!");
	#endif
			return nullptr;
		}
	}

	void LinearAllocator::free(void *location, size_t size) {
		std::free(location);
	}

	void LinearAllocator::logStates() const {
		LOG("Free Storage in Bytes", m_freeStorage);
		LOG("Allocated Storage in Bytes", m_allocSize);
	}

	void LinearAllocator::expand(unsigned int size) {
		// NO IMPLEMENTATION
	}

	unsigned int LinearAllocator::getFreeStorage() {
		return m_freeStorage;
	}

}}


