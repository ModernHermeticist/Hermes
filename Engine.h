#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
public:
	Engine(int _screen_width, int _screen_height, int _world_width, int _world_height);
	~Engine();

	void loadMapFile(std::string fileName);

	Player* getPlayer();

	Tile** getWorld();

	void addEntity(Entity* entity);
	std::vector<Entity*> getEntities();

	void updateEntities();

	int getWorldWidth();
	int getWorldHeight();

	std::vector<std::string> getLog();
	void addToLog(std::string message);

	bool isImpassibleSprite(int sprite);

private:
	int screen_width;
	int screen_height;

	int world_width;
	int world_height;

	Player* player;

	Tile** world;
	
	std::vector<Entity*> entities;

	std::vector<std::string> log;
};

extern Engine* engine;


#endif