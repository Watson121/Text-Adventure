#include "AdventureRoom.h"

AdventureRoom::AdventureRoom() {
	//Deafult Constructor for Adventure Room
}

AdventureRoom::AdventureRoom(int rn, string rName, string rDesc, bool rV, vector <Object> o, MotionTable *m) {

	//Consturctor Adventure Rooms that do not contain any AI

	roomNum = rn;
	roomName = rName;
	roomDescription = rDesc;
	roomVisited = rV;
	objectsInRoom = o;
	directions = m; 
}

AdventureRoom::AdventureRoom(int rn, string rName, string rDesc, bool rV, vector <Object> o, MotionTable *m, vector <AI> a) {
	//Constuctor for Adventure Rooms that do contain AI

	roomNum = rn;
	roomName = rName;
	roomDescription = rDesc;
	roomVisited = rV;
	objectsInRoom = o;
	directions = m;
	ai = a;
}

int AdventureRoom::GetRoomNum() {
	//This function returns the Current Room Number
	return roomNum;
}

string AdventureRoom::GetRoomName() {
	//This function returns the Current Room Name
	return roomName;
}

string AdventureRoom::GetRoomDesciption() {
	//This function returns the Current Room Description
	return roomDescription;
}

bool AdventureRoom::GetObjectInRoom(string name) {

	//This function searches for an object that the user is looking for, and it is found then it returns true and if not then false

	for (size_t i = 0; i < objectsInRoom.size(); ++i) {
		if (name == objectsInRoom[i].getName()) {
			if (name != "Door") {
				return true;
			}
			else if (name == "Door") {
				cout << "You can't pick up a DOOR" << endl;
			}
		}
	}
}

void AdventureRoom::LookAtObject(string name) {

	//This function finds an object, and it is found then it will tell the user more about the object within the current room that the player is in

	if (name == "MAN") {
		cout << ai[0].GetDescription() << "\n";
	}
	else {
		for (size_t i = 0; i < objectsInRoom.size(); ++i) {
			if (name == objectsInRoom[i].getName()) {
				cout << objectsInRoom[i].getDescription() << "\n";
				break;
			}
		}
	}
}

Object AdventureRoom::TakeObjectFromRoom(string name) {

	//This function takes an object from a room, and it adds it in to the player inventory

	for (size_t i = 0; i < objectsInRoom.size(); ++i) {
		if (name == objectsInRoom[i].getName()) {
			cout << "Added Object" << endl;
			return objectsInRoom[i];
			break;
		}
	}
}

void AdventureRoom::AddObjectToRoom(Object o) {

	//Adds objects to the room, mostly used for when the player drops an item within the current room.

	objectsInRoom.push_back(o);
	cout << "You have dropped the " + o.getName() + " in " + AdventureRoom::GetRoomName(); +"\n";
}


void AdventureRoom::DeleteObjectFromRoom(string name) {

	//Removes the object from the current room. Mostly used for when the player picks up an object within the room that they are currently in.

	for (size_t i = 0; i < objectsInRoom.size(); ++i) {
		if (name == objectsInRoom[i].getName()) {
			objectsInRoom.erase(objectsInRoom.begin() + i);
		}
	}
}

void AdventureRoom::LeaveRoom() {
	//When the player leaves the room, it tells the current Adventure Room that the user is currently not in there.
	roomVisited = false;
}

void AdventureRoom::EnterRoom() {
	//Tells that the user has just entered the room
	roomVisited = true;
}

void AdventureRoom::OpenDoor(bool hasKey) {
	//In rooms that have doors, that require keys. This function checks if the player has a key and if they do then open the door, and if not then leave the door locked

	objectsInRoom[0].KeyCheck(hasKey);

	if (objectsInRoom[0].IsDoorOpen() == true) {
		directions->ChangeUp();
	}
}

bool AdventureRoom::HasRoomBeenVisited() {
	//This function tells if the user is currently visiting the room or not.
	return roomVisited;
}

bool AdventureRoom::OpenSafe(int code) {
	//In rooms that have safes, this function checks if the user has implemented the right code or not. And if the code is correct, then open up the safe.
	if (objectsInRoom[1].CodeCheck(code) == true) {
		return true;
	}
}

bool AdventureRoom::GiveMoney(bool hasMoney) {	
	//In rooms that requries money to advance. This fucntion checks if the user has any money at all.
	if (ai[0].MoneyCheck(hasMoney) == true) {
		return true; 
	}
}

bool AdventureRoom::moveBetweenRooms(string direction) {
	//This function is mostly used for checking if the player can move between rooms by checking booleans of the Current Room's Motion Table.

	if (direction == "UP") {
		return directions->MoveUp();
	}
	else if (direction == "DOWN") {
		return directions->MoveDown();
	}
	else if (direction == "LEFT") {
		return directions->MoveLeft();
	}
	else if (direction == "RIGHT") {
		return directions->MoveRight();
	}
}

size_t AdventureRoom::ChangeRoomNumber(string direction) {
	//This function changes the room that the player is currently in, and this function is only used when the function above returns as true.

	if (direction == "UP") {
		return directions->RoomNum1();
	}
	else if (direction == "DOWN") {
		return directions->RoomNum2();
	}
	else if (direction == "LEFT") {
		return directions->RoomNum3();
	}
	else if (direction == "RIGHT") {
		return directions->RoomNum4();
	}
}

