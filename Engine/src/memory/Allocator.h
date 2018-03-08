#pragma once
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

	struct blk {
		void* ptr;
		unsigned int size;
	};

	class Allocator {

	

	private:
		void *m_pBegin, *m_pLimit;
		void *m_pCurrentLocation;
		size_t m_allocSize;
		size_t m_freeStorage;
	public:
		Allocator(size_t size);
		~Allocator();
	
		unsigned int getFreeStorage();

		void *allocate(size_t size);

		void free(void *location, size_t size);
		void logStates() const;
		void expand(unsigned int size);
	};
}}