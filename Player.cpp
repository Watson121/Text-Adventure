#include "Player.h"

Player::Player(vector<Object> o, int sc, int st) {
	//Main constructor for the Player

	inventroy = o;
	score = sc;
	steps = st;
}

void Player::AddObject(Object o) {
	//When this function is called, it will add items to the player's inventory.
	inventroy.push_back(o);
}

Object Player::RemoveObject(string objectName) {
	//This fucntion when active, removes a given object from the player inventory.
	Object o;
	
	for (size_t i = 0; i < inventroy.size(); ++i) {
		if (objectName == inventroy[i].getName()) {
			o = inventroy[i];
			inventroy.erase(inventroy.begin()+i);
			return o;
		}
	}
}

bool Player::GetOpen() {
	return open;
}

int Player::GetScore() {
	//Gets the player score
	return score;
}

int Player::GetSteps() {
	//Gets the how many steps the player has taken
	return steps;
}

void Player::OpenInventory() {

	//This function opens up the player inventory, and displays it to the console.

	open = true;
	cout << "Your Inventory is now open \n" << endl;
	cout << "Your Inventory Contains " << endl;
	
	for (size_t i = 0; i < inventroy.size(); ++i) {
		cout << inventroy[i].getName();
		cout << "\n";
	}
}

bool Player::GetObject(string name) {
	//This function searches the player's inventory for a certain object

	for (size_t i = 0; i < inventroy.size(); ++i) {
		if (name == inventroy[i].getName()) {
			return true;
		}
	}
}

void Player::LookAtObject(string name) {
	//This function looks closers at given objects within the player inventory

	for (size_t i = 0; i < inventroy.size(); ++i) {
		if (name == inventroy[i].getName()) {
			cout << inventroy[i].getDescription() << "\n";
			break;
		}
		else if (name != inventroy[i].getName()) {
			cout << "What are you looking at!? There is nothing there! \n";
		}
	}
}

void Player::inscreaseScoreAndSteps() {
	score = score + 10;
	steps = steps + 1;
}



