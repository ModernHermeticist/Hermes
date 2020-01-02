#include "main.h"

ItemComponent::ItemComponent()
{
	minimumDamage = NULL;
	maximumDamage = NULL;
	armor = NULL;
	health = NULL;
	stamina = NULL;
	mana = NULL;
	dodge = NULL;
	block = NULL;
	parry = NULL;
	slot = EquipmentComponent::EQUIPMENTSLOT::none;
	equipped = false;
	consumableComponent = NULL;
}

ItemComponent::ItemComponent(int _minimumDamage, int _maximumDamage, int _armor, int _health, int _stamina,
	int _mana, float _dodge, float _block, float _parry, EquipmentComponent::EQUIPMENTSLOT _slot)
{
	minimumDamage = _minimumDamage;
	maximumDamage = _maximumDamage;
	armor = _armor;
	health = _health;
	stamina = _stamina;
	mana = _mana;
	dodge = _dodge;
	block = _block;
	parry = _parry;
	slot = _slot;
	equipped = false;
	consumableComponent = NULL;
}

ItemComponent::ItemComponent(ConsumableComponent* _consumableComponent)
{
	minimumDamage = NULL;
	maximumDamage = NULL;
	armor = NULL;
	health = NULL;
	stamina = NULL;
	mana = NULL;
	dodge = NULL;
	block = NULL;
	parry = NULL;
	slot = EquipmentComponent::EQUIPMENTSLOT::none;
	equipped = false;
	consumableComponent = _consumableComponent;
}

ItemComponent::~ItemComponent()
{

}

int ItemComponent::getMinimumDamage() { return minimumDamage; }
int ItemComponent::getMaximumDamage() { return maximumDamage; }

int ItemComponent::getArmor() { return armor; }

int ItemComponent::getHealth() { return health; }
int ItemComponent::getStamina() { return stamina; }
int ItemComponent::getMana() { return mana; }

float ItemComponent::getDodge() { return dodge; }
float ItemComponent::getBlock() { return block; }
float ItemComponent::getParry() { return parry; }

EquipmentComponent::EQUIPMENTSLOT ItemComponent::getSlot() { return slot; }

bool ItemComponent::isEquipped() { return equipped; }
void ItemComponent::setEquipped(bool val) { equipped = val; }

ConsumableComponent* ItemComponent::getConsumableComponent() { return consumableComponent ;}