#pragma once

namespace wanikani
{
namespace grid
{
	double wastedSpace(int width, int &height, int num, double spaceRatio);
	double findBest(int num, double spaceRatio, int &width, int &height);
}
} //wanikani
