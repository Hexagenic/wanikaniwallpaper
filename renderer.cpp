#include "renderer.hpp"
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#define PNG_SKIP_SETJMP_CHECK
#include <png.h>
#include "grid.hpp"
#include "color.hpp"
#include <iomanip>

void png_user_warn(png_structp ctx, png_const_charp str)
{
	std::cerr << "libPNG warning: " << str << std::endl; 
}

void png_user_error(png_structp ctx, png_const_charp str)
{
	std::cerr << "libPNG error: " << str << std::endl; 
	exit(1);
}

void renderGlyph(FT_Face &face, int charCode)
{
	int error;
	error = FT_Load_Char(face, charCode, FT_LOAD_DEFAULT);
	if(error)
	{
		std::cerr << "Could not find character in font face, code: " << error << std::endl;
		exit(1);
	}

	error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_LCD);
	if(error)
	{
		std::cerr << "Could not render glyph, code: " << error << std::endl;
		exit(1);
	}
}

void drawGlyph(int* buffer, int bufferPitch, int originX, int originY, FT_GlyphSlot glyph, int fontSize, wanikani::Color colorIn)
{
	FT_Bitmap bitmap = glyph->bitmap;
	int glyphWidth = bitmap.width;
	int glyphHeight = bitmap.rows;
	int glyphPitch = bitmap.pitch;
	int glyphLeft = glyph->bitmap_left;
	int glyphTop = fontSize - glyph->bitmap_top;

	for (int glyphX = 0; glyphX < glyphWidth / 3; glyphX++)
	{
		for (int glyphY = 0; glyphY < glyphHeight; glyphY++)
		{
			int glyphPos = glyphX*3 + glyphY * glyphPitch;	

			int bufferX = originX + glyphX + glyphLeft;
			int bufferY = originY + glyphY + glyphTop;

			int bufferPos = bufferX + bufferY * bufferPitch;

            uint32_t r = bitmap.buffer[glyphPos + 0];
            uint32_t g = bitmap.buffer[glyphPos + 1];
			uint32_t b = bitmap.buffer[glyphPos + 2];

			// TODO: HACK: Should not need to get alpha from RGB.
			uint32_t a = (r + g + b) / 3;

			wanikani::Color colorOut(r,g,b);

            colorOut *= colorIn;

			// Overlay alpha compositing
			buffer[bufferPos] = ((colorOut * a) + wanikani::Color(buffer[bufferPos]) * (0xFF - a)).ABGR();
		}
	}	
}

namespace wanikani
{

Renderer::Renderer(int width, int height, std::string fontName)
	:width_(width)
	,height_(height)
	,marginLeft_(0)
	,marginRight_(0)
	,marginTop_(0)
	,marginBottom_(0)
	,buffer_(new int[width * height]())
{
	int error = 0;

	error = FT_Init_FreeType(&library_);
	if(error)
	{
		std::cerr << "Failed to initialize freetype library, code: " << error << std::endl;
		exit(1);
	}

	error = FT_New_Face(library_, fontName.c_str(), 0, &face_);
	if(error)
	{
		std::cerr << "Failed to load font face: " << fontName << ", code: " << error << std::endl;
		exit(1);
	}
}

void Renderer::setMargins(int left, int right, int top, int bottom)
{
	marginLeft_ = left;
	marginRight_ = right;
	marginTop_ = top;
	marginBottom_ = bottom;
}

void Renderer::render(Order &order)
{
    //Set background
	for(int x = 0; x < width_; x++)
	{
		for(int y = 0; y < height_; y++)
		{
			int pos = x + (y * width_);

			buffer_[pos] = colorBackground_.ABGR();
		}
	}
	
    double width = width_ - marginLeft_ - marginRight_;
	double height = height_ - marginTop_ - marginBottom_;

	double ratio = width / height;	
	int w, h;
	double wasted = grid::findBest(order.size(), ratio, w, h);
	double contentRatio = double(w) / double(h);
	double characterWidth = width / double(w);
	double characterHeight = height / double(h);
    int fontSize = contentRatio < ratio ? (int) characterHeight : (int) characterWidth;
	FT_Select_Charmap(face_, ft_encoding_unicode);
	FT_Set_Pixel_Sizes(face_, 0, fontSize);

	for(int i = 0; i < order.size(); i++)
	{
		int gridX = (i % w) * characterWidth + marginLeft_;
		int gridY = (i / w) * characterHeight + marginTop_;


		renderGlyph(face_, order.kanji(i).character());
		
		drawGlyph(buffer_, width_, gridX, gridY, face_->glyph, fontSize, SRSColor(order.kanji(i).SRS()));
	}
}

void Renderer::save(std::string fileName)
{
	FILE *file = fopen(fileName.c_str(), "wb");

    if(file == NULL)
	{
		std::cerr << "Could not open " << fileName << " for writing, code: " << errno << std::endl;
		exit(1);
	}

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, png_user_error, png_user_warn);
	png_infop info_ptr = png_create_info_struct(png_ptr);

	setjmp(png_jmpbuf(png_ptr));

	png_init_io(png_ptr, file);

	png_set_IHDR(
			png_ptr, 
			info_ptr, 
			width_, 
			height_, 
			8, 
			PNG_COLOR_TYPE_RGBA, 
			PNG_INTERLACE_NONE, 
			PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT);

	png_write_info(png_ptr, info_ptr);
	png_set_packing(png_ptr);

	png_bytep *row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height_ * 4);

	for(int i = 0; i < height_; i++)
		row_pointers[i] = (png_bytep)buffer_ + i * width_ * 4;

	png_write_image(png_ptr, row_pointers);
	png_write_end(png_ptr, info_ptr);

	free(row_pointers);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(file);
}

void Renderer::setBackground(Color color) { colorBackground_ = color; }
void Renderer::setUnseen(Color color) { colorUnseen_ = color; }
void Renderer::setApprentice(Color color) { colorApprentice_ = color; }
void Renderer::setGuru(Color color) { colorGuru_ = color; }
void Renderer::setMaster(Color color) { colorMaster_ = color; }
void Renderer::setEnlightened(Color color) { colorEnlightened_ = color; }
void Renderer::setBurned(Color color) { colorBurned_ = color; }
void Renderer::setError(Color color) { colorError_ = color; }

Color Renderer::SRSColor(WaniKaniSRS srs)
{
	switch(srs)
	{
		case SRS_UNSEEN:
			return colorUnseen_;
		case SRS_APPRENTICE:
			return colorApprentice_;
		case SRS_GURU:
			return colorGuru_;
		case SRS_MASTER:
            return colorMaster_;
		case SRS_ENLIGHTENED:
			return colorEnlightened_;
		case SRS_BURNED:
			return colorBurned_;
		default:
			return colorError_;
	}
}	


}
