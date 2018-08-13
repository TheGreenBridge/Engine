#pragma once

#include <memory/LookupHandle.h>
#include <memory/allocator/PoolAllocator.h>

namespace engine {
	namespace memory {

		class IPoolContainer 
		{

		};

		template<typename T>
		class PoolContainer : public IPoolContainer{
		private:
			LookupHandle<T> m_Handle;
			PoolAllocator<T> m_Allocator;
		public:

			explicit PoolContainer(IAllocator* allocator, size_t size);
			~PoolContainer();

			template <typename... arguments>
			T* newElement(U32 id, arguments&&... args);

			void deleteElement(U32 id);

			T* getElement(U32 id) const;

			U32 getElementNumber() const;

			// Deleted Ctor
			PoolContainer() = delete;
			PoolContainer(const PoolContainer&) = delete;
			PoolContainer(PoolContainer&&) = delete;
			PoolContainer& operator=(const PoolContainer&) = delete;
			PoolContainer& operator=(PoolContainer&&) = delete;
		};
	}
}

// IMPLEMENTATION

namespace engine {
	namespace memory {

		template <typename T>
		PoolContainer<T>::PoolContainer(IAllocator* allocator, size_t size)
			: m_Allocator(allocator, size)
		{
			
		}
		template <typename T>
		PoolContainer<T>::~PoolContainer()
		{

		}

		template <typename T>
		template <typename... arguments>
		T* PoolContainer<T>::newElement(U32 id, arguments&&... args) {
			T* element = m_Allocator.allocate(std::forward<arguments>(args)...);
			m_Handle.insertEntry(id, element);
			return element;
		}

		template <typename T>
		void PoolContainer<T>::deleteElement(U32 id) {

			m_Allocator.deallocate(m_Handle.getEntry(id));
			m_Handle.deleteEntry(id);

		}

		template <typename T>
		T* PoolContainer<T>::getElement(U32 id) const {
			return m_Handle.getEntry(id);
		}

		template <typename T>
		U32 PoolContainer<T>::getElementNumber() const {
			return m_Allocator.
		}
	}
}