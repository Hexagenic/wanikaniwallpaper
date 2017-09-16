#include "grid.hpp"
#include <iostream>

namespace wanikani
{
namespace grid
{

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

}
}
