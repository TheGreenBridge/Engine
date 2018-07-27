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
		
		LOG("Allocated Bytes", size);
		
		m_pCurrentLocation = m_pBegin;
	}

	LinearAllocator::~LinearAllocator() {
	
		LOG("Linear Allocator destroyed!!");

		std::free(m_pBegin);
	}

	blk LinearAllocator::allocate(size_t size) {
		blk allocation;
		if (size < m_freeStorage) {
			void *pMark = m_pCurrentLocation;
			// To increment size * 8 
			m_pCurrentLocation = static_cast<char*>(m_pCurrentLocation) + size;
			m_freeStorage -= size;

			//printf("Address of x is %p\n", (void *)pMark);
			LOG("Requested Memory in Bytes", size);

			
			allocation.ptr = pMark;
			allocation.size = size;
			
		}
		else {
	
			LOG("Allocator", "Could not allocate memory!");
			allocation.ptr = nullptr;
			allocation.size = 0;
		}

		return allocation;
	}

	void LinearAllocator::free(blk allocation) {
		//std::free(location);
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


