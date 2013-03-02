#include "kanji.hpp"

using std::string;

namespace wanikani
{

TTF_Font *Kanji::font_;

Kanji::Kanji()
	:character_("")
	,SRS_(SRS_UNSEEN)
{
}

Kanji::Kanji(string character, WaniKaniSRS SRS)
	:character_(character)
	,SRS_(SRS)
{
}

const string Kanji::character() const
{
	return character_;
}

const WaniKaniSRS Kanji::SRS() const
{
	return SRS_;
}

void Kanji::draw(SDL_Surface *surface, int x, int y)
{
    SDL_Color col = {0, 0, 0};

    switch(SRS_)
	{
		case SRS_UNSEEN:
			col = {40, 40, 40};
			break;
		case SRS_APPRENTICE:
			col = {221, 0, 147};
			break;
		case SRS_GURU:
			col = {136, 45, 158};
			break;
		case SRS_MASTER:
			col = {41, 77, 219};
			break;
		case SRS_ENLIGHTENED:
			col = {0, 147, 221};
			break;
		case SRS_BURNED:
			col = {240, 240, 240};
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
