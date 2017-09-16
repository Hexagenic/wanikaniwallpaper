#pragma once

#include <string>
#include <stdint.h>

namespace wanikani
{

class Color
{
public:
	Color();
	Color(const std::string hexcode);
	Color(uint32_t abgr);
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0xFF);
	Color(const Color &other);
	
    Color operator+(const Color& other) const;
    Color operator*(const Color& other) const;
    Color& operator*=(const Color& other);
    
	Color operator*(uint8_t scalar) const;

	const uint32_t ABGR() const;
	void ABGR(uint32_t abgr);

	static uint32_t compToABGR(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0xFF);
	static uint32_t hexToABGR(const std::string hexcode);
	static void ABGRToComp(uint32_t abgr, uint8_t& red, uint8_t& green, uint8_t& blue, uint8_t& alpha);
private:
	uint8_t a_, b_, g_, r_;
};

}
