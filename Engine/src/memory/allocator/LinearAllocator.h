#pragma once

#include <memory\allocator\IAllocator.h>

namespace engine {	namespace memory {

	template <class T> 
	struct TypeAndCount
	{
	};

	template <class T, size_t N> 
	struct TypeAndCount<T[N]>
	{
		typedef T Type;
		static const size_t Count = N;
	};
	
	struct memInfo {
		void *pBegin;
		void *pLimit;
		memInfo *next;
	};

	

	class LinearAllocator : public IAllocator {

	private:
		void *m_pBegin, *m_pLimit;
		void *m_pCurrentLocation;
		U32 m_allocSize;
		U32 m_freeStorage;
	public:
		LinearAllocator(U32 size);
		~LinearAllocator();
	
		unsigned int getFreeStorage();

		blk allocate(U32 size);

		void deallocate(blk allocation);

		void logStates() const;
		void expand(unsigned int size);
	};
}}