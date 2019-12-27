#ifndef DESTROYCOMPONENT_H
#define DESTROYCOMPONENT_H


class DestroyComponent
{
public:
	DestroyComponent(int _maximumHealth);
	~DestroyComponent();

	int getCurrentHealth();
	int getMaximumHealth();

	void setCurrentHealth(int val);
	void setMaximumHealtH(int val);

	void adjustCurrentHealth(int val);
	void adjustMaximumHealth(int val);

	bool isAlive();
	void setAlive(bool val);
private:
	int currentHealth;
	int maximumHealth;

	bool alive;

};

#endif
