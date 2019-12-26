#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(int _xPos, int _yPos, int _sprite, int _maximumHealth);
	~Player();
	void Update(TCOD_key_t key, Tile** tiles);

	int getXPos();
	int getYPos();

	void setXPos(int val);
	void setYPos(int val);

	int getSprite();

	TCODColor getSpriteForeground();
	TCODColor getSpriteBackground();

	void setSprite(int s);
	void setSpriteForeground(TCODColor c);
	void setSpriteBackground(TCODColor c);

	int getCurrentHealth();
	int getMaximumHealth();

	void setCurrentHealth(int val);
	void setMaximumHealtH(int val);

	void takeDamage(int val);
	void heal(int val);

	bool canMoveTo(Tile tile, int newX, int newY);

private:
	int xPos;
	int yPos;

	int sprite;
	TCODColor spriteForeground;
	TCODColor spriteBackground;

	int currentHealth;
	int maximumHealth;

	bool alive;

};

#endif