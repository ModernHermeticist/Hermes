#include "main.h"



Engine::Engine(int _screen_width, int _screen_height, int _world_width, int _world_height)
{
	screen_width = _screen_width;
	screen_height = _screen_height;
	world_width = _world_width;
	world_height = _world_height;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, NULL);
	PlayerAI* playerAI = new PlayerAI();
	int minimumDamage = 1;
	int maximumDamage = 5;
	AttackComponent* attackComponent = new AttackComponent(minimumDamage, maximumDamage);
	int health = 25;
	int stamina = 10;
	int mana = 10;
	int armor = 0;
	float block = 0.0;
	float dodge = 0.0;
	float parry = 0.0;
	int strength = 3;
	int agility = 1;
	int endurance = 2;
	int luck = 1;
	int intelligence = 1;
	int wisdom = 1;
	DestroyComponent* destroyComponent = new DestroyComponent(health, stamina, mana, armor, block, dodge, parry, strength, agility,
																endurance, luck, intelligence, wisdom);
	int inventoryCapacity = 10;
	InventoryComponent* inventoryComponent = new InventoryComponent(inventoryCapacity);
	EquipmentComponent* equipmentComponent = new EquipmentComponent();
	int xPos = 0;
	int yPos = 0;
	int sprite = 'p';
	TCODColor color = TCODColor::green;
	std::string name = "Healing Potion";
	std::string description = "A blood red potion. When uncorked a rich steam can be seen raising from the liquid.";
	ConsumableComponent::Consumable_Type type = ConsumableComponent::Consumable_Type::POTION;
	int effectValue = 5;
	Entity* potion = itemGenerators::generateHealingItem(xPos, yPos, sprite, color, name, description, type, effectValue);
	inventoryComponent->addToStorage(potion);
	player = new Player(0, 0, 1, "Player", playerAI, attackComponent, destroyComponent, inventoryComponent, equipmentComponent);
	//player = new Player(0, 0, 2, "Player", playerAI, attackComponent, destroyComponent, inventoryComponent, equipmentComponent);
	map = new Map(screen_width, screen_height);
	fovRadius = 10;
	refresh = false;
	computeFov = true;
	state = Engine::STATE::PLAYER_TURN;
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
			xp::RexTile tile = *fileMap.getTile(0, i, j);
			xp::RexTile entityTile = *fileMap.getTile(1, i, j);
			xp::RexTile itemTile = *fileMap.getTile(2, i, j);
			TCODColor color = TCOD_black;
			color.r = tile.fore_red;
			color.g = tile.fore_green;
			color.b = tile.fore_blue;
			Tile newTile = Tile(i, j, tile.character, color, TCOD_black);
			int sprite = newTile.getSprite();
			map->getTCODMap()->setProperties(i, j, true, true);
			if (isImpassibleSprite(sprite))
			{
				newTile.setWalkable(false);
				newTile.setBlocks(true);
				if (sprite != WATER)
					map->getTCODMap()->setProperties(i, j, false, false);
			}
			if (tile.character == '!')
			{
				int frameStart = rand() % 3 + TORCH1;
				AnimatorComponent* animatorComponent = new AnimatorComponent(TORCH1, TORCH4, frameStart, 25, true);
				Entity* entity = new Entity(i, j, TORCH1, TCODColor::white, TCODColor::black, "Torch", animatorComponent);
				entity->getAnimatorComponent()->setParent(entity);
				entities.push_back(entity);
			}
			else if (tile.character == '~')
			{
				int frameStart = WATER5;
				AnimatorComponent* animatorComponent = new AnimatorComponent(WATER5, WATER11, frameStart, 20, false);
				Entity* entity = new Entity(i, j, WATER5, TCODColor::white, TCODColor::black, "Water", animatorComponent);
				entity->getAnimatorComponent()->setParent(entity);
				entities.push_back(entity);
			}
			else if (tile.character == '.')
			{
				newTile.setSprite(WOOD_FLOOR_1);
				newTile.setVisibleForeground(TCODColor::white);
				newTile.setExploredForeground(TCODColor::darkGrey);
				map->setTile(i, j, newTile);
			}
			else
			{
				map->setTile(i, j, newTile);
			}
			if (entityTile.character != 0 && entityTile.character != 32)
			{
				TCODColor cF = TCOD_black;
				cF.r = entityTile.fore_red;
				cF.b = entityTile.fore_blue;
				cF.g = entityTile.fore_green;
				TCODColor cB = TCOD_black;
				cB.r = entityTile.back_red;
				cB.b = entityTile.back_blue;
				cB.g = entityTile.back_green;
				if (entityTile.character == 2)
				{
					player->setXPos(i);
					player->setYPos(j);
					player->setSprite(entityTile.character);
					player->setSpriteForeground(cF);
					player->setSpriteBackground(cB);
				}
				else
				{
					EnemyAI* enemyAI = new EnemyAI();
					AttackComponent* attackComponent = new AttackComponent(1, 3);
					DestroyComponent* destroyComponent = new DestroyComponent(10, 2, 0, 2, 0, 0, 0, 0);
					Entity* entity = new Entity(i, j, KOBOLD_1, cF, cB, "Kobold Whelp", enemyAI, attackComponent, destroyComponent, NULL, NULL);
					entities.push_back(entity);
				}
			}
			if (itemTile.character != 0 && itemTile.character != 32)
			{
				TCODColor cF = TCOD_black;
				cF.r = itemTile.fore_red;
				cF.b = itemTile.fore_blue;
				cF.g = itemTile.fore_green;
				TCODColor cB = TCOD_black;
				cB.r = itemTile.back_red;
				cB.b = itemTile.back_blue;
				cB.g = itemTile.back_green;

				ItemComponent* itemComponent = new ItemComponent(0, 2,0,0,0,0,0,0,0,EquipmentComponent::EQUIPMENTSLOT::rightHand);
				std::string description = "Legendary blade said to have been crafted from the soul of an ancient spirit of power.";
				Entity* entity = new Entity(i, j, itemTile.character, cF, cB, "Limirail, Blade of the Ninth Moon", description, itemComponent);
				entities.push_back(entity);
			}
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

