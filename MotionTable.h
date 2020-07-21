#ifndef MOTIONTABLE_H
#define MOTIONTABLE_H

#include <iostream>

using namespace std;

class MotionTable
{

private:

	bool moveUp, moveDown, moveLeft, moveRight;
	int roomNum1, roomNum2, roomNum3, roomNum4;

public:
	
	//Constructors
	MotionTable();
	MotionTable(bool up, bool down, bool left, bool right, int rm1, int rm2, int rm3, int rm4);

	//Changing the values of the booleans
	void ChangeUp();
	void ChangeDown();
	void ChangeLeft();
	void ChangeRight();

	//Returning the values of the booleans
	bool MoveUp();
	bool MoveDown();
	bool MoveLeft();
	bool MoveRight();

	//Returning the values of the integers
	size_t RoomNum1();
	size_t RoomNum2();
	size_t RoomNum3();
	size_t RoomNum4();

};

#endif // !MOTIONTABLE_H

