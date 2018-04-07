#pragma once

#include <entity\Entity.h>
#include <memory\LookupHandle.h>
#include <memory\allocator\PoolAllocator.h>

namespace engine {

	class EntityManager //: private PoolContainer<Entity>
	{
	private:
		static U32 EntityIds;

		memory::LookupHandle<Entity> m_Handle;
		memory::PoolAllocator<Entity> m_Allocator;
	public:
		EntityManager();
		~EntityManager();

		Entity* newEntity();

		void deleteEntity(U32 id);

		Entity* getEntity(U32 id) const;

		U32 getEntityCount() const;
	};
}
