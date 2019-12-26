#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
public:
	Engine(int _screen_width, int _screen_height, int _world_width, int _world_height);
	~Engine();

	void loadMapFile(std::string fileName);

	Player* getPlayer();

	Map* getMap();


	void addEntity(Entity* entity);
	std::vector<Entity*> getEntities();

	void updateEntities();

	int getWorldWidth();
	int getWorldHeight();

	std::vector<LogEntry> getLog();
	void addToLog(std::string message, TCODColor c);

	bool isImpassibleSprite(int sprite);

	int getFovRadius();

	bool getComputeFov();
	void setComputeFov(bool val);

private:
	int fovRadius;
	bool computeFov;

	int screen_width;
	int screen_height;

	int world_width;
	int world_height;

	Player* player;

	Map* map;
	
	std::vector<Entity*> entities;

	std::vector<LogEntry> log;
};

extern Engine* engine;


#endif