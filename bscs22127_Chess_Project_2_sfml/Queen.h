#pragma once
#include"Peice.h"

class Queen : public Peice
{
public:
	void set_vector_posi(sf::Vector2f& v)override
	{
		set_posi(v);
	}
	Queen(Position P_p, Color clr, Board* B, char sym = char(-37));
	bool Peice_legal(Board B, Position Sc, Position Dc)override;
	bool Rockleg(Board B, Position Sc, Position Dc);
	bool bishopleg(Board B, Position Sc, Position Dc);
	void print(sf::RenderWindow& window, int column, int row)override
	{
			print_1(window);
	}
};

