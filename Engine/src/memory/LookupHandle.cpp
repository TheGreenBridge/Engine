//#pragma once
//
//#include <memory\LookupHandle.h>
//
//namespace engine {
//	namespace memory {
//		template<typename T>
//		void LookupHandle<T>::insertEntry(U32 id, T* element) {
//			m_Hashtable.insert(std::pair<U32, T*>(id, element));
//		}
//
//		template<typename T>
//		void LookupHandle<T>::deleteEntry(U32 id)
//		{
//			m_Hashtable.erase(id);
//		}
//
//		template<typename T>
//		T* LookupHandle<T>::getEntry(U32 id) const {
//			return m_Hashtable.find(id)->second;
//		}
//
//		// No need to call this TemporaryFunction() function,
//		// it's just to avoid link error.
//		/*void TemporaryFunctionLookup()
//		{
//			LookupHandle<int> TempObj;
//		}*/
//	}
///*
//	template void memory::LookupHandle<int>::insertEntry(U32 id, int* element);
//	template int* memory::LookupHandle<int>::getEntry(U32 id) const;
//*/
//	/*template class memory::LookupHandle<int>;
//
//	void TemporaryFunctionLookupenginens()
//	{
//		memory::LookupHandle<int> TempObj;
//		
//	}*/
//}
////void TemporaryFunctionLookupGlobal()
////{
////	engine::memory::LookupHandle<int> TempObj;
////}
//
//
//
