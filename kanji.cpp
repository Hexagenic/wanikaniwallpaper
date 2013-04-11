#include "kanji.hpp"

namespace wanikani
{

Kanji::Kanji()
	:character_(0)
	,SRS_(SRS_UNSEEN)
{
}

Kanji::Kanji(int character, std::string utf8Character, WaniKaniSRS SRS)
	:character_(character)
	,utf8Character_(utf8Character)
	,SRS_(SRS)
{
}

const int Kanji::character() const
{
	return character_;
}

const std::string  Kanji::utf8Character() const
{
	return utf8Character_;
}

const WaniKaniSRS Kanji::SRS() const
{
	return SRS_;
}

const unsigned int Kanji::color() const
{
	switch(SRS_)
	{
		case SRS_UNSEEN:
			return 0xFF505050;
		case SRS_APPRENTICE:
			return 0xFF9300DD;
		case SRS_GURU:
			return 0xFF9E2D88;
		case SRS_MASTER:
            return 0xFFDB4D29;
		case SRS_ENLIGHTENED:
			return 0xFFDD9300;
		case SRS_BURNED:
			return 0xFFF0F0F0;
		default:
			return 0xFF0000FF;
	}
}
} //Wanikani 
