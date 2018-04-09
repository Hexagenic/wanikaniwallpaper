#pragma once

#include <string>
#include <map>
#include <vector>

#include "kanji.hpp"

namespace wanikani
{
class Order
{
public:
	Order();
	void update(std::vector<Kanji> list);
	void updateHeisig(int index);
	int position(int character);
	int character(int position);
	Kanji kanji(int position);
	int size();
private:
	std::map<int, int> intToChar_;
	std::map<int, int> charToInt_;
	std::map<int, Kanji> charToKanji_;	
};
} //wanikani
