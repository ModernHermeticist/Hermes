#include "main.h"

namespace utilityfunctions
{
	std::vector<int> getCardinalDirectionXYValues(int cardinalDirection)
	{
		std::vector<int> xyVal;
		switch (cardinalDirection)
		{
			case NORTH: xyVal.push_back(0); xyVal.push_back(-1); break;
			case SOUTH: xyVal.push_back(0); xyVal.push_back(1); break;
			case EAST: xyVal.push_back(1); xyVal.push_back(0); break;
			case WEST: xyVal.push_back(-1); xyVal.push_back(0); break;
			case NORTHWEST: xyVal.push_back(-1); xyVal.push_back(-1); break;
			case NORTHEAST: xyVal.push_back(1); xyVal.push_back(-1); break;
			case SOUTHWEST: xyVal.push_back(-1); xyVal.push_back(1); break;
			case SOUTHEAST: xyVal.push_back(1); xyVal.push_back(1); break;
			default: xyVal.push_back(-10); xyVal.push_back(-10); break;
		}
		return xyVal;
	}
}