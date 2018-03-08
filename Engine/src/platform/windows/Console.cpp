#include "Console.h"
#include "../../utils/Log.h"
#include <iostream>

void checkConsole() {
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