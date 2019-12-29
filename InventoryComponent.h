#ifndef INVENTORYCOMPONENT_H
#define INVENTORYCOMPONENT_H

class Entity;

class InventoryComponent
{
public:
	InventoryComponent(int _capacity);
	~InventoryComponent();

	int getStorageCapacity();
	void setStorageCapacity(int val);
	void adjustStorageCapacity(int val);

	std::vector<Entity*> getStorage();

	void addToStorage(Entity* entity);
	void removeFromStorage(Entity* entity);

	Entity* getItemAtLocation(int location);

	void clearStorage();

	int getCurrentStorageSize();

private:
	std::vector<Entity*> storage;
	int capacity;

};

#endif