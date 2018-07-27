
#include "tests\Game.h"
#include "tests\EngineTest.h"



int main() {
	EngineTest test;

	test.init();
	test.runApp();
	test.stop();

	return 0;
}