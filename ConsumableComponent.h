#ifndef CONSUMABLECOMPONENT_H
#define CONSUMABLECOMPONENT_H

class ConsumableComponent
{
public:
	enum class Consumable_Type {POTION, SCROLL, NONE};

	ConsumableComponent();
	ConsumableComponent(Consumable_Type _type, EffectComponent* _effectComponent);
	~ConsumableComponent();

	EffectComponent* getEffectComponent();

private:
	EffectComponent* effectComponent;
	Consumable_Type type;

};

#endif