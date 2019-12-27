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

	int getDamage();

private:
	int minimumAttackPower;
	int maximumAttackPower;
};

#endif