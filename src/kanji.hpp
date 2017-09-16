#pragma once

#include <string>

namespace wanikani
{
enum WaniKaniSRS {SRS_ERROR, SRS_UNSEEN, SRS_APPRENTICE, SRS_GURU, SRS_MASTER, SRS_ENLIGHTENED, SRS_BURNED};

class Kanji
{
public:
	Kanji();
	Kanji(int character, std::string utf8Character, WaniKaniSRS SRS = SRS_UNSEEN);
	const int character() const;
	const std::string utf8Character() const;
	const WaniKaniSRS SRS() const;
	const unsigned int color() const;

private:
	int character_;
	std::string utf8Character_;
	WaniKaniSRS SRS_;

};
} //wanikani
