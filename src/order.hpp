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
	Order(std::string filename = "order");
	void update(std::vector<Kanji> list);
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
