#pragma once
#include"Peice.h"

class King : public Peice
{
private:
	static void King_Sym(int ri, int ci, char sym, int col);
	char ch1{};
public:
	void set_vector_posi(sf::Vector2f& v)override
	{
		set_posi(v);
	}
	char get_sym()override;
	King(Position P_p, Color clr, Board* B, char sym = char(-37));
	void Draw_Peice()override;
	bool Peice_legal(Board B, Position Sc, Position Dc)override;

	bool bishopleg(Board B, Position Sc, Position Dc);
	bool Rockleg(Board B, Position Sc, Position Dc);

	void print(sf::RenderWindow& window, int column, int row)override
	{
			print_1(window);
	}
};

