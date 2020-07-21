#ifndef ADVENTURE_H
#define ADVENTURE_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <iterator>
#include <locale>
#include "Player.h"
#include "AdventureRoom.h"
#include "MotionTable.h"
#include "Object.h"

using namespace std; 

class Adventure
{

private:

	std::string commandWords[10] = {"QUIT", "HELP", "LOOK", "INVENTORY", "TAKE", "OPEN", "DROP", "MOVE", "ENTER", "TALK"};
	std::string userInput;
	int roomNum;

	//Files
	ifstream playerFile;
	ifstream roomFile;

	bool playerHasKey, playerHasMoney, gameEnded;

	Player *player;
	vector<AdventureRoom> rooms;
	MotionTable *motionTable;
	AdventureRoom *currentRoom;
	AdventureRoom *nextRoom;

public:
	
	Adventure();
	void WelcomeText(string name);
	void InatalizePlayer(ifstream &pf);
	void CreateRoom(ifstream &rf);
	void CurrentRoom();
	void GetUserInput();
	void UseInput(string input);
	void Help();
	void WinningScreen();

};

#endif // !ADVENTURE_H

