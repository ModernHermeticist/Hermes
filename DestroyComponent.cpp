#include "main.h"

DestroyComponent::DestroyComponent(int _maximumHealth, int _maximumStamina, int _maximumMana,
	int _armor, float _block, float _dodge, float _parry, int _strength,
	int _agility, int _endurance, int _luck, int _intelligence, int _wisdom)
{
	baseStrength = _strength;
	baseAgility = _agility;
	baseEndurance = _endurance;
	baseLuck = _luck;
	baseIntelligence = _intelligence;
	baseWisdom = _wisdom;

	finalStrength = _strength;
	finalAgility = _agility;
	finalEndurance = _endurance;
	finalLuck = _luck;
	finalIntelligence = _intelligence;
	finalWisdom = _wisdom;


	baseMaximumHealth = _maximumHealth;
	finalMaximumHealth = standardHealthAdjustment();
	currentHealth = finalMaximumHealth;

	baseMaximumStamina = _maximumStamina;
	finalMaximumStamina = standardStaminaAdjustment();
	currentStamina = finalMaximumStamina;

	baseMaximumMana = _maximumMana;
	finalMaximumMana = standardManaAdjustment();
	currentMana = finalMaximumMana;

	experienceValue = 0;

	baseArmor = _armor;
	finalArmor = _armor;
	baseBlock = _block;
	finalBlock = _block;
	finalBlock = standardBlockAdjustment();
	baseDodge = _dodge;
	finalDodge = _dodge;
	finalDodge = standardDodgeAdjustment();
	baseParry = _parry;
	finalParry = _parry;
	finalParry = standardParryAdjustment();

	alive = true;
}

DestroyComponent::DestroyComponent(int _maximumHealth, int _maximumStamina, int _maximumMana,
	int _experienceValue, int _armor, float _block, float _dodge, float _parry)
{
	baseStrength = 0;
	baseAgility = 0;
	baseEndurance = 0;
	baseLuck = 0;
	baseIntelligence = 0;
	baseWisdom = 0;

	finalStrength = 0;
	finalAgility = 0;
	finalEndurance = 0;
	finalLuck = 0;
	finalIntelligence = 0;
	finalWisdom = 0;

	baseMaximumHealth = _maximumHealth;
	finalMaximumHealth = standardHealthAdjustment();
	currentHealth = finalMaximumHealth;

	baseMaximumStamina = _maximumStamina;
	finalMaximumStamina = standardStaminaAdjustment();
	currentStamina = finalMaximumStamina;

	baseMaximumMana = _maximumMana;
	finalMaximumMana = standardManaAdjustment();
	currentMana = finalMaximumMana;

	experienceValue = _experienceValue;

	baseArmor = _armor;
	finalArmor = baseArmor;
	baseBlock = _block;
	finalBlock = standardBlockAdjustment();
	baseDodge = _dodge;
	finalDodge = standardDodgeAdjustment();
	baseParry = _parry;
	finalParry = standardParryAdjustment();

	alive = true;
}


DestroyComponent::~DestroyComponent()
{

}

int DestroyComponent::getExperienceValue() { return experienceValue; }

int DestroyComponent::getCurrentHealth() { return currentHealth; }
int DestroyComponent::getMaximumHealth() { return finalMaximumHealth; }

int DestroyComponent::getCurrentStamina() { return currentStamina; }
int DestroyComponent::getMaximumStamina() { return finalMaximumStamina; }

int DestroyComponent::getCurrentMana() { return currentMana; }
int DestroyComponent::getMaximumMana() { return finalMaximumMana; }

void DestroyComponent::setCurrentHealth(int val) { currentHealth = val; }
void DestroyComponent::setMaximumHealth(int val) { baseMaximumHealth = val; }

void DestroyComponent::setCurrentStamina(int val) { currentStamina = val; }
void DestroyComponent::setMaximumStamina(int val) { baseMaximumStamina = val; }

void DestroyComponent::setCurrentMana(int val) { currentMana = val; }
void DestroyComponent::setMaximumMana(int val) { baseMaximumMana = val; }

void DestroyComponent::adjustCurrentHealth(int val) { currentHealth += val; }
void DestroyComponent::adjustMaximumHealth(int val) { baseMaximumHealth += val; }
void DestroyComponent::adjustFinalMaximumHealthByItem(int val) { finalMaximumHealth += val; }

int DestroyComponent::standardHealthAdjustment()
{
	return baseMaximumHealth + finalEndurance;
}

int DestroyComponent::standardHealthAdjustmentPreview(int val)
{
	return finalMaximumHealth + val + finalEndurance;
}

void DestroyComponent::adjustCurrentStamina(int val) { currentStamina += val; }
void DestroyComponent::adjustMaximumStamina(int val) { baseMaximumStamina += val; }
void DestroyComponent::adjustFinalMaximumStaminaByItem(int val) { finalMaximumStamina += val; }

int DestroyComponent::standardStaminaAdjustment()
{
	return baseMaximumStamina + floor(finalEndurance / 2);
}

int DestroyComponent::standardStaminaAdjustmentPreview(int val)
{
	return finalMaximumStamina + floor((val + finalEndurance) / 2);
}

void DestroyComponent::adjustCurrentMana(int val) { currentMana += val; }
void DestroyComponent::adjustMaximumMana(int val) { baseMaximumMana += val; }
void DestroyComponent::adjustFinalMaximumManaByItem(int val) { finalMaximumMana += val; }

