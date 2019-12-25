#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(int _xPos, int _yPos, int _sprite);
	~Player();
	void Update(TCOD_key_t key, Tile** tiles);

	int getXPos();
	int getYPos();

	int getSprite();

	bool canMoveTo(Tile tile, int newX, int newY);

private:
	int xPos;
	int yPos;

	int sprite;

};

#endif