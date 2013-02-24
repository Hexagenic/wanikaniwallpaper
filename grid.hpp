#pragma once

#include <SDL/SDL.h>

#include "order.hpp"

namespace wanikani
{
	void draw(Order order, SDL_Surface *surface, SDL_Rect rect);
} //wanikani
