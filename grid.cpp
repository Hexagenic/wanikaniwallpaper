#include "grid.hpp"

#include <iostream>

double wastedSpace(int width, int &height, int num, double spaceRatio)
{
    if(num == 0)
		return 1;

	if (num < width)
		width = num;

	if(num % width == 0) // Fits perfectly
		height = num / width;
	else
		height = (num / width) + 1;

	double contentRatio = float(width) / float(height);

	double wasted;
	double charArea;
    
	if(contentRatio > spaceRatio)
	{
		wasted = ((1/spaceRatio) - (1/contentRatio)) * spaceRatio;
		double charWidth = 1.0 / width;
        charArea = (charWidth * charWidth) * spaceRatio;
	}
	else
	{
		wasted = (spaceRatio - contentRatio) / spaceRatio;
		double charHeight = 1.0 / height;
		charArea = (charHeight * charHeight) / spaceRatio;
	}

	int missing = (width * height) - num;

	wasted += missing * charArea;

	return wasted;
}

double findBest(int num, double spaceRatio, int &width, int &height)
{

    int bestWidth = -1;
	int bestHeight = -1;
	double bestWasted = -1;

    for(int i = 1; i <= num; i++)
	{
		int currentWidth = i;
		int currentHeight = 0;
		double currentWasted = wastedSpace(currentWidth, currentHeight, num, spaceRatio);

		if(bestWasted < 0 || currentWasted < bestWasted)
		{
			bestWidth = currentWidth;
			bestHeight = currentHeight;
			bestWasted = currentWasted;
		}
	}


	width = bestWidth;
	height = bestHeight;

	return bestWasted;
}

namespace wanikani
{

void draw(Order order, SDL_Surface *surface, SDL_Rect rect)
{
	double ratio = double(rect.w) / double(rect.h);
	int w, h;
	double wasted = findBest(order.size(), ratio, w, h);

	double contentRatio = double(w) / double(h);
	double gridWidth = double(rect.w) / double(w);
	double gridHeight = double(rect.h) / double(h);

    int fontSize = contentRatio < ratio ? (int) gridHeight : (int) gridWidth;

	Kanji::loadFont("/usr/share/fonts/OTF/ipag.ttf", fontSize);

    for(int i = 0; i < order.size(); i++)
	{
		int x = (i % w) * gridWidth;
		int y = (i / w) * gridHeight;

		order.kanji(i).draw(surface, x, y);
	}

	Kanji::unloadFont();	

}
}
