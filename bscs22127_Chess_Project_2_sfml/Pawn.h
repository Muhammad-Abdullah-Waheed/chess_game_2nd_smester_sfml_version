#pragma once

#include"Peice.h"


class Pawn : public Peice
{
	bool is_first_move{ false };
	Position Fix{};
public:
	void set_vector_posi(sf::Vector2f& v)override
	{
		set_posi(v);
	}
	Pawn() = default;
	Pawn(Position P_p, Color clr, Board* B, char sym = char(-37));
	bool Peice_legal(Board B, Position Sc, Position Dc)override;
	bool valuechanged(Position P);
	char get_sym() override {
		if (P_color == WHITE)
			return 'P';
		else if (P_color == BLACK)
			return 'p';
	}
	bool Pawndown(Board B, Position Sc, Position Dc, int a);
	bool Pawnup(Board B, Position Sc, Position Dc, int a);

	void print(sf::RenderWindow& window, int column, int row)override
	{
		print_1(window);
	}
};
