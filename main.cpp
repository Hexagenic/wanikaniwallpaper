#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "kanji.hpp"
#include "order.hpp"
#include "grid.hpp"
#include "api.hpp"
#include "save.hpp"

int main(int argc, char **argv)
{

	if(argc != 2)
		return 1;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	Uint32 rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	SDL_Surface *surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1920, 1080, 32, rmask, gmask, bmask, amask);

	wanikani::Order order;

	order.update(wanikani::API::get(argv[1]));

	SDL_Rect rect = surface->clip_rect;
	SDL_FillRect(surface, &surface->clip_rect, 0xFF000000);
	wanikani::draw(order, surface, rect); 
	SDL_Flip(surface);

    savePNG("out.png", surface);

	SDL_FreeSurface(surface);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
