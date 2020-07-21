#include "MotionTable.h"

MotionTable::MotionTable() {
	//Basic constructor for the Motion Table
}


MotionTable::MotionTable(bool up, bool down, bool left, bool right, int rm1, int rm2, int rm3, int rm4) {
	//Main constructor for the Motion Table
	moveUp = up;		//Saves the boolean that allows the user to travel in a certain direction or not
	moveDown = down;	//Saves the boolean that allows the user to travel in a certain direction or not
	moveLeft = left;	//Saves the boolean that allows the user to travel in a certain direction or not
	moveRight = right;	//Saves the boolean that allows the user to travel in a certain direction or not
	roomNum1 = rm1;		//This saves the ID, that the user will travel to when they move up.
	roomNum2 = rm2;		//This saves the ID, that the user will travel to when they move down.
	roomNum3 = rm3;		//This saves the ID, that the user will travel to when they move left.
	roomNum4 = rm4;		//This saves the ID, that the user will travel to when they move right.
}

#pragma region SETS THE VALUES OF THE MOTION TABLE

void MotionTable::ChangeUp() {
	moveUp = true;
}

void MotionTable::ChangeDown() {
	moveDown = true;
}

void MotionTable::ChangeRight() {
	moveRight = true;
}

void MotionTable::ChangeLeft() {
	moveLeft = true;
}

#pragma endregion

#pragma region RETURNS BOOLEANS  

bool MotionTable::MoveUp() {
	return moveUp;
}

bool MotionTable::MoveDown() {
	return moveDown;
}

bool MotionTable::MoveLeft() {
	return moveLeft;
}

bool MotionTable::MoveRight() {
	return moveRight;
}

#pragma endregion

#pragma region RETURNS THE INT VALUES

size_t MotionTable::RoomNum1() {
	return roomNum1;
}

size_t MotionTable::RoomNum2() {
	return roomNum2;
}

size_t MotionTable::RoomNum3() {
	return roomNum3;
}

size_t MotionTable::RoomNum4() {
	return roomNum4;
}

#pragma endregion



