#include "main.h"

InventoryComponent::InventoryComponent(int _capacity)
{
	capacity = _capacity;
}

InventoryComponent::~InventoryComponent()
{
	for (std::vector<Entity*>::iterator it = storage.begin(); it != storage.end(); it++)
	{
		delete* it;
	}
}

int InventoryComponent::getStorageCapacity() { return capacity; }

void InventoryComponent::setStorageCapacity(int val)
{
	if (val < 0)
	{
		val = 0;
	}
	capacity = val;
}

void InventoryComponent::adjustStorageCapacity(int val)
{
	capacity += val;
	if (capacity < 0)
	{
		capacity = 0;
	}
}

std::vector<Entity*> InventoryComponent::getStorage() { return storage; }

void InventoryComponent::addToStorage(Entity* entity) { storage.push_back(entity); }

void InventoryComponent::removeFromStorage(Entity* entity) 
{ 
	for (std::vector<Entity*>::iterator it = storage.begin(); it != storage.end(); it++)
	{
		Entity* entityInStorage = *it;
		if (entity == entityInStorage)
		{
			storage.erase(it);
			return;
		}
	}
}

Entity* InventoryComponent::getItemAtLocation(int location)
{
	int itemPos = location - 97;
	if (storage.size() > 0 && itemPos < storage.size())
		return storage[itemPos];
	else return NULL;
}

void InventoryComponent::clearStorage() { storage.clear(); }

int InventoryComponent::getCurrentStorageSize() { return (int)storage.size(); }