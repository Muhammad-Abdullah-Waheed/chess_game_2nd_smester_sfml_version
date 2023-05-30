#pragma once
#include<iostream>
#include<fstream>
#include<SFML/Graphics.hpp>
using namespace std;
class Peice;
struct Position
{
	int r, c;
};


class Board
{
private:
	int Dimension;
	Peice*** Ps;
	sf::Sprite S{};
	sf::Texture t{};
public:
	Board(ifstream& rdr);
	Board(int);

	Board();
	void Draw_box(sf::RenderWindow& w, Position p);
	void Generate_peices(char sym, Position P);
	
	void Utility();
	Peice* get_peice_at(Position P)
	{
		return Ps[P.r][P.c];
	}

	void set_peice_at(Peice* p, Position P);
	void postion_change(Position P1, Position P2);
	int get_Dimension() { return Dimension; };
	Position get_free_position(Position);
	void for_permotion(const Position p, int a);
	Peice*& get_peice_at(Position P,int );
	void display_image_1(sf::RenderWindow& w, sf::Vector2f V, sf::Vector2f scale, string name);


	Board(sf::RenderWindow& w,ifstream &rdr);
	void PrintLeft_right_arrow(sf::RenderWindow& window, sf::RectangleShape& r);

	/*~Board()
	{
		for (int i = 0; i < Dimension ; i++)
		{
			delete[]Ps[i];
		}
		delete[]Ps;
	}*/
	

	void delete_peice(Position p)
	{
		delete[] Ps[p.r][p.c];
	}
	void move_1(Position Sou, Position Des);
	void draw_board(sf::RenderWindow& w, sf::RectangleShape& r);
	void box(sf::RenderWindow& window, sf::RectangleShape& r, int ro, int c, int clr, int r_dim, int C_dim);
};

