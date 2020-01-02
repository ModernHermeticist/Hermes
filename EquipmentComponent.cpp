#include "main.h"

EquipmentComponent::EquipmentComponent()
{

}
EquipmentComponent::~EquipmentComponent()
{	
	/*
	if (leftHand != NULL) delete leftHand;
	if (rightHand != NULL) delete rightHand;
	if (chest != NULL) delete chest;
	if (legs != NULL) delete legs;
	if (feet != NULL) delete feet;
	if (hands != NULL) delete hands;
	if (shoulders != NULL) delete shoulders;
	if (back != NULL) delete back;
	if (head != NULL) delete head;
	if (waist != NULL) delete waist;
	if (leftRing != NULL) delete leftRing;
	if (rightRing != NULL) delete rightRing;
	if (leftEarring != NULL) delete leftEarring;
	if (rightEarring != NULL) delete rightEarring;
	if (neck != NULL) delete neck;
	*/
}

void EquipmentComponent::setLeftHand(Entity* _leftHand) { leftHand = _leftHand; }
void EquipmentComponent::setRightHand(Entity* _rightHand) { rightHand = _rightHand; }
void EquipmentComponent::setChest(Entity* _chest) { chest = _chest; }
void EquipmentComponent::setLegs(Entity* _legs) { legs = _legs; }
void EquipmentComponent::setFeet(Entity* _feet) { feet = _feet; }
void EquipmentComponent::setHands(Entity* _hands) { hands = _hands; }
void EquipmentComponent::setShoulders(Entity* _shoulders) { shoulders = _shoulders; }
void EquipmentComponent::setBack(Entity* _back) { back = _back; }
void EquipmentComponent::setHead(Entity* _head) { head = _head; }
void EquipmentComponent::setWaist(Entity* _waist) { waist = _waist; }
void EquipmentComponent::setLeftRing(Entity* _leftRing) { leftRing = _leftRing; }
void EquipmentComponent::setRightRing(Entity* _rightRing) { rightRing = _rightRing; }
void EquipmentComponent::setLeftEarring(Entity* _leftEarring) { leftEarring = _leftEarring; }
void EquipmentComponent::setRightEarring(Entity* _rightEarring) { rightEarring = _rightEarring; }
void EquipmentComponent::setNeck(Entity* _neck) { neck = _neck; }

Entity* EquipmentComponent::getLeftHand() { return leftHand; }
Entity* EquipmentComponent::getRightHand() { return rightHand; }
Entity* EquipmentComponent::getChest() { return chest; }
Entity* EquipmentComponent::getLegs() { return legs; }
Entity* EquipmentComponent::getFeet() { return feet; }
Entity* EquipmentComponent::getHands() { return hands; }
Entity* EquipmentComponent::getShoulders() { return shoulders; }
Entity* EquipmentComponent::getBack() { return back; }
Entity* EquipmentComponent::getHead() { return head; }
Entity* EquipmentComponent::getWaist() { return waist; }
Entity* EquipmentComponent::getLeftRing() { return leftRing; }
Entity* EquipmentComponent::getRightRing() { return rightRing; }
Entity* EquipmentComponent::getLeftEarring() { return leftEarring; }
Entity* EquipmentComponent::getRightEarring() { return rightEarring; }
Entity* EquipmentComponent::getNeck() { return neck; }

