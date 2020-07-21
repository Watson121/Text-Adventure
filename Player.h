#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include "Object.h"

using namespace std;

class Player
{

private:

	std::vector< Object > inventroy;
	int score;
	int steps;
	bool open = false;

public:

	Player(vector<Object> o, int sc, int st);
	void OpenInventory();
	bool GetObject(string name);
	void LookAtObject(string name);
	void AddObject(Object o);
	Object RemoveObject(string objectName);
	bool GetOpen(); 
	void inscreaseScoreAndSteps();
	int GetScore();
	int GetSteps();

};

#endif // !PLAYER_H

