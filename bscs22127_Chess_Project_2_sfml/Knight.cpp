#include "Knight.h"
#include"Peice.h"



Knight::Knight(Position P_p, Color clr, Board* B, char sym) :Peice(P_p, clr, B, sym)
{
	if (clr == BLACK)
		Sym2 = 'n';
	else if (clr == WHITE)
		Sym2 = 'N';
	if (P_color == WHITE)
		t.loadFromFile("Knight_1.png");
	else if (P_color == BLACK)
		t.loadFromFile("Knight_2.png");
	sp.setTexture(t);
	this->sp.setScale(0.07, 0.07);
}
bool Knight::Peice_legal(Board B, Position Sc, Position Dc)
{
	int dr, dc;
	dr = Dc.r - Sc.r;
	dc = Dc.c - Sc.c;
	return ((abs(dr) == 2 && abs(dc) == 1) || (abs(dr) == 1 && abs(dc) == 2));
}