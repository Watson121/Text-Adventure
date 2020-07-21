#include "Object.h"

Object::Object() {
	//Basis constructor for the Object
}

Object::Object(string n, string d) {
	//One of the main constructors for the objects withn the game world
	name = n;
	description = d;
}

Object::Object(string n, string d, bool open) {
	//Door Object constructor
	name = n;
	description = d;
	doorOpen = open;
}

Object::Object(string n, string d, int code) {
	//Safe Object constructor
	name = n;
	description = n;
	codeSafe = code;
}

void Object::KeyCheck(bool hasKey) {
	//This function checks if the player has the key to open the door or not
	if (hasKey == true) {
		cout << "DOOR is now open! The KEY has been used. \n";
		doorOpen = true;
	}
}

bool Object::CodeCheck(int code) {
	//Checks if the user has entered in the right code or not
	if (code = codeSafe) {
		return true;
	}
}


bool Object::IsDoorOpen() {
	//Checks if the door is open or not.
	return doorOpen;
}


string Object::getName() {
	//Returns the name of the object
	return name;
}

string Object::getDescription() {
	//Returns the the description of the object
	return description;
}



