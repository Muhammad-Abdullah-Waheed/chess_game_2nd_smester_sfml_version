#pragma once
#include"Header.h"
#include"Board.h"


class Peice
{
protected:
	Position P_position;
	Color P_color;
	Board* board;
	char Sym;
	char Sym2{ 'g' };
	sf::Vector2f V{};
	sf::Texture t{};
	sf::Sprite sp{};
	void set_posi(sf::Vector2f v)
	{
		V.x = v.x, V.y = v.y;
	}
public:
	virtual void set_vector_posi(sf::Vector2f& v) = 0;
	int get_x()
	{
		return V.x;
	}
	int get_y()
	{
		return V.y;
	}
	Peice() = default;
	Peice(Position P_p, Color clr, Board* B, char sym = char(-37));
	virtual void Draw_Peice() {};
	void Peice_move(Position P_p);
	virtual char get_sym() { return '-'; }
	Color get_Clr();

	virtual bool Peice_legal(Board B, Position Sc, Position Dc) = 0;

	char get_sym1() { return Sym2; }

	bool Ishorizontal(Position Sc, Position Dc);
	bool Isvertical(Position Sc, Position Dc);
	bool Isdigonal(Position Sc, Position Dc);
	bool Ishorizontalpathclear(Board B, Position& Sc, Position& Dc);
	bool Isverticalpathclear(Board B, Position& Sc, Position& Dc);
	bool IsprimarydigonalPathcler(Board B, Position& Sc, Position& Dc);
	bool IssecondrydigonalPathcler(Board B, Position& Sc, Position& Dc);


	virtual void print(sf::RenderWindow& window, int column, int row ) = 0;
	void print_1(sf::RenderWindow& window)
	{
		/*this->sp.setScale(0.07, 0.07);*/ 
		if (P_position.r >= 8)
			V.x += 200;
		sp.setPosition(V.x, V.y);
		window.draw(sp);	
	}
};

