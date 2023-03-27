#include <cstring>
#include <iostream>
#include "./Engine/Engine.h"

int main(int argc, char* argv[]) {
	bool debug = true;

	Engine engine;

	if (argc >= 2)
		debug = std::strcmp(argv[1], "debug") == 0;

	engine.Init(debug);
	engine.Run();
	engine.Cleanup();


	return 0;
}
