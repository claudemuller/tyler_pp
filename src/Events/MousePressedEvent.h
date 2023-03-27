#ifndef MOUSE_PRESS_EVENT_H
#define MOUSE_PRESS_EVENT_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../EventBus/Event.h"

class MousePressedEvent: public Event {
public:
	glm::vec2 location;
	SDL_Keycode symbol;

	MousePressedEvent(SDL_Keycode symbol, glm::vec2 location = glm::vec2(0)) {
		this->symbol = symbol;
		this->location = location;
	}
};

#endif // MOUSE_PRESS_EVENT_H
