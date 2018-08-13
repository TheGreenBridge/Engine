#include "Console.h"
#include "../../utils/Log.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <EngineCore.h>

namespace engine {

	bool Console::m_IsRunning = true;
	Worker Console::m_Worker;

	void work()
	{
		Entity* entity = nullptr;
		std::vector<std::string> params;
		while (Console::m_IsRunning) {
			std::string inputtext;

			std::getline(std::cin, inputtext);

			LOG("command", inputtext);

			std::stringstream ss(inputtext);
			std::istream_iterator<std::string> begin(ss);
			std::istream_iterator<std::string> end;
			std::vector<std::string> params(begin, end);
			//std::copy(params.begin(), params.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

			if (params.size() == 0)
			{
				continue;
			}

			std::string command = params[0];

			if (command == "hallo") LOG("peace!");
			else if (command == "help") LOG("Command list: *hallo *exit");
			else if (command == "fetch")
			{
				if (params.size() != 2) continue;
				U32 index = std::stoi(params[1]);
				entity = Engine::getEntityManager()->getEntity(index);
				if (entity == nullptr)
				{
					LOG("could not find entity");
				}
			}
			else if (command == "move-up") {
				if (entity != nullptr) {					
					entity->transform.position.y += 0.5f;
				}
			}
			else if (command == "move-left") {
				if (entity != nullptr) {
					entity->transform.position.x -= 0.5f;
				}
			}
			else if (command == "move-right") {
				if (entity != nullptr) {
					entity->transform.position.x += 0.5f;
				}
			}
			else if (command == "move-down") {
				if (entity != nullptr) {
					entity->transform.position.y -= 0.5f;
				}
			}
			else if (command == "exit") break;
			else LOG("no command");
			
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