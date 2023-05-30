#pragma once
#include"Peice.h"

class Bishop : public Peice
{
private:
	static void Bishop_Sym(int ri, int ci, char sym, int col);
public:
	Bishop() = default;
	Bishop(Position P_p, Color clr, Board* B, char sym = char(-37));
	void Draw_Peice()override;
	bool Peice_legal(Board B, Position Sc, Position Dc)override;

	void print(sf::RenderWindow& window, int column, int row)override
	{
		print_1(window);
	}
	void set_vector_posi(sf::Vector2f& v)override
	{
		set_posi(v);
	}
};
