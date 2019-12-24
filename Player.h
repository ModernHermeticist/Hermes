#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(int _xPos, int _yPos);
	~Player();
	void Update(TCOD_key_t key, std::vector<Tile*> tiles);

	int getXPos();
	int getYPos();


private:
	int xPos;
	int yPos;


};

#endif