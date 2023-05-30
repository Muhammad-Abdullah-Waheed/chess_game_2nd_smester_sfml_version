#include "Bishop.h"
#include"Peice.h"
#include"Chess.h"
Bishop::Bishop(Position P_p, Color clr, Board* B, char sym) :Peice(P_p, clr, B, sym)
{
	if (clr == BLACK)
		Sym2 = 'b';
	else if (clr == WHITE)
		Sym2 = 'B';
	if (P_color == WHITE)
		t.loadFromFile("Bishop_1.png");
	else if (P_color == BLACK)
		t.loadFromFile("Bishop_2.png");
	sp.setTexture(t);
	this->sp.setScale(0.07, 0.07);
}
void Bishop::Draw_Peice()
{
	if (this->P_color == BLACK)
	{
		int height = 7;
		Bishop_Sym(P_position.r, P_position.c, Sym, P_color);

	}
	else if (this->P_color)
	{
		int height = 5;
		Bishop_Sym(P_position.r, P_position.c, Sym, P_color);

	}
}

void Bishop::Bishop_Sym(int ri, int ci, char sym, int col)
{
	if (ri >= 8)
	{
		ri -= 8, ci = ci + 8 + 6;
	}
	ri = ((ri + 1) * Dimen2) + Dimen2 - 5;
	ci = ((ci + 1) * Dimen2) + Dimen2 - 5;

	SetClr(col);
	gotoRowCol(ri - 2, ci - 4);
	for (int i = 0; i < 7; i++)
		cout << sym;
	gotoRowCol(ri - 1, ci - 1);
	for (int i = 0; i < 2; i++)
		cout << sym;
	gotoRowCol(ri, ci - 1);
	for (int i = 0; i < 2; i++)
		cout << sym;
	gotoRowCol(ri + 1, ci - 1);
	for (int i = 0; i < 2; i++)
		cout << sym;
	gotoRowCol(ri, ci - 4);
	for (int i = 0; i < 7; i++)
		cout << sym;
	gotoRowCol(ri + 2, ci - 4);
	for (int i = 0; i < 7; i++)
		cout << sym;
}


bool Bishop::Peice_legal(Board B, Position Sc, Position Dc)
{
	int dr, dc;
	dr = Dc.r - Sc.r;
	dc = Dc.c - Sc.c;
	if (dr == dc)
	{
		return(Isdigonal(Sc, Dc) && IsprimarydigonalPathcler(B, Sc, Dc));
	}
	else if (dr != dc)
	{
		return (Isdigonal(Sc, Dc) && IssecondrydigonalPathcler(B, Sc, Dc));
	}
}
