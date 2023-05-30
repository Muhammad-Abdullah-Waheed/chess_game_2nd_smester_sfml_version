#include"Peice.h"
#include"Chess.h"
#include "Rock.h"


Rock::Rock(Position P_p, Color clr, Board* B, char sym) :Peice(P_p, clr, B, sym)
{
	if (clr == BLACK)
		Sym2 = 'r';
	else if (clr == WHITE)
		Sym2 = 'R';
	if (P_color == WHITE)
		t.loadFromFile("Rook_1.png");
	else if (P_color == BLACK)
		t.loadFromFile("Rook_2.png");
	sp.setTexture(t);
	this->sp.setScale(0.07, 0.07);
}
bool Rock::Peice_legal(Board B, Position Sc, Position Dc)
{
	return ((Ishorizontal(Sc, Dc) && Ishorizontalpathclear(B, Sc, Dc)) ||
		(Isvertical(Sc, Dc) && Isverticalpathclear(B, Sc, Dc)));
}

void Rock::print(sf::RenderWindow& window, int column, int row)
{
		print_1(window);
}

