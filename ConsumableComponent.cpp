#include "main.h"


ConsumableComponent::ConsumableComponent()
{
	type = Consumable_Type::NONE;
	effectComponent = NULL;
}

ConsumableComponent::ConsumableComponent(Consumable_Type _type, EffectComponent* _effectComponent)
{
	type = _type;
	effectComponent = _effectComponent;
}

ConsumableComponent::~ConsumableComponent()
{
	if (effectComponent != NULL) delete effectComponent;
}

EffectComponent* ConsumableComponent::getEffectComponent() { return effectComponent; }