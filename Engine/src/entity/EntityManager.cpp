#include <entity\EntityManager.h>

namespace engine {

	U32 EntityManager::EntityIds = 0;
	
	EntityManager::EntityManager() {
	}

	EntityManager::~EntityManager()
	{
	}

	Entity * EntityManager::newEntity()
	{
		EntityIds++;
		Entity* entity = m_Allocator.allocate();
		m_Handle.insertEntry(EntityIds, nullptr);
		entity->m_UniqueId.id = EntityIds;
		return entity;
	}

	void EntityManager::deleteEntity(U32 id) {
		m_Allocator.deallocate(m_Handle.getEntry(id));
		m_Handle.deleteEntry(id);
	}

	Entity* EntityManager::getEntity(U32 id) const {
		return m_Handle.getEntry(id);	
	}

	U32 EntityManager::getEntityCount() const {
		return m_Allocator.getSize();
	}
}