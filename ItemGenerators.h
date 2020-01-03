#ifndef ITEMGENERATORS_H
#define ITEMGENERATORS_H

namespace itemGenerators
{

	Entity* generateHealingItem(int xPos, int yPos, int sprite, TCODColor color, std::string name,
		std::string description, ConsumableComponent::Consumable_Type type, int effectValue);

}

#endif