Entity* EquipmentComponent::getItemAtSlot(EQUIPMENTSLOT slot)
{
	Entity* entity;
	switch (slot)
	{
	case EQUIPMENTSLOT::leftHand: entity = leftHand; break;
	case EQUIPMENTSLOT::rightHand: entity = rightHand; break;
	case EQUIPMENTSLOT::chest: entity = chest; break;
	case EQUIPMENTSLOT::legs: entity = legs; break;
	case EQUIPMENTSLOT::feet: entity = feet; break;
	case EQUIPMENTSLOT::hands: entity = hands; break;
	case EQUIPMENTSLOT::shoulders: entity = shoulders; break;
	case EQUIPMENTSLOT::back: entity = back; break;
	case EQUIPMENTSLOT::head: entity = head; break;
	case EQUIPMENTSLOT::waist: entity = waist; break;
	case EQUIPMENTSLOT::leftRing: entity = leftRing; break;
	case EQUIPMENTSLOT::rightRing: entity = rightRing; break;
	case EQUIPMENTSLOT::leftEarring: entity = leftEarring; break;
	case EQUIPMENTSLOT::rightEarring: entity = rightEarring; break;
	case EQUIPMENTSLOT::neck: entity = neck; break;
	default: entity = NULL; break;
	}
	return entity;
}

std::vector<Entity*> EquipmentComponent::getAllItemSlots()
{
	std::vector<Entity*> allItemSlots;
	allItemSlots.push_back(head);
	allItemSlots.push_back(chest);
	allItemSlots.push_back(neck);
	allItemSlots.push_back(shoulders);
	allItemSlots.push_back(hands);
	allItemSlots.push_back(waist);
	allItemSlots.push_back(legs);
	allItemSlots.push_back(feet);
	allItemSlots.push_back(leftRing);
	allItemSlots.push_back(rightRing);
	allItemSlots.push_back(leftEarring);
	allItemSlots.push_back(rightEarring);
	allItemSlots.push_back(leftHand);
	allItemSlots.push_back(rightHand);
	return allItemSlots;
}

void EquipmentComponent::setItemAtSlot(Entity* item, EQUIPMENTSLOT slot)
{
	switch (slot)
	{
	case EQUIPMENTSLOT::leftHand: leftHand = item; break;
	case EQUIPMENTSLOT::rightHand: rightHand = item; break;
	case EQUIPMENTSLOT::chest: chest = item; break;
	case EQUIPMENTSLOT::legs: legs = item; break;
	case EQUIPMENTSLOT::feet: feet = item; break;
	case EQUIPMENTSLOT::hands: hands = item; break;
	case EQUIPMENTSLOT::shoulders: shoulders = item; break;
	case EQUIPMENTSLOT::back: back = item; break;
	case EQUIPMENTSLOT::head: head = item; break;
	case EQUIPMENTSLOT::waist: waist = item; break;
	case EQUIPMENTSLOT::leftRing: leftRing = item; break;
	case EQUIPMENTSLOT::rightRing: rightRing = item; break;
	case EQUIPMENTSLOT::leftEarring: leftEarring = item; break;
	case EQUIPMENTSLOT::rightEarring: rightEarring = item; break;
	case EQUIPMENTSLOT::neck: neck = item; break;
	default: break;
	}
}

void EquipmentComponent::removeItemAtSlot(EQUIPMENTSLOT slot)
{
	switch (slot)
	{
		case EQUIPMENTSLOT::leftHand: leftHand = NULL; break;
		case EQUIPMENTSLOT::rightHand: rightHand = NULL; break;
		case EQUIPMENTSLOT::chest: chest = NULL; break;
		case EQUIPMENTSLOT::legs: legs = NULL; break;
		case EQUIPMENTSLOT::feet: feet = NULL; break;
		case EQUIPMENTSLOT::hands: hands = NULL; break;
		case EQUIPMENTSLOT::shoulders: shoulders = NULL; break;
		case EQUIPMENTSLOT::back: back = NULL; break;
		case EQUIPMENTSLOT::head: head = NULL; break;
		case EQUIPMENTSLOT::waist: waist = NULL; break;
		case EQUIPMENTSLOT::leftRing: leftRing = NULL; break;
		case EQUIPMENTSLOT::rightRing: rightRing = NULL; break;
		case EQUIPMENTSLOT::leftEarring: leftEarring = NULL; break;
		case EQUIPMENTSLOT::rightEarring: rightEarring = NULL; break;
		case EQUIPMENTSLOT::neck: neck = NULL; break;
	default: break;
	}
}