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
	int position(std::string character);
	std::string character(int position);
	Kanji kanji(std::string character);
	Kanji kanji(int position);
	int size();
private:
	std::map<int, std::string> intToChar_;
	std::map<std::string, int> charToInt_;
	std::map<std::string, Kanji> charToKanji_;	
};
} //wanikani
