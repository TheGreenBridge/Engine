//------------------------------------------------------------------------------
// ComponentManager.h
//
// Manages components of entities
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 23.07.18
//------------------------------------------------------------------------------
//

#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__	

#pragma once

#include <common\types.h>
#include <memory\PoolContainer.h>
#include <entity\component\Transform.h>
#include <entity\Entity.h>
#include <utils\Log.h>
#include <map>
#include <memory\MemoryManager.h>
	
namespace engine {

	class ComponentManager {
	private:
		static U32 TypeCounter;
		static U32 GetTypeCounter();

		static memory::MemoryManager *m_memory;

		std::map<size_t, memory::IPoolContainer*> m_container;
		
		template <typename T>
		void addNewContainer() 
		{
			blk temp = m_memory->allocate(sizeof(memory::PoolContainer<T>));
			m_container.insert(
				std::pair<size_t, memory::IPoolContainer*>
				(
					typeid(T).hash_code(), 
					dynamic_cast<memory::IPoolContainer*>
					(
						new(temp.ptr)  memory::PoolContainer<T>(30)
					)
				)
			);
		}

	public:
		ComponentManager();
		~ComponentManager();

		template <typename T, typename... arguments>
		T* AddComponent(const Entity *entity, arguments&&... args)
		{
			//LOG(typeid(T).name());
			//LOG("WHAT");
			//LOG("test", typeid(T).hash_code());
			//LOG("sizeis", sizeof(typeid(T)));

			if (m_container.find(typeid(T).hash_code()) == m_container.end())
			{
				addNewContainer<T>();
			}

			memory::PoolContainer<T> *container = reinterpret_cast<memory::PoolContainer<T>*> (m_container.find(typeid(T).hash_code())->second);

			return container->newElement(entity->m_UniqueId.id, std::forward<arguments>(args)...);

			

			//if (std::is_same<T, Model>::value) {
			//	m_model.newElement(entity.m_UniqueId.id, std::forward<arguments>(args)...);
			//}
			//else if (std::is_same<T, Transform>::value)
			//{
			//	m_trans.newElement(entity.m_UniqueId.id, std::forward<arguments>(args)...);

			//}
			
		}		//m_test.newElement(entity.m_UniqueId.id, std::forward<arguments>(args));

		template <typename T>
		T* GetComponent(const Entity *entity)
		{
			memory::PoolContainer<T>* container = reinterpret_cast<memory::PoolContainer<T>*>(m_container.find(typeid(T).hash_code())->second);		
			return container->getElement(entity->m_UniqueId.id);
		}
	};

 }

#endif //__COMPONENT_MANAGER_H__	

