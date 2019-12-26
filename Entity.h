#ifndef ENTITY_H
#define ENTITY_H

static const int TRACKING_TURNS = 3;

class Entity
{
public:
	enum xDirection { left = -1, right = 1};
	enum yDirection { up = -1, down = 1 };

	Entity(int _xPos, int _yPos, int _sprite, TCODColor _spriteForeground, TCODColor _spriteBackground);
	~Entity();
	void Update(Tile** tiles, int targetX, int targetY);

	int getXPos();
	int getYPos();

	int getSprite();

	TCODColor getSpriteForeground();
	TCODColor getSpriteBackground();

	void setSpriteForeground(TCODColor c);
	void setSpriteBackground(TCODColor c);

	bool canMoveTo(Tile tile, int newX, int newY);


private:
	int xPos;
	int yPos;

	int sprite;

	int moveCount;

	bool alive;

	TCODColor spriteForeground;
	TCODColor spriteBackground;

};

#endif