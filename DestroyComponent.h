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
	void adjustFinalMaximumHealthByItem(int val);

	int standardHealthAdjustment();
	int standardHealthAdjustmentPreview(int val);

	void adjustCurrentStamina(int val);
	void adjustMaximumStamina(int val);
	void adjustFinalMaximumStaminaByItem(int val);

	int standardStaminaAdjustment();
	int standardStaminaAdjustmentPreview(int val);

	void adjustCurrentMana(int val);
	void adjustMaximumMana(int val);
	void adjustFinalMaximumManaByItem(int val);

	int standardManaAdjustment();
	int standardManaAdjustmentPreview(int val);

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

	void adjustFinalStrengthByItem(int val);
	void adjustFinalAgilityByItem(int val);
	void adjustFinalEnduranceByItem(int val);
	void adjustFinalLuckByItem(int val);
	void adjustFinalIntelligenceByItem(int val);
	void adjustFinallWisdomByItem(int val);

	int getStrength();
	int getAgility();
	int getEndurance();
	int getLuck();
	int getIntelligence();
	int getWisdom();

	void setArmor(int val);
	void adjustArmor(int val);
	void adjustFinalArmorByItem(int val);

	void setDodge(float val);
	void adjustDodge(float val);
	void adjustFinalDodgeByItem(float val);

	float standardDodgeAdjustment();
	float standardDodgeAdjustmentPreview(int _agi, int _luck);

	void setBlock(float val);
	void adjustBlock(float val);
	void adjustFinalBlockByItem(float val);

	float standardBlockAdjustment();
	float standardBlockAdjustmentPreview(int _str, int _luck);

	void setParry(float val);
	void ajustParry(float val);
	void adjustFinalParryByItem(float val);

	float standardParryAdjustment();
	float standardParryAdjustmentPreview(int _agi, int _luck);

	void applyBaseStatsToFinal();
	void applyOtherBaseStatsToFinal();

	void die(Entity* owner);

	bool isAlive();
	void setAlive(bool val);
private:
	int experienceValue;

	int currentHealth;
	int maximumHealth;

	int baseMaximumHealth;
	int finalMaximumHealth;

	int currentStamina;
	int maximumStamina;

	int baseMaximumStamina;
	int finalMaximumStamina;

	int currentMana;
	int maximumMana;

	int baseMaximumMana;
	int finalMaximumMana;

	int baseStrength;
	int finalStrength;

	int baseAgility;
	int finalAgility;

	int baseEndurance;
	int finalEndurance;

	int baseLuck;
	int finalLuck;

	int baseIntelligence;
	int finalIntelligence;

	int baseWisdom;
	int finalWisdom;

	int baseArmor;
	int finalArmor;

	float baseDodge;
	float finalDodge;

	float baseBlock;
	float finalBlock;

	float baseParry;
	float finalParry;


	bool alive;

};

#endif
