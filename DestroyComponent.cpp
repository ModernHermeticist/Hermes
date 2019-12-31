#include "main.h"

DestroyComponent::DestroyComponent(int _maximumHealth, int _maximumStamina, int _maximumMana,
	int _armor, float _block, float _dodge, float _parry, int _strength,
	int _agility, int _endurance, int _luck, int _intelligence, int _wisdom)
{
	strength = _strength;
	agility = _agility;
	endurance = _endurance;
	luck = _luck;
	intelligence = _intelligence;
	wisdom = _wisdom;


	maximumHealth = standardHealthAdjustment(_maximumHealth);
	currentHealth = maximumHealth;

	maximumStamina = standardStaminaAdjustment(_maximumStamina);
	currentStamina = maximumStamina;

	maximumMana = standardManaAdjustment(_maximumMana);
	currentMana = maximumMana;

	experienceValue = 0;

	armor = _armor;
	block = standardBlockAdjustment(_block);
	dodge = standardDodgeAdjustment(_dodge);
	parry = standardParryAdjustment(_parry);

	alive = true;
}

DestroyComponent::DestroyComponent(int _maximumHealth, int _maximumStamina, int _maximumMana,
	int _experienceValue, int _armor, float _block, float _dodge, float _parry)
{
	strength = 0;
	agility = 0;
	endurance = 0;
	luck = 0;
	intelligence = 0;
	wisdom = 0;

	maximumHealth = standardHealthAdjustment(_maximumHealth);
	currentHealth = maximumHealth;

	maximumStamina = standardStaminaAdjustment(_maximumStamina);
	currentStamina = maximumStamina;

	maximumMana = standardManaAdjustment(_maximumMana);
	currentMana = maximumMana;

	experienceValue = _experienceValue;

	armor = _armor;
	block = standardBlockAdjustment(_block);
	dodge = standardDodgeAdjustment(_dodge);
	parry = standardParryAdjustment(_parry);

	alive = true;
}


DestroyComponent::~DestroyComponent()
{

}

int DestroyComponent::getExperienceValue() { return experienceValue; }

int DestroyComponent::getCurrentHealth() { return currentHealth; }
int DestroyComponent::getMaximumHealth() { return maximumHealth; }

int DestroyComponent::getCurrentStamina() { return currentStamina; }
int DestroyComponent::getMaximumStamina() { return maximumStamina; }

int DestroyComponent::getCurrentMana() { return currentMana; }
int DestroyComponent::getMaximumMana() { return maximumMana; }

void DestroyComponent::setCurrentHealth(int val) { currentHealth = val; }
void DestroyComponent::setMaximumHealth(int val) { maximumHealth = val; }

void DestroyComponent::setCurrentStamina(int val) { currentStamina = val; }
void DestroyComponent::setMaximumStamina(int val) { maximumStamina = val; }

void DestroyComponent::setCurrentMana(int val) { currentMana = val; }
void DestroyComponent::setMaximumMana(int val) { maximumMana = val; }

void DestroyComponent::adjustCurrentHealth(int val) { currentHealth += val; }
void DestroyComponent::adjustMaximumHealth(int val) { currentHealth += val; }

int DestroyComponent::standardHealthAdjustment(int val)
{
	return val + (endurance * 2);
}

int DestroyComponent::standardHealthAdjustment(int val, int _endurance)
{
	return val + ((endurance + _endurance) * 2);
}

void DestroyComponent::adjustCurrentStamina(int val) { currentStamina += val; }
void DestroyComponent::adjustMaximumStamina(int val) { maximumStamina += val; }

int DestroyComponent::standardStaminaAdjustment(int val)
{
	return val + floor(endurance / 2);
}

int DestroyComponent::standardStaminaAdjustment(int val, int _endurance)
{
	return val + floor((endurance + _endurance) / 2);
}

void DestroyComponent::adjustCurrentMana(int val) { currentMana += val; }
void DestroyComponent::adjustMaximumMana(int val) { maximumMana += val; }

int DestroyComponent::standardManaAdjustment(int val)
{
	return val + intelligence;
}

int DestroyComponent::standardManaAdjustment(int val, int _intelligence)
{
	return val + intelligence + _intelligence;
}

void DestroyComponent::setStrength(int val) { strength = val; }
void DestroyComponent::setAgility(int val) { agility = val; }
void DestroyComponent::setEndurance(int val) { endurance = val; }
void DestroyComponent::setLuck(int val) { luck = val; }
void DestroyComponent::setIntelligence(int val) { intelligence = val; }
void DestroyComponent::setWisdom(int val) { wisdom = val; }

void DestroyComponent::adjustStrength(int val) { strength += val; }
void DestroyComponent::adjustAgility(int val) { agility += val; }
void DestroyComponent::adjustEndurance(int val) { endurance += val; }
void DestroyComponent::adjustLuck(int val) { luck += val; }
void DestroyComponent::adjustIntelligence(int val) { intelligence += val; }
void DestroyComponent::adjustWisdom(int val) { wisdom += val; }

int DestroyComponent::getStrength() { return strength; }
int DestroyComponent::getAgility() { return agility; }
int DestroyComponent::getEndurance() { return endurance; }
int DestroyComponent::getLuck() { return luck; }
int DestroyComponent::getIntelligence() { return intelligence; }
int DestroyComponent::getWisdom() { return wisdom; }

int DestroyComponent::getArmor() { return armor; }

float DestroyComponent::getDodge() { return dodge; }
float DestroyComponent::getBlock() { return block; }
float DestroyComponent::getParry() { return parry; }

bool DestroyComponent::isAlive() { return alive; }
void DestroyComponent::setAlive(bool val) { alive = val; }

void DestroyComponent::setArmor(int val) { armor = val; }
void DestroyComponent::adjustArmor(int val) { armor += val; }

void DestroyComponent::setDodge(float val) { dodge = val; }
void DestroyComponent::adjustDodge(float val) { dodge += val; }

float DestroyComponent::standardDodgeAdjustment(float val)
{
	return val + (agility / 100 * luck / 1000);
}

float DestroyComponent::standardDodgeAdjustment(float val, int _agility, int _luck)
{
	return val + ((agility + _agility) / 100 * (luck + _luck) / 1000);
}

void DestroyComponent::setBlock(float val) { block = val; }
void DestroyComponent::adjustBlock(float val) { block += val; }

float DestroyComponent::standardBlockAdjustment(float val)
{
	return val + (strength / 100 * luck / 1000);
}

float DestroyComponent::standardBlockAdjustment(float val, int _strength, int _luck)
{
	return val + ((strength + _strength) / 100 * (luck + _luck) / 1000);
}

void DestroyComponent::setParry(float val) { parry = val; }
void DestroyComponent::ajustParry(float val) { parry += val; }

float DestroyComponent::standardParryAdjustment(float val)
{
	return val + (agility / 100 * luck / 1000);
}

float DestroyComponent::standardParryAdjustment(float val, int _agility, int _luck)
{
	return val + ((agility + _agility) / 100 * (luck + _luck) / 1000);
}

void DestroyComponent::die(Entity* owner)
{
	owner->setSprite('%');
	owner->setSpriteForeground(TCOD_red);
	alive = false;
}