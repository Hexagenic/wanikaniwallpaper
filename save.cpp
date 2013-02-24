#include "save.hpp"

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <png.h>

void png_user_warn(png_structp ctx, png_const_charp str)
{
	std::cerr << "libPNG warning: " << str << std::endl; 
}

void png_user_error(png_structp ctx, png_const_charp str)
{
	std::cerr << "libPNG error: " << str << std::endl; 
}

void savePNG(char *filename, SDL_Surface *surf)
{
	FILE *file = fopen(filename, "wb");

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, png_user_error, png_user_warn);
	png_infop info_ptr = png_create_info_struct(png_ptr);

	setjmp(png_jmpbuf(png_ptr));

	png_init_io(png_ptr, file);

	int colortype = PNG_COLOR_MASK_COLOR;
	if(surf->format->palette)
		colortype |= PNG_COLOR_MASK_PALETTE;
	else if(surf->format->Amask)
		colortype |= PNG_COLOR_MASK_ALPHA;

	png_set_IHDR(
			png_ptr, 
			info_ptr, 
			surf->w, 
			surf->h, 
			8, 
			colortype, 
			PNG_INTERLACE_NONE, 
			PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT);
	
	png_write_info(png_ptr, info_ptr);
	png_set_packing(png_ptr);

	png_bytep *row_pointers = (png_bytep*) malloc(sizeof(png_bytep)*surf->h);
	
	for(int i = 0; i < surf->h; i++)
		row_pointers[i] = (png_bytep)(Uint8 *)surf->pixels + i*surf->pitch;
	
	png_write_image(png_ptr, row_pointers);
	png_write_end(png_ptr, info_ptr);

	free(row_pointers);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(file);
}
