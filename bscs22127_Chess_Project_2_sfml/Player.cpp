#include "Player.h"


Player::Player(string name, Color colr)
{
	this->Name = name;
	this->C = colr;
}

string Player::get_name()
{
	return Name;
}
Color Player::get_Color()
{
	return C;
}