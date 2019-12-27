#include "main.h"

DestroyComponent::DestroyComponent(int _maximumHealth)
{
	maximumHealth = _maximumHealth;
	currentHealth = maximumHealth;
	alive = true;
}

DestroyComponent::~DestroyComponent()
{

}

int DestroyComponent::getCurrentHealth() { return currentHealth; }
int DestroyComponent::getMaximumHealth() { return maximumHealth; }

void DestroyComponent::setCurrentHealth(int val) { currentHealth = val; }
void DestroyComponent::setMaximumHealtH(int val) { maximumHealth = val; }

void DestroyComponent::adjustCurrentHealth(int val) { currentHealth += val; }
void DestroyComponent::adjustMaximumHealth(int val) { currentHealth += val; }

bool DestroyComponent::isAlive() { return alive; }
void DestroyComponent::setAlive(bool val) { alive = val; }