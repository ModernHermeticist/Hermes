#include "main.h"

DestroyComponent::DestroyComponent(int _maximumHealth, int _maximumStamina, int _maximumMana, 
	int _armor, float _block, float _dodge, float _parry)
{
	maximumHealth = _maximumHealth;
	currentHealth = maximumHealth;

	maximumStamina = _maximumStamina;
	currentStamina = maximumStamina;

	maximumMana = _maximumMana;
	currentMana = maximumMana;

	experienceValue = 0;

	armor = _armor;
	block = _block;
	dodge = _dodge;
	parry = _parry;

	alive = true;
}

DestroyComponent::DestroyComponent(int _maximumHealth, int _maximumStamina, int _maximumMana,
	int _experienceValue, int _armor, float _block, float _dodge, float _parry)
{
	maximumHealth = _maximumHealth;
	currentHealth = maximumHealth;

	maximumStamina = _maximumStamina;
	currentStamina = maximumStamina;

	maximumMana = _maximumMana;
	currentMana = maximumMana;

	experienceValue = _experienceValue;

	armor = _armor;
	block = _block;
	dodge = _dodge;
	parry = _parry;

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
void DestroyComponent::setMaximumHealtH(int val) { maximumHealth = val; }

void DestroyComponent::setCurrentStamina(int val) { currentStamina = val; }
void DestroyComponent::setMaximumStamina(int val) { maximumStamina = val; }

void DestroyComponent::setCurrentMana(int val) { currentMana = val; }
void DestroyComponent::setMaximumMana(int val) { maximumMana = val; }

void DestroyComponent::adjustCurrentHealth(int val) { currentHealth += val; }
void DestroyComponent::adjustMaximumHealth(int val) { currentHealth += val; }

void DestroyComponent::adjustCurrentStamina(int val) { currentStamina += val; }
void DestroyComponent::adjustMaximumStamina(int val) { maximumStamina += val; }

void DestroyComponent::adjustCurrentMana(int val) { currentMana += val; }
void DestroyComponent::adjustMaximumMana(int val) { maximumMana += val; }

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

void DestroyComponent::setBlock(float val) { block = val; }
void DestroyComponent::adjustBlock(float val) { block += val; }

void DestroyComponent::setParry(float val) { parry = val; }
void DestroyComponent::ajustParry(float val) { parry += val; }

void DestroyComponent::die(Entity* owner)
{
	owner->setSprite('%');
	owner->setSpriteForeground(TCOD_red);
	alive = false;
}