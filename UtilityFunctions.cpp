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

	void printLine(SDL_Renderer* renderer, std::string s, SDL_Color textColor, int x, int y)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(engine->getLogFont(), s.c_str(), textColor);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_Rect Message_rect; //create a rect
		Message_rect.x = x;  //controls the rect's x coordinate 
		Message_rect.y = y; // controls the rect's y coordinte
		Message_rect.w = 0; // controls the width of the rect
		Message_rect.h = 0; // controls the height of the rect
		SDL_QueryTexture(textTexture, NULL, NULL, &Message_rect.w, &Message_rect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &Message_rect);
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(textSurface);
	}

	SDL_Color mapTCODColorToSDLColor(TCODColor color)
	{
		SDL_Color c;

		c.a = 255;
		c.r = color.r;
		c.g = color.g;
		c.b = color.b;
		return c;
	}

	TCODColor mapSDLColorToTCODColor(SDL_Color color)
	{
		TCODColor c;

		c.r = color.r;
		c.g = color.g;
		c.b = color.b;
		return c;
	}
}