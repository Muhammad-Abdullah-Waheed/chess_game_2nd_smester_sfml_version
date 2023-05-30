#include "Queen.h"
#include"Peice.h"
#include"Rock.h"
Queen::Queen(Position P_p, Color clr, Board* B, char sym) :Peice(P_p, clr, B, sym)
{
	if (clr == BLACK)
		Sym2 = 'q';
	else if (clr == WHITE)
		Sym2 = 'Q';

	if (P_color == WHITE)
		t.loadFromFile("Queen_1.png");
	else if (P_color == BLACK)
		t.loadFromFile("Queen_2.png");
	sp.setTexture(t);
	this->sp.setScale(0.07, 0.07);
}
bool Queen::Rockleg(Board B, Position Sc, Position Dc)
{
	return ((Ishorizontal(Sc, Dc) && Ishorizontalpathclear(B, Sc, Dc)) ||
		(Isvertical(Sc, Dc) && Isverticalpathclear(B, Sc, Dc)));
}
bool Queen::bishopleg(Board B, Position Sc, Position Dc)
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
bool Queen::Peice_legal(Board B, Position Sc, Position Dc)
{
	int dr, dc;
	dr = Dc.r - Sc.r;
	dc = Dc.c - Sc.c;
	return((Rockleg(B, Sc, Dc) || bishopleg(B, Sc, Dc)));
}