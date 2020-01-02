#ifndef EQUIPMENTCOMPONENT_H
#define EQUIPMENTCOMPONENT_H

class Entity;

class EquipmentComponent
{
public:
	enum class EQUIPMENTSLOT {leftHand, rightHand, chest, legs, feet, hands, shoulders, 
		back, head, waist, leftRing, rightRing, leftEarring, rightEarring, neck, none};

	EquipmentComponent();
	~EquipmentComponent();

	void setLeftHand(Entity* _leftHand);
	void setRightHand(Entity* _rightHand);
	void setChest(Entity* _chest);
	void setLegs(Entity* _legs);
	void setFeet(Entity* _feet);
	void setHands(Entity* _hands);
	void setShoulders(Entity* _shoulders);
	void setBack(Entity* _back);
	void setHead(Entity* _head);
	void setWaist(Entity* _waist);
	void setLeftRing(Entity* _leftRing);
	void setRightRing(Entity* _rightRing);
	void setLeftEarring(Entity* _leftEarring);
	void setRightEarring(Entity* _rightEarring);
	void setNeck(Entity* _Neck);

	Entity* getLeftHand();
	Entity* getRightHand();
	Entity* getChest();
	Entity* getLegs();
	Entity* getFeet();
	Entity* getHands();
	Entity* getShoulders();
	Entity* getBack();
	Entity* getHead();
	Entity* getWaist();
	Entity* getLeftRing();
	Entity* getRightRing();
	Entity* getLeftEarring();
	Entity* getRightEarring();
	Entity* getNeck();

	std::vector<Entity*> getAllItemSlots();
	Entity* getItemAtSlot(EQUIPMENTSLOT slot);
	void setItemAtSlot(Entity* item, EQUIPMENTSLOT slot);
	void removeItemAtSlot(EQUIPMENTSLOT slot);

private:
	Entity* leftHand = NULL;
	Entity* rightHand = NULL;
	Entity* chest = NULL;
	Entity* legs = NULL;
	Entity* feet = NULL;
	Entity* hands = NULL;
	Entity* shoulders = NULL;
	Entity* back = NULL;
	Entity* head = NULL;
	Entity* waist = NULL;
	Entity* leftRing = NULL;
	Entity* rightRing = NULL;
	Entity* leftEarring = NULL;
	Entity* rightEarring = NULL;
	Entity* neck = NULL;


};

#endif
