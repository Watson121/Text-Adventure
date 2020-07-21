#include "Adventure.h"

enum concol // enumeration type
{
	black = 0, dark_blue = 1, dark_green = 2,
	dark_aqua, dark_cyan = 3,
	dark_red = 4,
	dark_purple = 5, dark_pink = 5, dark_magenta = 5,
	dark_yellow = 6,
	dark_white = 7,
	gray = 8,
	blue = 9,
	green = 10,
	aqua = 11, cyan = 11,
	red = 12,
	purple = 13, pink = 13, magenta = 13,
	yellow = 14,
	white = 15
};

Adventure::Adventure() {
	string playerName;						//Stores the player name
	nextRoom = new AdventureRoom();			//This is inatlized so it can be used later, to store the next room that the player is travelling to.
	
	cout << "Please, enter in your name" << endl;
	getline(cin, playerName);

	/*The code below opens the playerFile.txt. After this is done, 
	it is sent to the Inatalize Player function where the file is read
	line by line and the contents of file are added to the Player.
	*/

	playerFile.open("playerFile.txt");
	Adventure::InatalizePlayer(playerFile);
	roomNum = 1;

	/*Similar to the code above, but this instead loads all of the
	Adventure Rooms information into the game. This is done the same way as before
	by reading the contents of the text line by line.*/

	roomFile.open("Rooms.txt");
	Adventure::CreateRoom(roomFile);
	Adventure::WelcomeText(playerName);

	Adventure::GetUserInput();

	gameEnded = false;
}

void Adventure::WelcomeText(string name) {

	//This just displays the Welcome Text, which is displayed when the player first starts the game.

	cout << "-----------------------------------------------------WELCOME------------------------------------------------------" << endl;
	cout << "\n\nHi, " + name + " welcome to the game. The aim of the game is to escape the trapped basement that you're in. To play this game, you type in commands into the keyboard. If you want help, just type HELP into the keyboard. \n" << endl;
}


void Adventure::InatalizePlayer(ifstream &pf) {

	std::vector< Object > startInventroy;		//Starting inventory for the player

	if (playerFile.is_open()) {
		int lineNum = 1;
		string line, name, description;

		while (getline(playerFile, line)) {
			if (lineNum == 1) {
				name = line;
				lineNum++;
			}
			else if (lineNum == 2) {
				description = line;
				lineNum = 1;
				Object *o = new Object(name, description);
				startInventroy.push_back(*o);
			}
		}
	
		playerFile.close();
	}

	player = new Player(startInventroy, 0, 0);	//Creates the player, and it sends the starting inventory so the user can access it properly.

}

