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
	: a_(0xFF)
	, b_(0x00)
	, g_(0x00)
	, r_(0x00)
{
}

Color::Color(const std::string hexcode)
{
	uint32_t abgr = hexToABGR(hexcode);	
	ABGRToComp(abgr, r_, g_, b_, a_);
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
	: r_(red)
	, g_(green)
	, b_(blue)
	, a_(alpha)
{
}

Color::Color(const Color &other)
	: r_(other.r_)
	, g_(other.g_)
	, b_(other.b_)
	, a_(other.a_)
{
}

Color Color::operator*(const Color& other)
{
	return Color(
			(r_ * other.r_) / 0xFF,
			(g_ * other.g_) / 0xFF,
			(b_ * other.b_) / 0xFF,
			(a_ * other.a_) / 0xFF);
}

Color& Color::operator*=(const Color& other)
{
	r_ = (r_ * other.r_) / 0xFF;
	g_ = (g_ * other.g_) / 0xFF;
	b_ = (b_ * other.b_) / 0xFF;
	a_ = (a_ * other.a_) / 0xFF;

	return *this;
}	

const uint32_t Color::ABGR() const
{
	return compToABGR(r_, g_, b_, a_);
}

void Color::ABGR(uint32_t abgr)
{
	ABGRToComp(abgr, r_, g_, b_, a_);
}

uint32_t Color::compToABGR(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	return (alpha<<24) + (blue<<16) + (green<<8) + red;
}

uint32_t Color::hexToABGR(const std::string hexcode)
{
    if(hexcode.size() == 8 && hexcode[0] == '0' && hexcode[1] == 'x')
	{
		uint8_t red = (hexToInt(hexcode[2])<<4) + hexToInt(hexcode[3]); 
		uint8_t green = (hexToInt(hexcode[4])<<4) + hexToInt(hexcode[5]); 
		uint8_t blue = (hexToInt(hexcode[6])<<4) + hexToInt(hexcode[7]); 
        return compToABGR(red, green, blue);

	}
	else 
		return 0xFFFF00FF;

}
void Color::ABGRToComp(uint32_t abgr, uint8_t& red, uint8_t& green, uint8_t& blue, uint8_t& alpha)
{
	alpha = (abgr >> 24) & 0xFF;
	blue  = (abgr >> 16) & 0xFF;
	green = (abgr >>  8) & 0xFF;
	red   = (abgr >>  0) & 0xFF;
}

}
