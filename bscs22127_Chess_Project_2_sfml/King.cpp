#include "King.h"
#include"Bishop.h"
#include"Rock.h"
#include"Peice.h"

King::King(Position P_p, Color clr, Board* B, char sym) :Peice(P_p, clr, B, sym) {
	if (get_Clr() == WHITE)
		ch1 = 'K';
	else if (get_Clr() == BLACK)
		ch1 = 'k';

	if (clr == BLACK)
		Sym2 = 'k';
	else if (clr == WHITE)
		Sym2 = 'K';

	if (P_color == WHITE)
		t.loadFromFile("King_1.png");
	else if (P_color == BLACK)
		t.loadFromFile("King_2.png");
	sp.setTexture(t);
	this->sp.setScale(0.07, 0.07);
}
void King::Draw_Peice()
{

	if (this->P_color == BLACK)
	{
		int height = 7;
		King_Sym(P_position.r, P_position.c, Sym, P_color);

	}
	else if (this->P_color == WHITE)
	{
		int height = 5;
		King_Sym(P_position.r, P_position.c, Sym, P_color);

	}
}

char King::get_sym()
{
	return ch1;
}

void King::King_Sym(int ri, int ci, char sym, int col)
{
	if (ri >= 8)
	{
		ri -= 8, ci = ci + 8 + 6;
	}
	ri = ((ri + 1) * Dimen2) + Dimen2 - 5;
	ci = ((ci)*Dimen2) + Dimen2 + 4;
	SetClr(col);
	gotoRowCol(ri - 3, ci - 3);
	for (int i = 0; i < 7; i++)
		cout << sym;
	gotoRowCol(ri - 2, ci - 1);
	for (int i = 0; i < 3; i++)
		cout << sym;
	gotoRowCol(ri - 1, ci);
	cout << sym;
	gotoRowCol(ri, ci - 1);
	for (int i = 0; i < 3; i++)
		cout << sym;
	gotoRowCol(ri + 1, ci - 2);
	for (int i = 0; i < 5; i++)
		cout << sym;
	gotoRowCol(ri + 2, ci - 3);
	for (int i = 0; i < 7; i++)
		cout << sym;
	gotoRowCol(ri + 3, ci - 3);
	for (int i = 0; i < 7; i++)
		cout << sym;
}


bool King::Peice_legal(Board B, Position Sc, Position Dc)
{
	int dr, dc;
	dr = Dc.r - Sc.r;
	dc = Dc.c - Sc.c;
	return((Rockleg(B, Sc, Dc) || bishopleg(B, Sc, Dc)) && abs(dr) <= 1 && abs(dc) <= 1);
}




bool King::Rockleg(Board B, Position Sc, Position Dc)
{
	return ((Ishorizontal(Sc, Dc) && Ishorizontalpathclear(B, Sc, Dc)) ||
		(Isvertical(Sc, Dc) && Isverticalpathclear(B, Sc, Dc)));
}
bool King::bishopleg(Board B, Position Sc, Position Dc)
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
	//return((Isdigonal(Sc, Dc) && IsprimarydigonalPathcler(B, Sc, Dc)) || (Isdigonal(Sc, Dc) && IssecondrydigonalPathcler(B, Sc, Dc)));
}