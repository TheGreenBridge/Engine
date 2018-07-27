#pragma once

#include <map>
#include <common\types.h>
#include <iostream>

namespace engine {
	namespace memory {
		template<typename T>
		class LookupHandle {
		private:
			std::map<U32, T*> m_Hashtable;
		public:

			void insertEntry(U32 id, T* element);

			void deleteEntry(U32 id);

			T* getEntry(U32 id) const;
		};
	}
}

// IMPLEMENTATION

namespace engine {
	namespace memory {
		template<typename T>
		void LookupHandle<T>::insertEntry(U32 id, T* element) {
			m_Hashtable.insert(std::pair<U32, T*>(id, element));
		}

		template<typename T>
		void LookupHandle<T>::deleteEntry(U32 id)
		{
			m_Hashtable.erase(id);
		}

		template<typename T>
		T* LookupHandle<T>::getEntry(U32 id) const {
			
			std::map<U32, T*>::const_iterator search = m_Hashtable.find(id);
			if (search == m_Hashtable.end())
				return nullptr;
			return search->second;
		}

	}
	/*
	template void memory::LookupHandle<int>::insertEntry(U32 id, int* element);
	template int* memory::LookupHandle<int>::getEntry(U32 id) const;
	template class memory::LookupHandle<int>;
	*/

}