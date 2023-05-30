#pragma once
#include<string>
#include"Header.h"
using namespace std;

class Player
{
private:
	string Name;
	Color C;

public:
	Player(string name, Color colr);
	string get_name();
	Color get_Color();
};


