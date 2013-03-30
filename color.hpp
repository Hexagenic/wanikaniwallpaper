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
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0xFF);
	Color(const Color &other);
	
	const uint32_t ABGR() const;
	void ABGR(uint32_t abgr);

	static uint32_t compToABGR(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0xFF);
	static uint32_t hexToABGR(const std::string hexcode);

private:
	uint32_t abgr_;
};

}
