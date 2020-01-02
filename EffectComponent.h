#ifndef EFFECTCOMPONENT_H
#define EFFECTCOMPONENT_H

class EffectComponent
{
public:
	enum class Effect_Type {HEAL, DAMAGE, NONE};
	EffectComponent();
	EffectComponent(int _effectValue, Effect_Type _effectType);
	~EffectComponent();

	int getEffectValue();
	Effect_Type getEffectType();

private:
	int effectValue;
	Effect_Type effectType;
};

#endif
