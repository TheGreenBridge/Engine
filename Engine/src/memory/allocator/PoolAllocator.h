//------------------------------------------------------------------------------
// PoolAllocator.h
//
// Holds several slots of T objects. Every slot is the same size. 
// Allocations happens through a free list, which connects all free slots in 
// the pool.
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 17.08.18
//------------------------------------------------------------------------------
//

#pragma once

#include <common\types.h>
#include <memory\allocator\IAllocator.h>
#include <utils\Log.h>
// std
#include <memory>

namespace engine {
	namespace memory {

		template <typename T>
		struct PoolChunk 
		{
			union 
			{
				T value;
				PoolChunk<T> *nextPoolChunk;
			};
			BOOL allocated;

			PoolChunk() {};
			~PoolChunk() {};
		};

		template <typename T>
		class PoolIterator
		{
		public:
			PoolIterator& operator=(const PoolIterator& other)
			{
				m_item = other.m_item;
			}

			PoolIterator& operator++()
			{
				m_item++;
				return *this;
			}

			const T& operator->()
			{

				return *m_item;
			}

			const T& operator*()
			{

				return m_item->value;
			}

			BOOL operator!=(const PoolIterator& other)
			{
				if (m_item == other.m_item)
				{
					return false;
				}
				else
				{
					return true;
				}
			}

			BOOL operator==(const PoolIterator& other)
			{
				return !operator!=(other);
			}

			PoolChunk<T>* m_item;
		};

		template <typename T>
		class PoolAllocator
		{
		public:

			

		public:
			explicit PoolAllocator(IAllocator *parentAllocator, U32 size = POOLALLOCATORDEFAULTSIZE);
			~PoolAllocator();



			template <typename... arguments>
			T* allocate(arguments&&... args);

			void deallocate(T* data);

			U32 getSize() const;
			U32 getAllocations() const;

			PoolIterator<T> begin();
			PoolIterator<T> end();

			// Deleted Ctor
			PoolAllocator() = delete;
			PoolAllocator(const PoolAllocator &other) = delete; // Copy Cstr
			PoolAllocator(const PoolAllocator &&other) = delete; // Move Cstr
			PoolAllocator& operator= (const PoolAllocator &other) = delete; // Copy Assignment
			PoolAllocator& operator= (const PoolAllocator &&other) = delete; // Move Assignment

		private:

			static const U32 POOLALLOCATORDEFAULTSIZE = 1024;
		
			U32 m_OpenAllocations = 0;

			U32 m_Size = 0;

			PoolChunk<T> *m_Data = nullptr;
			PoolChunk<T> *m_Head = nullptr;

			IAllocator* m_ParentAllocator = nullptr;
			bool m_needsToDeleteParentAllocator = false;

		};
	}
}

// IMPLEMENTATION

namespace engine {
	namespace memory {

		template <typename T>
		PoolAllocator<T>::PoolAllocator(IAllocator *parentAllocator, U32 size = POOLALLOCATORDEFAULTSIZE)
			: m_Size(size), m_ParentAllocator(parentAllocator)
		{
			if (parentAllocator == nullptr) {
				LOG_ERROR("parent allocator is nullptr");
				//m_ParentAllocator = new Allocator();
				//m_needsToDeleteParentAllocator = true;
			}
			blk allocation = m_ParentAllocator->allocate(m_Size * sizeof(PoolChunk<T>));// new PoolChunk<T>[size];
			m_Data = static_cast<PoolChunk<T>*>(allocation.ptr);
			m_Head = m_Data;

			for (U32 i = 0; i < m_Size - 1; ++i)
			{
				m_Data[i].nextPoolChunk = std::addressof(m_Data[i + 1]);
				m_Data[i].allocated = false;
			}
			m_Data[m_Size - 1].nextPoolChunk = nullptr;
			m_Data[m_Size - 1].allocated = false;
		}


		template <typename T>
		PoolAllocator<T>::~PoolAllocator()
		{
			if (m_OpenAllocations != 0) {
				LOG_ERROR("Open allocations");
			}

			//m_ParentAllocator->deallocate(m_Data, m_Size);
			//if (m_needsToDeleteParentAllocator)
			//{
			//	delete m_ParentAllocator;
			//}
			m_Data = nullptr;
			m_Head = nullptr;
		}

		template <typename T>
		template <typename... arguments>
		T* PoolAllocator<T>::allocate(arguments&&... args)
		{
			if (m_Head == nullptr)
				return nullptr;

			m_OpenAllocations++;

			PoolChunk<T> *poolChunk = m_Head;
			poolChunk->allocated = true;
			m_Head = m_Head->nextPoolChunk;
			T* retVal = new (std::addressof(poolChunk->value)) T(std::forward<arguments>(args)...);
			return retVal;
		}

		template <typename T>
		void PoolAllocator<T>::deallocate(T* data)
		{
			if (data == nullptr)
			{
				return;
			}
			data->~T();
			m_OpenAllocations--;
			PoolChunk<T>* poolChunk = reinterpret_cast<PoolChunk<T>*>(data);
			poolChunk->allocated = false;
			poolChunk->nextPoolChunk = m_Head;
			m_Head = poolChunk;
		}

		template <typename T>
		U32 PoolAllocator<T>::getSize() const {
			return m_Size;
		}

		template <typename T>
		U32 PoolAllocator<T>::getAllocations() const {
			return m_OpenAllocations;
		}

		template <typename T>
		PoolIterator<T> PoolAllocator<T>::begin()
		{
			PoolIterator<T> result;
			result.m_item = m_Data;
			return result;
		}

		template <typename T>
		PoolIterator<T> PoolAllocator<T>::end()
		{
			PoolIterator<T> result;
			result.m_item = m_Data + m_OpenAllocations;
			return result;
		}
	}
}
