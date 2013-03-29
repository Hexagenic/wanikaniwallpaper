#pragma once

#include <stdint.h>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "order.hpp"


namespace wanikani
{
class Renderer
{
public:
	Renderer(int width, int height, std::string fontName);
	void render(Order &order);
	void save(std::string fileName);
private:
	FT_Library library_;
	FT_Face face_;
	int width_, height_;
	int *buffer_;
};
}

