#include "main.h"

AttackComponent::AttackComponent() { minimumAttackPower = 1; maximumAttackPower = 1; }

AttackComponent::AttackComponent(int _minimumAttackPower, int _maximumAttackPower)
{
	minimumAttackPower = _minimumAttackPower;
	maximumAttackPower = _maximumAttackPower;
}

AttackComponent::~AttackComponent()
{

}

int AttackComponent::getMinimumAttackPower() { return minimumAttackPower; }
int AttackComponent::getMaximumAttackPower() { return maximumAttackPower; }

void AttackComponent::setMinimumAttackPower(int val) { minimumAttackPower = val; }
void AttackComponent::setMaximumAttackPower(int val) { maximumAttackPower = val; }

void AttackComponent::adjustMinimumAttackPower(int val) { minimumAttackPower += val; }
void AttackComponent::adjustMaximumAttackPower(int val) { maximumAttackPower += val; }

int AttackComponent::getDamage()
{
	return TCOD_random_get_int(NULL, minimumAttackPower, maximumAttackPower);
}