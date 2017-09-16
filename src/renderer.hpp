#pragma once

#include <stdint.h>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "order.hpp"
#include "color.hpp"

namespace wanikani
{
class Renderer
{
public:
	Renderer(int width, int height, std::string fontName);
	void setMargins(int left, int right, int top, int bottom);
	void render(Order &order);
	void save(std::string fileName);
	void setBackground(Color color);
	void setUnseen(Color color);
	void setApprentice(Color color);
	void setGuru(Color color);
	void setMaster(Color color);
	void setEnlightened(Color color);
	void setBurned(Color color);
	void setError(Color color);

	Color SRSColor(WaniKaniSRS srs);

private:
	void drawGlyph(int originX, int originY, FT_GlyphSlot glyph, int fontSize, wanikani::Color colorIn);

	FT_Library library_;
	FT_Face face_;
	int width_, height_;
	int marginLeft_, marginRight_, marginTop_, marginBottom_;
	Color colorBackground_, colorUnseen_, colorApprentice_, colorGuru_, colorMaster_, colorEnlightened_, colorBurned_, colorError_;
	int *buffer_;
};
}

