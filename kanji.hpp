#pragma once
#include <string>
#include <SDL/SDL_ttf.h>

namespace wanikani
{
enum Knowledge {ERROR, UNKNOWN, APPRENTICE, GURU, MASTER, ENLIGHTENED};

class Kanji
{
public:
	Kanji();
	Kanji(std::string character, Knowledge knowledge = UNKNOWN);
	const std::string character() const;
	const Knowledge knowledge() const;

	void draw(SDL_Surface *surface, int x, int y);

	static void loadFont(std::string name, int size);
	static void unloadFont();	
private:
	std::string character_;
	Knowledge knowledge_;
	static TTF_Font *font_;

};
} //wanikani
