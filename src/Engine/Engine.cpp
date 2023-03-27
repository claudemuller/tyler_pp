#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include "Engine.h"
#include "../Logger/Logger.h"
#include "../Events/MousePressedEvent.h"
#include "SDL2/SDL_events.h"

const int TILE_SIZE = 32;
const int TILE_COLS = 60;
const int TILE_ROWS = 33;

int Engine::WindowWidth;
int Engine::WindowHeight;
int Engine::MapWidth;
int Engine::MapHeight;

void
test()
{
    printf("it worked");
}

Engine::Engine() {
    isRunning = false;
    isDebug = false;
    millisecsPreviousFrame = 0;
    eventBus = std::make_unique<EventBus>();
}

Engine::~Engine() {}

void Engine::Init(bool debug) {
    Logger::Log = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
	Logger::Err("error initing SDL");
	return;
    }

 //    if (TTF_Init() != 0) {
	// Logger::Err("error initing TTF");
	// return;
 //    }

    // SDL_DisplayMode displayMode;
    // SDL_GetCurrentDisplayMode(0, &displayMode);
    // WindowWidth = 1280; //displayMode.w;
    // WindowHeight = 720; //displayMode.h;
    WindowWidth = TILE_SIZE*TILE_COLS;
    WindowHeight = TILE_SIZE*TILE_ROWS;


    window = SDL_CreateWindow(
	    NULL,
	    SDL_WINDOWPOS_CENTERED,
	    SDL_WINDOWPOS_CENTERED,
	    WindowWidth,
	    WindowHeight,
	    SDL_WINDOW_BORDERLESS
    );
    if (window == nullptr) {
	Logger::Err("error creating window");
	return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
	Logger::Err("error creating renderer");
	return;
    }

    if (!debug)
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;

    camera.x = 0;
    camera.y = 0;
    camera.w = WindowWidth;
    camera.h = WindowHeight;

    Logger::Info("engine successfully initialised");
}

void Engine::Run() {
    Setup();

    while (isRunning) {
	ProcessInput();
	Update();
	Render();
    }
}

void Engine::Setup() {
}

void Engine::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
	switch (event.type) {
	    case SDL_QUIT:
		isRunning = false;
	    break;
	    case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
		    isRunning = false;
		}
		if (event.key.keysym.sym == SDLK_F1) {
		    isDebug = !isDebug;
		}
	    case SDL_MOUSEBUTTONDOWN:
		eventBus->EmitEvent<MousePressedEvent>(event.key.keysym.sym, glm::vec2(0));
		break;
	}
    }
}

void Engine::Update() {
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) SDL_Delay(timeToWait);

    double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
    millisecsPreviousFrame = SDL_GetTicks();

    eventBus->Reset();
    // entityManager->GetSystem<DamageSystem>().SubscribeToEvents(eventBus);

}

void Engine::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 11, 11, 11, 255);
    SDL_Rect dst_rect = {0, 0, TILE_SIZE, TILE_SIZE};

    for (int y = 0; y < TILE_ROWS; y++) {
	for (int x = 0; x < TILE_COLS; x++) {
	    dst_rect.x = x*TILE_SIZE;
	    dst_rect.y = y*TILE_SIZE;

	    SDL_RenderDrawRect(renderer, &dst_rect);
	}
    }

    SDL_Surface *surface = IMG_Load("./assets/tilemaps/tilemap.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    int tex_width = 0;
    int tex_height = 0;
    SDL_QueryTexture(texture, NULL, NULL, &tex_width, &tex_height);
    SDL_Rect tilemap_rect = {
	.x = 0,
	.y = WindowHeight-tex_height,
	.w = tex_width,
	.h = tex_height
    };

    SDL_RenderCopy(renderer, texture, NULL, &tilemap_rect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}

void Engine::Cleanup() {
    // TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
