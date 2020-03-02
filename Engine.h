#ifndef ENGINE_H
#define ENGINE_H

class Player;
class LogEntry;

class Engine
{
public:
	enum class STATE{PLAYER_TURN, ENEMY_TURN, SHOW_CHARACTER_SCREEN, 
		SHOW_INVENTORY_SCREEN, SHOW_PROGRESSION_SCREEN, SELECTING_TARGET, PICK_UP_ITEM, INSPECT_ITEM,
		PROGRESS_CHARACTER};

	Engine(int _screen_width, int _screen_height, int _world_width, int _world_height);
	~Engine();

	void loadMapFile(std::string fileName);

	Player* getPlayer();

	Map* getMap();


	void addEntity(Entity* entity);
	std::vector<Entity*> getEntities();

	void removeEntity(Entity* entity);

	Engine::STATE updateEntities();

	void updateEntityAnimations();

	int getWorldWidth();
	int getWorldHeight();

	std::vector<LogEntry> getGeneralLog();
	std::vector<LogEntry> getCombatLog();
	void addToGeneralLog(std::string message, TCODColor c);
	void addToCombatLog(std::string message, TCODColor c);

	bool isImpassibleSprite(int sprite);

	int getFovRadius();

	bool getComputeFov();
	void setComputeFov(bool val);

	TCOD_key_t getLastKey();
	void setLastKey(TCOD_key_t k);

	Engine::STATE getState();
	void setState(Engine::STATE s);

	bool getRefresh();
	void setRefresh(bool val);

	void incrementGeneralLogPointer();
	void decrementGeneralLogPointer();
	void incrementCombatLogPointer();
	void decrementCombatLogPointer();

	int getGeneralLogPointer();
	int getCombatLogPointer();

private:
	int fovRadius;
	bool computeFov;

	int screen_width;
	int screen_height;

	int world_width;
	int world_height;

	int generalLogPointer = 0;
	int combatLogPointer = 0;
	int maxLogHistory = 200;

	STATE state;

	bool refresh;

	Player* player;

	Map* map;
	
	std::vector<Entity*> entities;

	std::vector<LogEntry> generalLog;
	std::vector<LogEntry> combatLog;

	TCOD_key_t lastKey;
};

extern Engine* engine;


#endif