//------------------------------------------------------------------------------
// ComponentManager.h
//
// Manages components of entities
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 13.08.18
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

// std
#include <map>

	
namespace engine {

	// Forward Declarations
	class memory::IAllocator;

	class ComponentManager {

	public:
		// Ctor & Dtor
		explicit ComponentManager(memory::IAllocator* allocator);
		~ComponentManager();

		// Component Interface
		template <typename T, typename... arguments>
		T* AddComponent(const Entity *entity, arguments&&... args);

		template <typename T>
		T* GetComponent(const Entity *entity);

		template <typename T>
		void DestroyComponent(const Entity* entity);

		template <typename T>
		memory::PoolAllocator<T>* getContainer();

		// Deleted Ctor
		ComponentManager() = delete;
		ComponentManager(const ComponentManager&) = delete;
		ComponentManager(ComponentManager&&) = delete;
		ComponentManager& operator=(const ComponentManager&) = delete;
		ComponentManager& operator=(ComponentManager&&) = delete;

	private:
		static U32 TypeCounter;
		static U32 GetTypeCounter();
		
		memory::IAllocator* m_memory;
		std::map<U32, memory::IPoolContainer*> m_container;
		
		template <typename T>
		void addNewContainer();
	};
}

// Template implementation
namespace engine {

	//----------------------------------------------------------------------
	template <typename T, typename... arguments>
	T* ComponentManager::AddComponent(const Entity *entity, arguments&&... args)
	{
		if (m_container.find(typeid(T).hash_code()) == m_container.end())
		{
			addNewContainer<T>();
		}

		memory::PoolContainer<T>* container =
			reinterpret_cast<memory::PoolContainer<T>*>
			(m_container.find(typeid(T).hash_code())->second);

		return container->newElement(
			entity->m_UniqueId.id, std::forward<arguments>(args)...);

		//if (std::is_same<T, Model>::value) {
		//	m_model.newElement(entity.m_UniqueId.id, std::forward<arguments>(args)...);
		//}			
	}

	//----------------------------------------------------------------------
	template <typename T>
	T* ComponentManager::GetComponent(const Entity *entity)
	{
		memory::PoolContainer<T>* container =
			reinterpret_cast<memory::PoolContainer<T>*>(
				m_container.find(typeid(T).hash_code())->second);
		return container->getElement(entity->m_UniqueId.id);
	}

	//----------------------------------------------------------------------
	template <typename T>
	void ComponentManager::DestroyComponent(const Entity* entity)
	{
		memory::PoolContainer<T>* container =
			reinterpret_cast<memory::PoolContainer<T>*>(
				m_container.find(typeid(T).hash_code())->second);
		container->deleteElement(entity->m_UniqueId.id);
	}

	//----------------------------------------------------------------------
	template <typename T>
	void ComponentManager::addNewContainer()
	{
		blk temp = m_memory->allocate(sizeof(memory::PoolContainer<T>));
		m_container.insert(
			std::pair<U32, memory::IPoolContainer*>
			(
				typeid(T).hash_code(),
				dynamic_cast<memory::IPoolContainer*>
				(
					new(temp.ptr)  memory::PoolContainer<T>(m_memory, 30)
					)
				)
		);
	}

	//----------------------------------------------------------------------
	template <typename T>
	memory::PoolAllocator<T>* ComponentManager::getContainer()
	{
		auto it = m_container.find(typeid(T).hash_code());
		if (it != m_container.end())
		{
			memory::PoolContainer<T>* container = reinterpret_cast<memory::PoolContainer<T>*>(it->second);
			return container->getAllocator();
		}
		else return nullptr;
	}
}

#endif //__COMPONENT_MANAGER_H__	

