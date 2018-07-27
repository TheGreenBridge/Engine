#include "Console.h"
#include "../../utils/Log.h"
#include <iostream>
#include <EngineCore.h>

namespace engine {

	bool Console::m_IsRunning = true;
	Worker Console::m_Worker;

	void work()
	{
		while (Console::m_IsRunning) {
			std::string inputtext;
			std::cin >> inputtext;

			if (inputtext == "hallo") std::cout << "peace!" << std::endl;
			if (inputtext == "help") std::cout << "Command list: *hallo *exit" << std::endl;
			if (inputtext == "move-up") {		
				Entity *entity = Engine::getEntityManager()->getEntity(1);
				if (entity != nullptr) {					
					entity->transform.position.y += 0.5f;
				}
			}
			if (inputtext == "move-left") {
				Entity *entity = Engine::getEntityManager()->getEntity(1);
				if (entity != nullptr) {
					entity->transform.position.x -= 0.5f;
				}
			}
			if (inputtext == "move-right") {
				Entity *entity = Engine::getEntityManager()->getEntity(1);
				if (entity != nullptr) {
					entity->transform.position.x += 0.5f;
				}
			}
			if (inputtext == "move-down") {
				Entity *entity = Engine::getEntityManager()->getEntity(1);
				if (entity != nullptr) {
					entity->transform.position.y -= 0.5f;
				}
			}
			if (inputtext == "exit") break;
		}
	}

	void Console::runConsole() {
		m_Worker.doWork(&work);
	}

	void Console::stopConsole()
	{
		m_IsRunning = false;
	}


	void Console::checkConsole() {
		LOG("Console ready! (help)");
		while (true) {
			std::string inputtext;
			std::cin >> inputtext;

			if (inputtext == "hallo") LOG("peace!");
			if (inputtext == "help") LOG("Command list: *hallo *exit");

			/*if (inputtext == "print_camera_position") std::cout << "camera position: (" << camera.getposition().x
			<< " ," << camera.getposition().y << " ," << camera.getposition().z << ")" << std::endl;
			if (inputtext == "hallo") std::cout << "peace!" << std::endl;*/
			if (inputtext == "exit") break;
		}
	}

	Console::Console() 
	{

	}

}