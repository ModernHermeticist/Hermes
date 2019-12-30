#ifndef ITEMCOMPONENT_H
#define ITEMCOMPONENT_H

class EquipmentComponent;

class ItemComponent
{
public:
	ItemComponent();
	ItemComponent(int _minimumDamage, int _maximumDamage, int _armor, int _health, int _stamina,
		int _mana, float _dodge, float _block, float _parry, EquipmentComponent::EQUIPMENTSLOT _slot);
	~ItemComponent();

	int getMinimumDamage();
	int getMaximumDamage();

	int getArmor();

	int getHealth();
	int getStamina();
	int getMana();

	float getDodge();
	float getBlock();
	float getParry();

	EquipmentComponent::EQUIPMENTSLOT getSlot();

	bool isEquipped();
	void setEquipped(bool val);

private:
	int minimumDamage;
	int maximumDamage;

	int armor;

	int health;
	int stamina;
	int mana;

	float dodge;
	float block;
	float parry;

	EquipmentComponent::EQUIPMENTSLOT slot;

	bool equipped;
};

#endif