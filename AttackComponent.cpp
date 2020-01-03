#include "main.h"

AttackComponent::AttackComponent() { baseMinimumAttackPower = 1; baseMaximumAttackPower = 1; ; finalMinimumAttackPower = 1; finalMaximumAttackPower = 1; }

AttackComponent::AttackComponent(int _minimumAttackPower, int _maximumAttackPower)
{
	baseMinimumAttackPower = _minimumAttackPower;
	baseMaximumAttackPower = _maximumAttackPower;
	finalMinimumAttackPower = baseMinimumAttackPower;
	finalMaximumAttackPower = baseMaximumAttackPower;
}

AttackComponent::~AttackComponent()
{

}

int AttackComponent::getMinimumAttackPower() { return finalMinimumAttackPower; }
int AttackComponent::getMaximumAttackPower() { return finalMaximumAttackPower; }

void AttackComponent::setMinimumAttackPower(int val) { baseMinimumAttackPower = val; }
void AttackComponent::setMaximumAttackPower(int val) { baseMaximumAttackPower = val; }

void AttackComponent::adjustMinimumAttackPower(int val) { baseMinimumAttackPower += val; }
void AttackComponent::adjustMaximumAttackPower(int val) { baseMaximumAttackPower += val; }

void AttackComponent::adjustFinalMinimumAttackPowerByItem(int val) { finalMinimumAttackPower += val; }
void AttackComponent::adjustFinalMaximumAttackPowerByItem(int val) { finalMaximumAttackPower += val; }

int AttackComponent::standardMinimumAttackPowerAdjustment()
{
	DestroyComponent* destroyComponent = engine->getPlayer()->getDestroyComponent();
	return baseMinimumAttackPower + (int)floor(destroyComponent->getStrength() / 8);
}

int AttackComponent::standardMinimumAttackPowerAdjustmentPreview(int _strength)
{
	DestroyComponent* destroyComponent = engine->getPlayer()->getDestroyComponent();
	return finalMinimumAttackPower + (int)floor((_strength + destroyComponent->getStrength()) / 8);
}

int AttackComponent::standardMaximumAttackPowerAdjustment()
{
	DestroyComponent* destroyComponent = engine->getPlayer()->getDestroyComponent();
	return baseMaximumAttackPower + (int)floor(destroyComponent->getStrength() / 8);
}

int AttackComponent::standardMaximumAttackPowerAdjustmentPreview(int _strength)
{
	DestroyComponent* destroyComponent = engine->getPlayer()->getDestroyComponent();
	return finalMaximumAttackPower + (int)floor((_strength + destroyComponent->getStrength()) / 8);
}

void AttackComponent::applyBaseStatsToFinal()
{
	finalMinimumAttackPower = baseMinimumAttackPower;
	finalMaximumAttackPower = baseMaximumAttackPower;
}

int AttackComponent::getDamage()
{
	return TCOD_random_get_int(NULL, finalMinimumAttackPower, finalMaximumAttackPower);
}