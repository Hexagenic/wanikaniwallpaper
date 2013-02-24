#include "kanji.hpp"

using std::string;

namespace wanikani
{

TTF_Font *Kanji::font_;

Kanji::Kanji()
	:character_("")
	,knowledge_(UNKNOWN)
{
}

Kanji::Kanji(string character, Knowledge knowledge)
	:character_(character)
	,knowledge_(knowledge)
{
}

const string Kanji::character() const
{
	return character_;
}

const Knowledge Kanji::knowledge() const
{
	return knowledge_;
}

void Kanji::draw(SDL_Surface *surface, int x, int y)
{
    SDL_Color col = {0, 0, 0};

    switch(knowledge_)
	{
		case UNKNOWN:
			col = {40, 40, 40};
			break;
		case APPRENTICE:
			col = {221, 0, 147};
			break;
		case GURU:
			col = {136, 45, 158};
			break;
		case MASTER:
			col = {41, 77, 219};
			break;
		case ENLIGHTENED:
			col = {0, 147, 221};
			break;
		default:
			col = {255, 0, 0};
	}

	SDL_Surface *charsurf = TTF_RenderUTF8_Blended(font_, character_.c_str(), col);
	SDL_Rect rect = charsurf->clip_rect;
	rect.x = x;
	rect. y = y;

	SDL_BlitSurface(charsurf, &charsurf->clip_rect, surface, &rect);

	SDL_FreeSurface(charsurf);
}	

void Kanji::loadFont(std::string name, int size)
{
	font_ = TTF_OpenFont(name.c_str(), size);
}

void Kanji::unloadFont()
{

	TTF_CloseFont(font_);
	font_ = NULL;
}

} //Wanikani 
