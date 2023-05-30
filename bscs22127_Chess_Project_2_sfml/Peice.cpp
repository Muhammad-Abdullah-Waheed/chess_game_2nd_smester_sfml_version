#include"Chess.h"
#include "Peice.h"

Peice::Peice(Position P_p, Color clr, Board* B, char sym)
{
	this->P_position.c = P_p.c;
	this->P_position.r = P_p.r;

	this->P_color = clr;

	this->board = B;

	this->Sym = sym;
}


void Peice::Peice_move(Position P_p)
{

	this->P_position.r = P_p.r;
	this->P_position.c = P_p.c;
}

Color Peice::get_Clr()
{
	return P_color;
}



bool Peice::Ishorizontal(Position Sc, Position Dc)
{
	return (Sc.r == Dc.r);
}
bool Peice::Isvertical(Position Sc, Position Dc)
{
	return (Sc.c == Dc.c);
}
bool Peice::Isdigonal(Position Sc, Position Dc)
{
	int Ds = 0, De = 0;
	Ds = Dc.r - Sc.r;
	De = Dc.c - Sc.c;
	return (abs(Ds) == abs(De));
}
bool Peice::Ishorizontalpathclear(Board B, Position& Sc, Position& Dc)
{
	int s = 0, e = 0;
	if (Sc.c < Dc.c)
	{
		s = Sc.c + 1;
		e = Dc.c - 1;
	}
	else if (Sc.c > Dc.c)
	{
		s = Dc.c + 1;
		e = Sc.c - 1;
	}
	

	for (s; s <= e; s++)
		if (B.get_peice_at({Sc.r,s}) != nullptr)
			return false;
	return true;
}
bool Peice::Isverticalpathclear(Board B, Position& Sc, Position& Dc)
{
	int sp = 0, ep = 0;
	if (Sc.r < Dc.r)
	{
		sp = Sc.r + 1;
		ep = Dc.r - 1;
	}
	else if (Sc.r > Dc.r)
	{
		sp = Dc.r + 1;
		ep = Sc.r - 1;
	}

	for (int i = sp; i <= ep; i++)
	{
		if (B.get_peice_at({i,Sc.c}) != nullptr)
			return false;
	}
	return true;
}
bool Peice::IsprimarydigonalPathcler(Board B, Position& Sc, Position& Dc)
{
	int Ds = 0, De = 0, s = 0, e = 0;
	Ds = Dc.r - Sc.r;
	De = Dc.c - Sc.c;
	if (Sc.r < Dc.r)
	{
		s = Sc.r;
		e = Sc.c;
	}
	else if (Sc.r > Dc.r)
	{
		s = Dc.r;
		e = Dc.c;
	}
	for (int i = 1; i < abs(Ds); i++)
	{
		Position temp{};
		temp.r = s + i;
		temp.c = e + i;
		if (B.get_peice_at(temp) != nullptr)
			return false;
	}return true;
}
bool Peice::IssecondrydigonalPathcler(Board B, Position& Sc, Position& Dc)
{
	int Ds = 0, De = 0, s = 0, e = 0;
	Ds = Dc.r - Sc.r;
	De = Dc.c - Sc.c;
	if (Sc.r < Dc.r)
	{
		s = Sc.r;
		e = Sc.c;
	}
	else if (Sc.r > Dc.r)
	{
		s = Dc.r;
		e = Dc.c;
	}
	for (int i = 1; i < abs(Ds); i++)
	{
		Position temp{};
		temp.r = s + i;
		temp.c = e - i;
		if (B.get_peice_at(temp) != nullptr)
			return false;
	}return true;
}

