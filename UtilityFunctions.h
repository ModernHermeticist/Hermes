#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

namespace utilityfunctions
{
	std::vector<int> getCardinalDirectionXYValues(int cardinalDirection);

	void printLine(SDL_Renderer* renderer, std::string s, SDL_Color textColor, int x, int y);

	SDL_Color mapTCODColorToSDLColor(TCODColor color);
	TCODColor mapSDLColorToTCODColor(SDL_Color color);
}

#endif
