#include "main.h"



Engine::Engine(int _screen_width, int _screen_height, int _world_width, int _world_height)
{
	screen_width = _screen_width;
	screen_height = _screen_height;
	world_width = _world_width;
	world_height = _world_height;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, NULL);
	PlayerAI* playerAI = new PlayerAI();
	DestroyComponent* destroyComponent = new DestroyComponent(25);
	player = new Player(0, 0, '@', playerAI, destroyComponent);
	map = new Map(screen_width, screen_height);
	fovRadius = 10;
	computeFov = true;
	turn = TURN::PLAYER_TURN;
}

Engine::~Engine()
{
	delete player;
	delete map;
	for (int i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}
}

void Engine::loadMapFile(std::string fileName)
{
	xp::RexImage fileMap(fileName);

	for (int i = 0; i < fileMap.getWidth(); i++)
	{
		for (int j = 0; j < fileMap.getHeight(); j++)
		{
			xp::RexTile t = *fileMap.getTile(0, i, j);
			xp::RexTile eT = *fileMap.getTile(1, i, j);
			TCODColor c = TCOD_black;
			c.r = t.fore_red;
			c.b = t.fore_blue;
			c.g = t.fore_green;
			Tile newTile = Tile(i, j, t.character, c, TCOD_black);
			int sprite = newTile.getSprite();
			map->getTCODMap()->setProperties(i, j, true, true);
			if (isImpassibleSprite(sprite))
			{
				newTile.setWalkable(false);
				newTile.setBlocks(true);
				if (sprite != WATER)
					map->getTCODMap()->setProperties(i, j, false, false);
			}

			if (eT.character != 0)
			{
				TCODColor cF = TCOD_black;
				cF.r = eT.fore_red;
				cF.b = eT.fore_blue;
				cF.g = eT.fore_green;
				TCODColor cB = TCOD_black;
				cB.r = eT.back_red;
				cB.b = eT.back_blue;
				cB.g = eT.back_green;
				if (eT.character == '@')
				{
					player->setXPos(i);
					player->setYPos(j);
					player->setSprite(eT.character);
					player->setSpriteForeground(cF);
					player->setSpriteBackground(cB);
				}
				else
				{
					EnemyAI* enemyAI = new EnemyAI();
					DestroyComponent* destroyComponent = new DestroyComponent(10);
					Entity* entity = new Entity(i, j, eT.character, cF, cB, enemyAI, NULL, destroyComponent);
					entities.push_back(entity);
				}
			}
			map->setTile(i, j, newTile);
		}
	}
}

Player* Engine::getPlayer()
{
	return player;
}

Map* Engine::getMap() { return map; }

void Engine::addEntity(Entity* entity)
{
	entities.push_back(entity);
}

std::vector<Entity*> Engine::getEntities()
{
	return entities;
}

void Engine::updateEntities()
{
	int numOfEntities = entities.size();
	for (int i = 0; i < numOfEntities; i++)
	{
		Entity* entity = entities[i];
		entity->Update();
	}
}

int Engine::getWorldWidth()
{
	return world_width;
}

int Engine::getWorldHeight()
{
	return world_height;
}

std::vector<LogEntry> Engine::getLog()
{
	return log;
}
void Engine::addToLog(std::string message, TCODColor color)
{
	LogEntry lE = LogEntry(message, color);
	if (log.size() > 6) log.erase(log.begin());
	log.push_back(lE);
}

bool Engine::isImpassibleSprite(int sprite)
{
	if (sprite == TOP_LEFT_CORNER_WALL ||
		sprite == TOP_RIGHT_CORNER_WALL ||
		sprite == BOTTOM_RIGHT_CORNER_WALL ||
		sprite == BOTTOM_LEFT_CORNER_WALL ||
		sprite == VERTICAL_WALL ||
		sprite == HORIZONTAL_WALL ||
		sprite == TOP_FORK_WALL ||
		sprite == BOTTOM_FORK_WALL ||
		sprite == LEFT_FORK_WALL ||
		sprite == RIGHT_FORK_WALL ||
		sprite == WATER) return true;
	return false;
}

int Engine::getFovRadius()
{
	return fovRadius;
}

bool Engine::getComputeFov()
{
	return computeFov;
}
void Engine::setComputeFov(bool val)
{
	computeFov = val;
}

TCOD_key_t Engine::getLastKey() { return lastKey; }
void Engine::setLastKey(TCOD_key_t k) { lastKey = k; }