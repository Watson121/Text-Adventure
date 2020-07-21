#include "AI.h"

AI::AI() {
	//Defualt constructor for the AI
}

AI::AI(string n, string d, bool m) {
	//Main constructor for the AI
	name = n;
	description = d;
	money = m;
}

string AI::GetName() {
	//returns the name of the AI
	return name;
}

string AI::GetDescription() {
	//returns the description of the AI
	return description;
}

bool AI::HaveMoney() {
	//Checks if the AI has any money or not
	return money;
}

bool AI::MoneyCheck(bool hasMoney) {
	//This function allows the user to give the AI money or not. This only happens if the user has money contained in their invnetory.
	if (hasMoney == true) {
		cout << "You give the man money, and in return he hands you a key. You can now finally escape \n";
		money = true;
		return true;
	}
}