int DestroyComponent::standardManaAdjustment()
{
	return baseMaximumMana + finalIntelligence;
}

int DestroyComponent::standardManaAdjustmentPreview(int val)
{
	return finalMaximumMana + val + finalIntelligence;
}

void DestroyComponent::setStrength(int val) { baseStrength = val; }
void DestroyComponent::setAgility(int val) { baseAgility = val; }
void DestroyComponent::setEndurance(int val) { baseEndurance = val; }
void DestroyComponent::setLuck(int val) { baseLuck = val; }
void DestroyComponent::setIntelligence(int val) { baseIntelligence = val; }
void DestroyComponent::setWisdom(int val) { baseWisdom = val; }

void DestroyComponent::adjustStrength(int val) { baseStrength += val; }
void DestroyComponent::adjustAgility(int val) { baseAgility += val; }
void DestroyComponent::adjustEndurance(int val) { baseEndurance += val; }
void DestroyComponent::adjustLuck(int val) { baseLuck += val; }
void DestroyComponent::adjustIntelligence(int val) { baseIntelligence += val; }
void DestroyComponent::adjustWisdom(int val) { baseWisdom += val; }

void DestroyComponent::adjustFinalStrengthByItem(int val) { finalStrength += val; }
void DestroyComponent::adjustFinalAgilityByItem(int val) { finalAgility += val; }
void DestroyComponent::adjustFinalEnduranceByItem(int val) { finalEndurance += val; }
void DestroyComponent::adjustFinalLuckByItem(int val) { finalLuck += val; }
void DestroyComponent::adjustFinalIntelligenceByItem(int val) { finalIntelligence += val; }
void DestroyComponent::adjustFinallWisdomByItem(int val) { finalWisdom += val; }

int DestroyComponent::getStrength() { return finalStrength; }
int DestroyComponent::getAgility() { return finalAgility; }
int DestroyComponent::getEndurance() { return finalEndurance; }
int DestroyComponent::getLuck() { return finalLuck; }
int DestroyComponent::getIntelligence() { return finalIntelligence; }
int DestroyComponent::getWisdom() { return finalWisdom; }

int DestroyComponent::getArmor() { return finalArmor; }

float DestroyComponent::getDodge() { return finalDodge; }
float DestroyComponent::getBlock() { return finalBlock; }
float DestroyComponent::getParry() { return finalParry; }

bool DestroyComponent::isAlive() { return alive; }
void DestroyComponent::setAlive(bool val) { alive = val; }

void DestroyComponent::setArmor(int val) { baseArmor = val; }
void DestroyComponent::adjustArmor(int val) { baseArmor += val; }
void DestroyComponent::adjustFinalArmorByItem(int val) { finalArmor += val; }

void DestroyComponent::setDodge(float val) { baseDodge = val; }
void DestroyComponent::adjustDodge(float val) { baseDodge += val; }
void DestroyComponent::adjustFinalDodgeByItem(float val) { finalDodge += val; }

float DestroyComponent::standardDodgeAdjustment()
{
	return baseDodge + (finalAgility / 100 * finalLuck / 1000);
}

float DestroyComponent::standardDodgeAdjustmentPreview(int _agi, int _luck)
{
	return finalDodge + ((finalAgility + _agi) / 100 * (finalLuck + _luck) / 1000);
}


void DestroyComponent::setBlock(float val) { baseBlock = val; }
void DestroyComponent::adjustBlock(float val) { baseBlock += val; }
void DestroyComponent::adjustFinalBlockByItem(float val) { finalBlock += val; }

float DestroyComponent::standardBlockAdjustment()
{
	return baseBlock + (finalStrength / 100 * finalLuck / 1000);
}

float DestroyComponent::standardBlockAdjustmentPreview(int _str, int _luck)
{
	return finalBlock + ((finalStrength + _str) / 100 * (finalLuck + _luck) / 1000);
}

void DestroyComponent::setParry(float val) { baseParry = val; }
void DestroyComponent::ajustParry(float val) { baseParry += val; }
void DestroyComponent::adjustFinalParryByItem(float val) { finalParry += val; }

float DestroyComponent::standardParryAdjustment()
{
	return baseParry + (finalAgility / 100 * finalLuck / 1000);
}

float DestroyComponent::standardParryAdjustmentPreview(int _agi, int _luck)
{
	return finalParry + ((finalAgility + _agi) / 100 * (finalLuck + _luck) / 1000);
}

void DestroyComponent::applyBaseStatsToFinal()
{
	finalAgility = baseAgility;
	finalEndurance = baseEndurance;
	finalStrength = baseStrength;
	finalLuck = baseLuck;
	finalIntelligence = baseIntelligence;
	finalWisdom = baseWisdom;
}

void DestroyComponent::applyOtherBaseStatsToFinal()
{
	finalMaximumHealth = baseMaximumHealth;
	finalMaximumStamina = baseMaximumStamina;
	finalMaximumMana = baseMaximumMana;
	finalArmor = baseArmor;
	finalBlock = baseBlock;
	finalDodge = baseDodge;
	finalParry = baseParry;
}

void DestroyComponent::die(Entity* owner)
{
	owner->setSprite('%');
	owner->setSpriteForeground(TCOD_red);
	alive = false;
}