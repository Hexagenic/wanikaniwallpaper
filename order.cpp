#include "order.hpp"
#include "kanji.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
using std::string;

namespace wanikani
{
Order::Order(string filename)
{
	std::ifstream orderFile;
	orderFile.open(filename.c_str());

    char c;

	int index = 0;

	while(orderFile.good())
	{
		orderFile.get(c);

		if(c == 10)
			continue;
		else if(c <= -23 && c >= -29) // dirty way to get multi-byte characters
		{
			std::stringstream charstream;
			charstream << c;
			orderFile.get(c);
			charstream << c;
			orderFile.get(c);
			charstream << c;

			std::string character(charstream.str());
			Kanji kanji(character);

            intToChar_[index] = character;
			charToInt_[character] = index;
			charToKanji_[character] = kanji;

			index++;
		}
		else
		{
			std::cout << "Unknown bytcode: " << (int) c << std::endl;
		}
	}

    orderFile.close();
}

void Order::update(std::vector<Kanji> list)
{
	for(std::vector<Kanji>::iterator i = list.begin(); i!= list.end(); i++)
	{
		std::map<std::string, Kanji>::iterator k = charToKanji_.find(i->character());
		if(k != charToKanji_.end())
		{
			k->second = *i;
		}
		else
			std::cout << "Kanji from WaniKani not found in file: " << i->character() << std::endl;
	}
}

int Order::position(std::string character)
{
    return charToInt_[character];
}

std::string Order::character(int position)
{
	return intToChar_[position];
}

Kanji Order::kanji(std::string character)
{
	return charToKanji_[character];
}

Kanji Order::kanji(int position)
{
	const std::string character = intToChar_[position];
	return charToKanji_[character];
}

int Order::size()
{
	return intToChar_.size();
}

} //wanikani
