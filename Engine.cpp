#include "main.h"


Engine::Engine(int _screen_width, int _screen_height, int _world_width, int _world_height)
{
	screen_width = _screen_width;
	screen_height = _screen_height;
	world_width = _world_width;
	world_height = _world_height;
	player = new Player(0, 0, '@');

	world = new Tile * [world_width];
	for (int i = 0; i < world_width; i++)
	{
		world[i] = new Tile[world_height];
	}
}

Engine::~Engine()
{
	delete player;
	for (int i = 0; i < world_width; i++)
	{
		delete[] world[i];
	}
	delete[] world;
	for (int i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}
}

void Engine::loadMapFile(std::string fileName)
{
	xp::RexImage map(fileName);

	for (int i = 0; i < map.getWidth(); i++)
	{
		for (int j = 0; j < map.getHeight(); j++)
		{
			xp::RexTile t = *map.getTile(0, i, j);
			xp::RexTile eT = *map.getTile(1, i, j);
			TCODColor c = TCOD_black;
			c.r = t.fore_red;
			c.b = t.fore_blue;
			c.g = t.fore_green;
			Tile newTile = Tile(i, j, t.character, c, TCOD_black);
			int sprite = newTile.getSprite();
			if (isImpassibleSprite(sprite))
			{
				newTile.setWalkable(false);
				newTile.setBlocks(true);
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
				Entity* entity = new Entity(i, j, eT.character, cF, cB);
				entities.push_back(entity);
			}
			world[i][j] = newTile;
		}
	}
}

Player* Engine::getPlayer()
{
	return player;
}

Tile** Engine::getWorld()
{
	return world;
}

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
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		Entity* entity = *it;
		entity->Update(world);
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

std::vector<std::string> Engine::getLog()
{
	return log;
}
void Engine::addToLog(std::string message)
{
	if (log.size() > 6) log.erase(log.begin());
	log.push_back(message);
}

bool Engine::isImpassibleSprite(int sprite)
{
	if (sprite == TOP_LEFT_CORNER_WALL ||
		sprite == BOTTOM_RIGHT_CORNER_WALL ||
		sprite == VERTICAL_WALL ||
		sprite == HORIZONTAL_WALL ||
		sprite == TOP_FORK_WALL ||
		sprite == BOTTOM_FORK_WALL ||
		sprite == LEFT_FORK_WALL ||
		sprite == RIGHT_FORK_WALL ||
		sprite == WATER) return true;
	return false;
}