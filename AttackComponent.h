#ifndef ATTACKCOMPONENT_H
#define ATTACKCOMPONENT_H

class AttackComponent
{
public:
	AttackComponent();
	AttackComponent(int _minimumAttackPower, int _maximumAttackPower);
	~AttackComponent();

	int getMinimumAttackPower();
	int getMaximumAttackPower();

	void setMinimumAttackPower(int val);
	void setMaximumAttackPower(int val);

	void adjustMinimumAttackPower(int val);
	void adjustMaximumAttackPower(int val);

	void adjustFinalMinimumAttackPowerByItem(int val);
	void adjustFinalMaximumAttackPowerByItem(int val);

	int standardMinimumAttackPowerAdjustment();
	int standardMinimumAttackPowerAdjustmentPreview(int _strength);

	int standardMaximumAttackPowerAdjustment();
	int standardMaximumAttackPowerAdjustmentPreview(int _strength);

	void applyBaseStatsToFinal();

	int getDamage();

private:
	int baseMinimumAttackPower;
	int finalMinimumAttackPower;
	int baseMaximumAttackPower;
	int finalMaximumAttackPower;
};

#endif