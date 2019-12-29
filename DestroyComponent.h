#ifndef DESTROYCOMPONENT_H
#define DESTROYCOMPONENT_H

class Entity;

class DestroyComponent
{
public:
	DestroyComponent(int _maximumHealth, int _maximumStamina, int _maximumMana, int _armor, float _block, float _dodge, float _parry);
	DestroyComponent(int _maximumHealth, int _maximumStamina, int _maximumMana, int _experienceValue, int _armor, float _block, float _dodge, float _parry);
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
	void setMaximumHealtH(int val);

	void setCurrentStamina(int val);
	void setMaximumStamina(int val);
	
	void setCurrentMana(int val);
	void setMaximumMana(int val);

	void adjustCurrentHealth(int val);
	void adjustMaximumHealth(int val);

	void adjustCurrentStamina(int val);
	void adjustMaximumStamina(int val);

	void adjustCurrentMana(int val);
	void adjustMaximumMana(int val);

	void setArmor(int val);
	void adjustArmor(int val);

	void setDodge(float val);
	void adjustDodge(float val);

	void setBlock(float val);
	void adjustBlock(float val);

	void setParry(float val);
	void ajustParry(float val);

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

	int armor;
	float dodge;
	float block;
	float parry;

	bool alive;

};

#endif