void Adventure::CreateRoom(ifstream &rf){
	
	std::vector<Object> roomObjects;										//Stores the objects in the currentRoom
	std::vector<AI> aiObjects;
	string roomName, roomDescription, objectName, objectDescription;		//Gets the main parameters of the room
	bool roomVisited = true;												//Stores if the room has been visited or not
	bool north, south, east, west, hasAI;									//Stores the booleans read from file
	int roomNum, roomNum1, roomNum2, roomNum3, roomNum4;					//Stores the ints to be read from file
	
	int lineNum = 1;
	string line, title;
	bool doorOpen;

	if (roomFile.is_open())
	{
		while (getline(roomFile, line)) {
		if (lineNum == 1) {
			title = line;
			lineNum++;
		}
		else if (title == "ROOM:") {
			if (lineNum == 2) {
				roomNum = std::stoi(line, 0);
				lineNum++;
			}
			else if (lineNum == 3) {
				roomName = line;
				lineNum++;
			}
			else if (lineNum == 4) {
				roomDescription = line;
				lineNum++;
			}
			else if (lineNum == 5) {
				int numCheck = std::stoi(line, 0);
				if (numCheck == 0) {
					roomVisited = false;
				}
				else if (numCheck == 1) {
					roomVisited = true;
				}
				lineNum = 1;
			}
		}
		else if (title == "OBJECTS:") {
			if (lineNum == 2) {
				if (line != "MOTIONTABLE:") {
					objectName = line;
					lineNum++;
				}
				else if (line == "MOTIONTABLE:") {
					title = line;
					lineNum = 2;
				}
			}
			else if (lineNum == 3) {
				objectDescription = line;
				if (objectName == "DOOR") {
					Object *o = new Object(objectName, objectDescription, false);
					roomObjects.push_back(*o);	
					hasAI = false;
				}
				else if (objectName == "SAFE") {
					Object *o = new Object(objectName, objectDescription, 0451);
					roomObjects.push_back(*o);
					hasAI = false;
				}
				else if (objectName == "BATTERY") {
					Object *o = new Object(objectName, objectDescription, false);
					roomObjects.push_back(*o);
					hasAI = false;
				}
				else if (objectName == "MAN") {
					AI *ai = new AI(objectName, objectDescription, false);
					aiObjects.push_back(*ai);
					hasAI = true;
				}
				else if (objectName != "DOOR") {
					if (roomName != "Room Five") {
						Object *o = new Object(objectName, objectDescription);
						roomObjects.push_back(*o);
						hasAI = false;
					}
					else if (roomName == "Room Five") {
						Object *o = new Object(objectName, objectDescription);
						roomObjects.push_back(*o);
					}
				}
				lineNum = 2;
			}
		}
		else if ("MOTIONTABLE:") {	
			if (lineNum == 2) {			//UP
				int num = std::stoi(line.substr(0,1), 0);
				roomNum1 = std::stoi(line.substr(2, 1), 0);
				if (num == 1) {
					north = true;
				}
				else if (num == 0) {
					north = false;
				}
				lineNum++;
			}
			else if (lineNum == 3) {	//DOWN
				int num = std::stoi(line.substr(0, 1), 0);
				roomNum2 = std::stoi(line.substr(2, 1), 0);

				if (num == 1) {
					south = true;
				}
				else if (num == 0) {
					south = false;
				}
				lineNum++;
			}
			else if (lineNum == 4) {	//LEFT
				int num = std::stoi(line.substr(0, 1), 0);
				roomNum3 = std::stoi(line.substr(2, 1), 0);

				if (num == 1) {
					west = true;
				}
				else if (num == 0) {
					west = false;
				}
				lineNum++;
			}
			else if (lineNum == 5) {	//RIGHT
				int num = std::stoi(line.substr(0, 1), 0);
				roomNum4 = std::stoi(line.substr(2, 1), 0);

				if (num == 1) {
					east = true;
				}
				else if (num == 0) {
					east = false;
				}

				MotionTable *m = new MotionTable(north, south, west, east, roomNum1, roomNum2, roomNum3, roomNum4);
				motionTable = m;
				lineNum = 1;

				if (hasAI == false) {
					currentRoom = new AdventureRoom(roomNum, roomName, roomDescription, roomVisited, roomObjects, motionTable);
				}
				else if (hasAI == true) {
					currentRoom = new AdventureRoom(roomNum, roomName, roomDescription, roomVisited, roomObjects, motionTable, aiObjects);
				}
				rooms.push_back(*currentRoom);
				roomObjects.clear();
			}
		}
	}
	roomFile.close();
}

	
}

void Adventure::CurrentRoom()
{
	/*This fucntion gets the current room, which the player is currently loaded into*/

	for (size_t i = 0; i < rooms.size(); ++i) {
		if (rooms[i].HasRoomBeenVisited() == true) {
			*currentRoom = rooms[i];
		}
	}
}

void Adventure::GetUserInput() {

	/*This whole function asks the user to input data, and it also saves what the user has typed in and sends it to the UseInput function.*/

	*currentRoom = rooms[0];
	while (userInput != commandWords[0]) {
		if (gameEnded == false) {
			cout << "\n" + currentRoom->GetRoomDesciption();
		}
		cout << "\n\nEnter in an input: \n";
		getline(cin, userInput);
		player->inscreaseScoreAndSteps();
		system("cls");
		transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
		Adventure::UseInput(userInput);
	}
}

