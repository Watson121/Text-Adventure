#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>

using namespace std;

class Object
{
private:

	string name;
	string description;
	bool doorOpen;
	int codeSafe;

public:
	
	Object();
	Object(string n, string d);
	Object(string n, string d, bool open);
	Object(string n, string d, int code);
	void KeyCheck(bool hasKey);
	bool IsDoorOpen();
	bool CodeCheck(int code);
	void HasGloves(bool gloves);
	string getName();
	string getDescription();
	

};
#endif

