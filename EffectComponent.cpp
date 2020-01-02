#include "main.h"

EffectComponent::EffectComponent()
{
	effectValue = 0;
	effectType = Effect_Type::NONE;
}

EffectComponent::EffectComponent(int _effectValue, Effect_Type _effectType)
{
	effectValue = _effectValue;
	effectType = _effectType;
}

EffectComponent::~EffectComponent()
{

}

int EffectComponent::getEffectValue() { return effectValue; }
EffectComponent::Effect_Type EffectComponent::getEffectType(){ return effectType; }