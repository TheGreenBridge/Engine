//
//#include <memory\PoolContainer.h>
//namespace engine {
//	namespace memory {
//
//		template <typename T>
//		template <typename... arguments>
//		T* PoolContainer<T>::newElement(U32 id, arguments&&... args) {
//			T* element = m_Allocator.allocate(std::forward<arguments>(args)...);
//			m_Handle.insertEntry(id, element);
//			return element;
//		}
//
//		template<typename T>
//		void PoolContainer<T>::deleteElement(U32 id) {
//
//			m_Allocator.deallocate(m_Handle.getEntry(id));
//			m_Handle.deleteEntry(id);
//
//		}
//
//		template<typename T>
//		T* PoolContainer<T>::getElement(U32 id) const {
//			return m_Hashtable.find(id)->second;
//		}
//
//		template<typename T>
//		U32 PoolContainer<T>::getElementNumber() const {
//			return m_Allocator.
//		}
//
//		// No need to call this TemporaryFunction() function,
//		// it's just to avoid link error.
//		void TemporaryFunction()
//		{
//			PoolContainer<int> TempObj;
//		}
//
//	}
//}
