#pragma once

namespace wanikani
{
enum WaniKaniSRS {SRS_ERROR, SRS_UNSEEN, SRS_APPRENTICE, SRS_GURU, SRS_MASTER, SRS_ENLIGHTENED, SRS_BURNED};

class Kanji
{
public:
	Kanji();
	Kanji(int character, WaniKaniSRS SRS = SRS_UNSEEN);
	const int character() const;
	const WaniKaniSRS SRS() const;
	const unsigned int color() const;

private:
	int character_;
	WaniKaniSRS SRS_;

};
} //wanikani
