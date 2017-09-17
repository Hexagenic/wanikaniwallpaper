#include "order.hpp"
#include "kanji.hpp"
#include "order-data.hpp"

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <utf8.h>
#include <vector>
using std::string;

namespace wanikani
{
	Order::Order()
	{
		std::vector<int> wideString;
		utf8::utf8to32(orderData.begin(), orderData.end(), back_inserter(wideString));

		int index = 0;
		for(int i = 0; i < wideString.size(); i++)
		{
			int character = wideString[i];


			if(character != 10)
			{
				std::string utf8Character;
				utf8::utf32to8(wideString.begin() + i, wideString.begin() + i + 1, back_inserter(utf8Character));
				Kanji kanji(character, utf8Character);

				intToChar_[index] = character;
				if(charToInt_.find(character) != charToInt_.end())
					std::cout << "Duplicate character: " << kanji.utf8Character()
						<< ", utf32: " << std::hex << character << std::dec << std::endl;
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