void Adventure::UseInput(string input) {

	/*This function is reponsible, for taking the User Input
	and depending on what the user has typed it will react approiatly.*/

	std::stringstream orignalString(input);
	std::string word;
	std::string cmdWord;					//This is used to save command word which the user has typed out on the keyboard
	std::string actionWord;					//This is used to save the name of an object.

	vector<string> words;

	char space = ' ';

	


	while (std::getline(orignalString, word, space)) {

		/*The first lot of if statements check if any of the words in
		the sentence that the user has written contain any action words, 
		that the text adventure uses to complete actions in the game*/

		if (word == commandWords[0]) {			//QUIT - This command quits the game when it is found in a sentence.
			cmdWord = commandWords[0];
		}
		else if (word == commandWords[1]) {		//HELP - Opens up the HELP menu for the player, if they are stuck and want to know what are command words are.
			Adventure::Help();
		}
		else if (word == commandWords[2]) {		//LOOK - Allows the user to look closer at objects, rooms and other items in game.
			cmdWord = commandWords[2];
		}
		else if (word == commandWords[3]) {		//INVENTORY - Opens up the inventory of the player.
			player->OpenInventory();
		}
		else if (word == commandWords[4]) {		//TAKE - This allows the user to pick up objects within the environment
			cmdWord = commandWords[4];
		}
		else if (word == commandWords[5]) {		//OPEN - This allows the user to open up doors and objects.
			cmdWord = commandWords[5];
		}
		else if (word == commandWords[6]) {		//DROP - This allows the user to drop items from their inventory, when it is open
			cmdWord = commandWords[6];
		}
		else if (word == commandWords[7]) {		//MOVE - Allows the user to move around levels
			cmdWord = commandWords[7];
		}
		else if (word == commandWords[8]) {		//ENTER - Allows the user to enter in codes into SAFES
			cmdWord = commandWords[8];
		}
		else if (word == commandWords[9]) {		//TALK - Allows the user to talk to NPCs in the world.
			cmdWord = commandWords[9];
		}
	
		/*The code below takes the command words that the user has entered, and reacts to them*/


		if (player->GetOpen() == true) {
			if (player->GetObject(word) == true) {
				actionWord = word;
				if (cmdWord == commandWords[2]) {
					player->LookAtObject(actionWord);
				}
				else if (cmdWord == commandWords[6]) {
					currentRoom->AddObjectToRoom(player->RemoveObject(actionWord));
				}
			}
		}

		if (cmdWord == commandWords[2]) {
			if (word == "ROOM") {
				cout << currentRoom->GetRoomDesciption() + "\n" << endl;
			}
		}

		if (cmdWord == commandWords[5]) {
			if (currentRoom->GetRoomName() == "Room One") {
				if (word == "DOOR") {
					playerHasKey = player->GetObject("KEY");
					currentRoom->OpenDoor(playerHasKey);
					if (playerHasKey == true) {
						player->RemoveObject("KEY");
					}
					else if (playerHasKey == false) {
						cout << "Door cannot be opened! You don't have the key \n";
					}
				}
			}
			else if (currentRoom->GetRoomName() == "Room Four") {
					if (word == "DOOR") {
						playerHasKey = player->GetObject("ESCAPE KEY");
						currentRoom->OpenDoor(playerHasKey);
						if (playerHasKey == true) {
							player->RemoveObject("ESCAPE KEY");
						}
						else if (playerHasKey == false) {
							cout << "Door cannot be opened! You don't have the key \n";
						}
					}
			}
			else if (currentRoom->GetRoomName() == "Room Two") {
				if (word == "DOOR") {
					playerHasKey = player->GetObject("BATTERY");
					currentRoom->OpenDoor(playerHasKey);
					if (playerHasKey == true) {
						cout << "The DOOR is now open! Electricity is no longer connected to it! \n";
					}
					else if (playerHasKey == false) {
						cout << "The DOOR is still electrified! If I touch it now, it could kill me! \n";
					}
				}
			}
		}


		if (cmdWord == commandWords[7]) {
			if (currentRoom->moveBetweenRooms(word) == true) {
				if (word == "UP") {
					if (currentRoom->GetRoomName() == "Room Four") {
						Adventure::WinningScreen();
					}
					else {
						*nextRoom = rooms[currentRoom->ChangeRoomNumber("UP")];
						nextRoom->EnterRoom();
						currentRoom = nextRoom;
						cout << "You have moved UP into the next room \n";
					}
				}
				else if (word == "DOWN") {
					*nextRoom = rooms[currentRoom->ChangeRoomNumber("DOWN")];
					nextRoom->EnterRoom();
					currentRoom = nextRoom;
					cout << "You have moved DOWN into the next room \n";
				}
				else if (word == "LEFT") {
					*nextRoom = rooms[currentRoom->ChangeRoomNumber("LEFT")];
					nextRoom->EnterRoom();
					currentRoom = nextRoom;
					cout << "You have moved LEFT into the next room \n";
				}
				else if (word == "RIGHT") {
					if (currentRoom->GetRoomName() == "Room Four") {
						cout << "You try to go in that direction, but a gust of wind pushes you back \n";
					}
					else {
						*nextRoom = rooms[currentRoom->ChangeRoomNumber("RIGHT")];
						nextRoom->EnterRoom();
						currentRoom = nextRoom;
						cout << "You have moved RIGHT into the next room \n";
					}
				}
			}
			else if (currentRoom->moveBetweenRooms(word) == false) {
				cout << "You cannot move in that direction \n";
			}
		}

		if (cmdWord == commandWords[8]) {
			if (currentRoom->GetRoomName() == "Room Three") {
				if (word == "0451") {
					int code = std::stoi(word, 0);
					cout << "The code worked! The safe is now open! \n";
					if (currentRoom->OpenSafe(code) == true) {
						Object o = currentRoom->TakeObjectFromRoom("MONEY");
						player->AddObject(o);
						currentRoom->DeleteObjectFromRoom("MONEY");
						break;
					}
					else if (word != "0451" || word != commandWords[8]) {
						cout << "That code didn't work! Maybe I should try another code \n";
					}
				}
			}
		}

		if (cmdWord == commandWords[9]) {
			if (currentRoom->GetRoomName() == "Room Five") {
				if (word == "MAN") {
					playerHasKey = player->GetObject("MONEY");
					currentRoom->GiveMoney(playerHasMoney);
					if (playerHasKey == true) {
						Object o = currentRoom->TakeObjectFromRoom("ESCAPE KEY");
						player->AddObject(o);
						currentRoom->DeleteObjectFromRoom("ESCAPE KEY");
						player->RemoveObject("MONEY");
						cout << "You give the man money, and in return he hands you a key. You can now finally escape \n";
						break;
					}
				}
			}
		}


		if (currentRoom->GetObjectInRoom(word) == true) {
			actionWord = word;
			if (cmdWord == commandWords[2]) {
				currentRoom->LookAtObject(actionWord);
			}
			else if (cmdWord == commandWords[4]) {
				if (actionWord == "BATTERY") {
					if (currentRoom->GetRoomName() == "Room Three") {
						if (player->GetObject("GLOVES") == true) {
							Object o = currentRoom->TakeObjectFromRoom(actionWord);
							player->AddObject(o);
							currentRoom->DeleteObjectFromRoom(actionWord);
						}
						else if (player->GetObject("GLOVES") == false) {
							cout << "I don't have any GLOVES! It's too dangerous too touch the battery! If I do, I could get electrocuted! \n";
						}
					}
				}
				else if (actionWord == "DOOR") {
					cout << "You can't pick up a DOOR \n";
				}
				else {
					Object o = currentRoom->TakeObjectFromRoom(actionWord);
					player->AddObject(o);
					currentRoom->DeleteObjectFromRoom(actionWord);
				}
			}
		}
	}
}

void Adventure::Help() {

	/*This function, opens up the help menu*/

	cout << "\nHELP:" << endl;
	cout << "The keyboard is used to complete actions within the game." << endl;
	cout << "\nIMPORTANT WORDS:" << endl;
	cout << "QUIT - Quits the game" << endl;
	cout << "HELP - Opens up the help menu" << endl;
	cout << "LOOK - Allows the player to look at an object - e.g. LOOK at Note" << endl;
	cout << "INVENTORY - Opens up the Inventory" << endl;
	cout << "TAKE - Allows the player to take an object - e.g. TAKE note" << endl;
	cout << "OPEN - Allows the player to open an object - e.g. OPEN the Safe" << endl;
	cout << "DROP - Allows the player to drop an obejct - e.g. DROP the note" << endl;
	cout << "\n";
}

void Adventure::WinningScreen() {

	//This function opens up the Winning Screen.
	gameEnded = true; 
	cout << "WELL DONE!!!! YOU ESCAPED!!!!! \n";
	cout << "You took these many steps to complete the game - ";
	cout << player->GetSteps();
	cout << "\nHere is your final score - ";
	cout << player->GetScore();
	cout << "\nQuit the game by pressing typing QUIT into the window below\n";
}








