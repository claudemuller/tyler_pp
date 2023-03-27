#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include "../EventBus/EventBus.h"

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000/FPS;

class Engine {
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Rect camera;

	bool isRunning;
	bool isDebug;
	int millisecsPreviousFrame;

	std::unique_ptr<EventBus> eventBus;

public:
	Engine();
	~Engine();

	void Init(bool debug);
	void Run();
	void Setup();
	void ProcessInput();
	void Update();
	void Render();
	void Cleanup();

	static int WindowWidth;
	static int WindowHeight;
	static int MapWidth;
	static int MapHeight;
};

#endif // ENGINE_H
