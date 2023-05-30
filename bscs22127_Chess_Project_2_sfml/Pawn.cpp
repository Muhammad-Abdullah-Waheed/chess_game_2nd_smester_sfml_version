
#include "Pawn.h"
#include"Peice.h"


Pawn::Pawn(Position P_p, Color clr, Board* B, char sym) :Peice(P_p, clr, B, sym)
{
	if (clr == BLACK)
		Sym2 = 'p';
	else if (clr == WHITE)
		Sym2 = 'P';
	this->Fix.r = P_p.r;
	this->Fix.c = P_p.c;
	if (P_color == WHITE)
		t.loadFromFile("Pawn_1.png");
	else if (P_color == BLACK)
		t.loadFromFile("Pawn_2.png");
	sp.setTexture(t);
	this->sp.setScale(0.07, 0.07);
}

bool Pawn::Peice_legal(Board B, Position Sc, Position Dc)
{
	valuechanged(Sc);
	if (!is_first_move)
	{
		if (valuechanged(Sc))
		{
			if (B.get_peice_at(Sc)->get_Clr() == WHITE)
				return Pawndown(B, Sc, Dc, 1) ;
			else if (B.get_peice_at(Sc)->get_Clr() == BLACK)
				return Pawnup(B, Sc, Dc, 1);
		}
	}
	else
	{
		if (B.get_peice_at(Sc)->get_Clr() == WHITE)
			return Pawndown(B, Sc, Dc, 0) ;
		else if (B.get_peice_at(Sc)->get_Clr() == BLACK)
			return Pawnup(B, Sc, Dc, 0);
	}

}


bool Pawn::Pawnup(Board B, Position Sc, Position Dc, int a)
{
	Position j{};
	j.r = Sc.r - 1;
	j.c = Sc.c;
	int dr{}, dc{};
	dr = Dc.r - Sc.r;
	dc = Dc.c - Sc.c;
	if (a == 0)
		return ((B.get_peice_at({ Sc.r - 1,Sc.c }) == nullptr && Isvertical(Sc, Dc) && Isverticalpathclear(B, Sc, Dc) && dr == -1 && dc == dc)
			|| (B.get_peice_at({ Sc.r - 1,Sc.c + 1 }) != nullptr && dr == -1 && dc == 1) || (B.get_peice_at({ Sc.r - 1,Sc.c - 1 }) != nullptr && dr == -1 && dc == -1)
			);
	else if (a == 1)
		return (B.get_peice_at({ Sc.r - 1,Sc.c }) == nullptr && Isvertical(Sc, Dc) && Isverticalpathclear(B, Sc, Dc) && dr == -1 && dc == dc)
		|| (B.get_peice_at({ Sc.r - 2,Sc.c }) == nullptr && Isvertical(Sc, Dc) && Isverticalpathclear(B, Sc, Dc) && dr == -2 && dc == dc)
		|| (B.get_peice_at({ Sc.r - 1,Sc.c + 1 }) != nullptr && dr == -1 && dc == 1) || (B.get_peice_at({ Sc.r - 1,Sc.c - 1 }) != nullptr && dr == -1 && dc == -1);

}
bool Pawn::Pawndown(Board B, Position Sc, Position Dc, int a)
{
	int dr, dc;
	dr = Dc.r - Sc.r;
	dc = Dc.c - Sc.c;
	if (a == 0)
		return ((B.get_peice_at({ Sc.r + 1,Sc.c }) == nullptr && Isvertical(Sc, Dc) && Isverticalpathclear(B, Sc, Dc) && dr == 1 && dc == dc)
			|| (B.get_peice_at({ Sc.r + 1,Sc.c + 1 }) != nullptr && dr == 1 && dc == 1) || (B.get_peice_at({ Sc.r + 1,Sc.c - 1 }) != nullptr && dr == 1 && dc == -1));
	else if (a == 1)
		return (B.get_peice_at({ Sc.r + 1,Sc.c }) == nullptr && Isvertical(Sc, Dc) && Isverticalpathclear(B, Sc, Dc) && dr == 1 && dc == dc)
		|| (B.get_peice_at({ Sc.r + 2,Sc.c }) == nullptr && Isvertical(Sc, Dc) && Isverticalpathclear(B, Sc, Dc) && dr == 2 && dc == dc)
		|| (B.get_peice_at({ Sc.r + 1,Sc.c + 1 }) != nullptr && dr == 1 && dc == 1) || (B.get_peice_at({ Sc.r + 1,Sc.c - 1 }) != nullptr && dr == 1 && dc == -1);
}



bool Pawn::valuechanged(Position P)
{
	if (this->Fix.r != P.r || this->Fix.c != P.c)
		this->is_first_move = true;
	if (this->Fix.r == P.r && this->Fix.c == P.c)
		this->is_first_move = false;
	return true;
}




//bool Pawn::Pawnup(Board B, Position Sc, Position Dc, int a)
//{
//	Position j{};
//	j.r = Sc.r - 1;
//	j.c = Sc.c;
//	int dr{}, dc{};
//	dr = Dc.r - Sc.r;
//	dc = Dc.c - Sc.c;
//	if (a == 0)
//		return ((B.get_peice_at({ Sc.r - 1,Sc.c }) == nullptr && Isvertical(Sc, Dc) && Isverticalpathclear(B, Sc, Dc) && dr == -1 && dc == dc)
//			|| (B.get_peice_at({ Sc.r - 1,Sc.c + 1 }) != nullptr && dr == -1 && dc == 1) || (B.get_peice_at({ Sc.r - 1,Sc.c - 1 }) != nullptr && dr == -1 && dc == -1)
//			);
//	else if (a == 1)
//		return (Isvertical(Sc, Dc) && Isverticalpathclear(B, Sc, Dc) && (dr < 0 && dr >= -2) && dc == dc);
//
//}
//bool Pawn::Pawndown(Board B, Position Sc, Position Dc, int a)
//{
//	int dr, dc;
//	dr = Dc.r - Sc.r;
//	dc = Dc.c - Sc.c;
//	if (a == 0)
//		return ((B.get_peice_at({ Sc.r + 1,Sc.c }) == nullptr && Isvertical(Sc, Dc) && Isverticalpathclear(B, Sc, Dc) && dr == 1 && dc == dc)
//			|| (B.get_peice_at({ Sc.r + 1,Sc.c + 1 }) != nullptr && dr == 1 && dc == 1) || (B.get_peice_at({ Sc.r + 1,Sc.c - 1 }) != nullptr && dr == 1 && dc == -1));
//	else if (a == 1)
//		return (Isvertical(Sc, Dc) && Isverticalpathclear(B, Sc, Dc) && dr > 0 && dr <= 2 && dc == dc);
//}