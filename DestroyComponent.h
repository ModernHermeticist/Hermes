#ifndef DESTROYCOMPONENT_H
#define DESTROYCOMPONENT_H

class Entity;

class DestroyComponent
{
public:
	DestroyComponent(int _maximumHealth, int _maximumStamina, int _maximumMana, 
		int _armor, float _block, float _dodge, float _parry, int _strength,
		int _agility, int _endurance, int _luck, int _intelligence, int _wisdom);
	DestroyComponent(int _maximumHealth, int _maximumStamina, int _maximumMana, 
		int _experienceValue, int _armor, float _block, float _dodge, float _parry);
	~DestroyComponent();

	int getExperienceValue();

	int getCurrentHealth();
	int getMaximumHealth();

	int getCurrentStamina();
	int getMaximumStamina();

	int getCurrentMana();
	int getMaximumMana();

	int getArmor();

	float getDodge();
	float getBlock();
	float getParry();

	void setCurrentHealth(int val);
	void setMaximumHealth(int val);

	void setCurrentStamina(int val);
	void setMaximumStamina(int val);
	
	void setCurrentMana(int val);
	void setMaximumMana(int val);

	void adjustCurrentHealth(int val);
	void adjustMaximumHealth(int val);

	int standardHealthAdjustment(int val);
	int standardHealthAdjustment(int val, int _endurance);

	void adjustCurrentStamina(int val);
	void adjustMaximumStamina(int val);

	int standardStaminaAdjustment(int val);
	int standardStaminaAdjustment(int val, int _endurance);

	void adjustCurrentMana(int val);
	void adjustMaximumMana(int val);

	int standardManaAdjustment(int val);
	int standardManaAdjustment(int val, int _intelligence);

	void setStrength(int val);
	void setAgility(int val);
	void setEndurance(int val);
	void setLuck(int val);
	void setIntelligence(int val);
	void setWisdom(int val);

	void adjustStrength(int val);
	void adjustAgility(int val);
	void adjustEndurance(int val);
	void adjustLuck(int val);
	void adjustIntelligence(int val);
	void adjustWisdom(int val);

	int getStrength();
	int getAgility();
	int getEndurance();
	int getLuck();
	int getIntelligence();
	int getWisdom();

	void setArmor(int val);
	void adjustArmor(int val);

	void setDodge(float val);
	void adjustDodge(float val);

	float standardDodgeAdjustment(float val);
	float standardDodgeAdjustment(float val, int _agility, int _luck);

	void setBlock(float val);
	void adjustBlock(float val);

	float standardBlockAdjustment(float val);
	float standardBlockAdjustment(float val, int _strength, int _luck);

	void setParry(float val);
	void ajustParry(float val);

	float standardParryAdjustment(float val);
	float standardParryAdjustment(float val, int _agility, int _luck);

	void die(Entity* owner);

	bool isAlive();
	void setAlive(bool val);
private:
	int experienceValue;

	int currentHealth;
	int maximumHealth;

	int currentStamina;
	int maximumStamina;

	int currentMana;
	int maximumMana;

	int strength;
	int agility;
	int endurance;
	int luck;
	int intelligence;
	int wisdom;

	int armor;
	float dodge;
	float block;
	float parry;

	bool alive;

};

#endif
