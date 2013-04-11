#include "order.hpp"
#include "kanji.hpp"

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <utf8.h>
#include <vector>
using std::string;

namespace wanikani
{
	Order::Order(string filename)
	{
		std::ifstream orderFile;
		orderFile.open(filename.c_str());

        if(orderFile.fail())
		{
			std::cerr << "Could no open file " << filename << " for reading.\n";
			exit(1);
		}

		orderFile.seekg(0, orderFile.end);
		int length = orderFile.tellg();
		orderFile.seekg(0, orderFile.beg);

		char *buffer = new char[length];

		orderFile.read(buffer, length);

		orderFile.close();

		std::vector<int> wideString;
		utf8::utf8to32(buffer, buffer + length, back_inserter(wideString));

		int index = 0;
		for(int i = 0; i < wideString.size(); i++)
		{
			int character = wideString[i];


			if(character != 10)
			{
				std::string utf8Character;
				utf8::utf32to8(wideString.begin() + i, wideString.begin() + i, back_inserter(utf8Character));
				Kanji kanji(character, utf8Character);

				intToChar_[index] = character;
				charToInt_[character] = index;
				charToKanji_[character] = kanji;
				index++;
			}
		}

	}

	void Order::update(std::vector<Kanji> list)
	{
		for(std::vector<Kanji>::iterator i = list.begin(); i!= list.end(); i++)
		{
			std::map<int, Kanji>::iterator k = charToKanji_.find(i->character());
			if(k != charToKanji_.end())
			{
				k->second = *i;
			}
			else
				std::cout << "Kanji from WaniKani not found in file: " << i->utf8Character() 
					<< ", utf32: " << std::hex << i->character() << std::dec << std::endl;
		}
	}

	int Order::position(int character)
	{
		return charToInt_[character];
	}

	int Order::character(int position)
	{
		return intToChar_[position];
	}

	Kanji Order::kanji(int position)
	{
		const int character = intToChar_[position];
		return charToKanji_[character];
	}

	int Order::size()
	{
		return intToChar_.size();
	}

} //wanikani
