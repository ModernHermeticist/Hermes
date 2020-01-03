#include "main.h"

namespace itemGenerators
{

	Entity* generateHealingItem(int xPos, int yPos, int sprite, TCODColor color, std::string name,
		std::string description, ConsumableComponent::Consumable_Type type, int effectValue)
	{
		Entity* healingItem = new Entity(xPos, yPos, sprite, color, TCODColor::black, name, description,
			new ItemComponent(
				new ConsumableComponent(
					type, new EffectComponent(effectValue, EffectComponent::Effect_Type::HEAL))));
		return healingItem;
	}
}