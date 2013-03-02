#pragma once
#include <string>
#include <SDL/SDL_ttf.h>

namespace wanikani
{
enum WaniKaniSRS {SRS_ERROR, SRS_UNSEEN, SRS_APPRENTICE, SRS_GURU, SRS_MASTER, SRS_ENLIGHTENED, SRS_BURNED};

class Kanji
{
public:
	Kanji();
	Kanji(std::string character, WaniKaniSRS SRS = SRS_UNSEEN);
	const std::string character() const;
	const WaniKaniSRS SRS() const;

	void draw(SDL_Surface *surface, int x, int y);

	static void loadFont(std::string name, int size);
	static void unloadFont();	
private:
	std::string character_;
	WaniKaniSRS SRS_;
	static TTF_Font *font_;

};
} //wanikani
