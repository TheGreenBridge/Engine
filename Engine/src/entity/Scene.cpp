#include "../entity/Entity.h"
#include "Scene.h"

namespace engine {
	namespace graphics {

		void Scene::add(Entity *entity) {
			m_Entities.push_back(entity);
			m_EntityCount++;
		}

		std::vector<Entity*> Scene::getContainer() const { 
			return m_Entities; 
		}

		std::vector<Light*> Scene::getLights() const
		{
			return std::vector<Light*>();
		}
	}
}