void Engine::removeEntity(Entity* entity)
{
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		Entity* entityInStorage = *it;
		if (entity == entityInStorage)
		{
			entities.erase(it);
			return;
		}
	}
}

Engine::STATE Engine::updateEntities()
{
	int numOfEntities = (int)entities.size();
	for (int i = 0; i < numOfEntities; i++)
	{
		Entity* entity = entities[i];
		entity->Update();
	}
	return Engine::STATE::PLAYER_TURN;
}

void Engine::updateEntityAnimations()
{
	int numOfEntities = (int)entities.size();
	for (int i = 0; i < numOfEntities; i++)
	{
		Entity* entity = entities[i];
		AnimatorComponent* animatorComponent = entity->getAnimatorComponent();
		if (animatorComponent != NULL)
		{
			animatorComponent->animateCellOnTimer();
		}
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

std::vector<LogEntry> Engine::getGeneralLog()
{
	return generalLog;
}
std::vector<LogEntry> Engine::getCombatLog()
{
	return combatLog;
}
void Engine::addToGeneralLog(std::string message, TCODColor color)
{
	//36
	if (message.size() > 36)
	{
		do
		{
			LogEntry lE = LogEntry(message.substr(0, 36), color);
			if (generalLog.size() > maxLogHistory) generalLog.erase(generalLog.begin());
			generalLog.push_back(lE);
			message = message.substr(36);
		} while (message.size() > 36);
	}
	LogEntry lE = LogEntry(message.substr(0, 36), color);
	if (generalLog.size() > maxLogHistory) generalLog.erase(generalLog.begin());
	generalLog.push_back(lE);
}
void Engine::addToCombatLog(std::string message, TCODColor color)
{
	if (message.size() > 36)
	{
		do
		{
			LogEntry lE = LogEntry(message.substr(0, 35), color);
			if (combatLog.size() > maxLogHistory) combatLog.erase(combatLog.begin());
			combatLog.push_back(lE);
			message = message.substr(35);
		} while (message.size() > 36);
	}
	LogEntry lE = LogEntry(message.substr(0, 35), color);
	if (combatLog.size() > maxLogHistory) combatLog.erase(combatLog.begin());
	combatLog.push_back(lE);
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

Engine::STATE Engine::getState() { return state; }
void Engine::setState(Engine::STATE s) { state = s; }

bool Engine::getRefresh() { return refresh; }
void Engine::setRefresh(bool val) { refresh = val; }

void Engine::incrementGeneralLogPointer() 
{ 
	if (generalLogPointer < maxLogHistory && generalLogPointer < (int)generalLog.size()-7)
		generalLogPointer++; 
}
void Engine::decrementGeneralLogPointer() 
{ 
	if (generalLogPointer > 0)
		generalLogPointer--; 
}

void Engine::incrementCombatLogPointer()
{
	if (combatLogPointer < maxLogHistory && combatLogPointer < (int)combatLog.size() - 7)
		combatLogPointer++;
}
void Engine::decrementCombatLogPointer()
{
	if (combatLogPointer > 0)
		combatLogPointer--;
}

int Engine::getGeneralLogPointer() { return generalLogPointer; }
int Engine::getCombatLogPointer() { return combatLogPointer; }
