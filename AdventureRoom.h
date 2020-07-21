#ifndef ADVENTUREROOM_H
#define ADVENTUREROOM_H



#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "MotionTable.h"
#include "Object.h"
#include "Player.h"
#include "AI.h"

using namespace std;

class AdventureRoom
{
private:

	int roomNum;
	string roomName;
	string roomDescription;
	vector <Object> objectsInRoom;
	bool roomVisited;
	MotionTable *directions;
	vector <AI> ai;

public:

	AdventureRoom();
	AdventureRoom(int rn, string rName, string rDesc, bool rV, vector <Object> o, MotionTable *m);
	AdventureRoom(int rn, string rName, string rDesc, bool rV, vector <Object> o, MotionTable *m, vector <AI> a);
	int GetRoomNum();
	
	string GetRoomName();
	string GetRoomDesciption();
	
	bool GetObjectInRoom(string name);
	void LookAtObject(string name);
	void DeleteObjectFromRoom(string name);
	void AddObjectToRoom(Object o);
	Object TakeObjectFromRoom(string name);
	
	void LeaveRoom();
	void EnterRoom();
	
	void OpenDoor(bool hasKey);
	bool OpenSafe(int code);
	bool GiveMoney(bool hasMoney); 

	bool HasRoomBeenVisited();
	bool moveBetweenRooms(string direction);

	size_t ChangeRoomNumber(string direction);

};

#endif // !ADEVENTUREROOM_H

