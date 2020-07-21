#ifndef AI_H
#define AI_H

#include <iostream>
#include <string>

using namespace std;

class AI
{

private:

	string name;
	string description;
	bool money;
	

public:

	AI();
	AI(string n, string d, bool m);
	bool MoneyCheck(bool hasMoney);
	string GetName();
	string GetDescription();
	bool HaveMoney();
	
};

#endif // !AI_H

