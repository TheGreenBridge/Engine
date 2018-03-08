#pragma once

#include <vector>

#include <common/types.h>

namespace engine {	
	// forward declaration
	class Entity;
	
	namespace graphics{
	// forward declaration
	class Light;

	class Scene {
	private:
		std::vector<Entity*> m_Entities;
		std::vector<Light*> m_Lights;
		U32 m_EntityCount;

	public:
		void add(Entity *entity);
		std::vector<Entity*> getContainer() const;
		std::vector<Light*> getLights() const;
	};

}}
