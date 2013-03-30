#include "color.hpp"

uint8_t hexToInt(char hex)
{
	switch(hex)
	{
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		case 'a':
		case 'A':
			return 10;
		case 'b':
		case 'B':
			return 11;
		case 'c':
		case 'C':
			return 12;
		case 'd':
		case 'D':
			return 13;
		case 'e':
		case 'E':
			return 14;
		case 'f':
		case 'F':
			return 15;
		default:
			return 0;
	}
}

namespace wanikani
{

Color::Color()
	:abgr_(0xFF000000)
{
}

Color::Color(const std::string hexcode)
	:abgr_(hexToABGR(hexcode))
{
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
	:abgr_(compToABGR(red, green, blue, alpha))
{
}

Color::Color(const Color &other)
	:abgr_(other.abgr_)
{
}

const uint32_t Color::ABGR() const
{
	return abgr_;
}

void Color::ABGR(uint32_t abgr)
{
	abgr_ = abgr;
}

uint32_t Color::compToABGR(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	return (alpha<<24) + (blue<<16) + (green<<8) + red;
}

uint32_t Color::hexToABGR(const std::string hexcode)
{
    if(hexcode.size() == 7 && hexcode[0] == '#')
	{
		uint8_t red = (hexToInt(hexcode[1])<<4) + hexToInt(hexcode[2]); 
		uint8_t green = (hexToInt(hexcode[3])<<4) + hexToInt(hexcode[4]); 
		uint8_t blue = (hexToInt(hexcode[5])<<4) + hexToInt(hexcode[6]); 
        return compToABGR(red, green, blue);

	}
	else 
		return 0xFFFF00FF;

}

}
