#include"Board.h"
#include"Pawn.h"
#include"Rock.h"
#include"Knight.h"
#include"King.h"
#include"Queen.h"
#include"Bishop.h"
#include"Peice.h"
#include"Header.h"



Board::Board(int n)
{
	Dimension = 8;

	Ps = new Peice * *[Dimension + 4] {};
	for (int i = 0; i < Dimension + 4; i++)
	{
		Ps[i] = new Peice * [Dimension] {};
	}

}


Board::Board(ifstream& rdr)
{
	sf::Vector2f v{};
	char imp = 'v';
	do
	{
		cout << "Enter the Dimension of Board (8 for chess).";
		rdr >> Dimension;
	} while (Dimension != 8);
	


	Ps = new Peice * *[Dimension + 4] {};
	for (int i = 0; i < Dimension + 4; i++)
	{
		Ps[i] = new Peice * [Dimension] {};
		for (int j = 0; j < Dimension; j++)
		{


			int a = 15;
			v.y = (i+1) * 100 + a -5;
			v.x = (j+4) * 100 + a -10;

			rdr >> imp;
			if (imp == '-')
				Ps[i][j] = nullptr;
			else
			{
				Generate_peices(imp, { i,j }), Ps[i][j]->set_vector_posi(v);
			}
		}
	}
}



Board::Board()
{
	do
	{
		cout << "Enter the Dimension of Board (8 for chess).";
		Dimension = 8;
	} while (Dimension != 8);
	Utility();

}
void Board::Generate_peices(char sym, Position P)
{
	switch (sym)
	{
	case 'P':
		Ps[P.r][P.c] = new Pawn(P, WHITE, this, 'P');
		break;
	case 'p':
		Ps[P.r][P.c] = new Pawn(P, BLACK, this, 'p');
		break;
	case 'R':
		Ps[P.r][P.c] = new Rock(P, WHITE, this, 'R');
		break;
	case 'r':
		Ps[P.r][P.c] = new Rock(P, BLACK, this, 'r');
		break;
	case 'Q':
		Ps[P.r][P.c] = new Queen(P, WHITE, this, 'Q');
		break;
	case 'q':
		Ps[P.r][P.c] = new Queen(P, BLACK, this, 'q');
		break;
	case 'K':
		Ps[P.r][P.c] = new King(P, WHITE, this, 'K');
		break;
	case 'k':
		Ps[P.r][P.c] = new King(P, BLACK, this, 'k');
		break;
	case 'N':
		Ps[P.r][P.c] = new Knight(P, WHITE, this, 'N');
		break;
	case 'n':
		Ps[P.r][P.c] = new Knight(P, BLACK, this, 'n');
		break;
	case 'B':
		Ps[P.r][P.c] = new Bishop(P, WHITE, this, 'B');
		break;
	case 'b':
		Ps[P.r][P.c] = new Bishop(P, BLACK, this, 'b');
		break;
	}
}

void Board::Utility()
{
	char ch = '*';
	Ps = new Peice * *[Dimension + 4] {};
	for (int r = 0; r < Dimension + 4; r++)
	{
		Ps[r] = new Peice * [Dimension] {};
		for (int c = 0; c < Dimension; c++)
		{
			Position T{};
			T.r = r;
			T.c = c;
			if (r == 1)
				Ps[r][c] = new Pawn(T, WHITE, this, ch);
			else if (r == 6)
				Ps[r][c] = new Pawn(T, BLACK, this, ch);
			else if (r == 0 && (c == 0 || c == 7))
				Ps[r][c] = new Rock(T, WHITE, this, ch);
			else if (r == 7 && (c == 0 || c == 7))
				Ps[r][c] = new Rock(T, BLACK, this, ch);
			else if (r == 0 && (c == 1 || c == 6))
				Ps[r][c] = new Knight(T, WHITE, this, ch);
			else if (r == 7 && (c == 1 || c == 6))
				Ps[r][c] = new Knight(T, BLACK, this, ch);
			else if (r == 0 && (c == 2 || c == 5))
				Ps[r][c] = new Bishop(T, WHITE, this, ch);
			else if (r == 7 && (c == 2 || c == 5))
				Ps[r][c] = new Bishop(T, BLACK, this, ch);
			else if (r == 0 && (c == 4))
				Ps[r][c] = new King(T, WHITE, this, ch);
			else if (r == 7 && (c == 4))
				Ps[r][c] = new King(T, BLACK, this, ch);
			else if (r == 0 && (c == 3))
				Ps[r][c] = new Queen(T, WHITE, this, ch);
			else if (r == 7 && (c == 3))
				Ps[r][c] = new Queen(T, BLACK, this, ch);
			else
				Ps[r][c] = nullptr;
		}
	}
}
Board::Board(sf::RenderWindow& w, ifstream& rdr)
{
	Dimension = 8;
	sf::Vector2f v{};
	Ps = new Peice * *[Dimension + 4] {};
	for (int r = 0; r < Dimension + 4; r++)
	{
		Ps[r] = new Peice * [Dimension] {};
		for (int c = 0; c < Dimension; c++)
		{
			int a = 15;
			v.x = c * 100 +a-5;
			v.y = r * 100 +a;
			Position T{};
			T.r = r;
			T.c = c;
			if (r == 1)
				Ps[r][c] = new Pawn(T, WHITE, this, 'P'), Ps[r][c]->set_vector_posi(v);
			else if (r == 6)
				Ps[r][c] = new Pawn(T, BLACK, this, 'p'), Ps[r][c]->set_vector_posi(v);
			else if (r == 0 && (c == 0 || c == 7))
				Ps[r][c] = new Rock(T, WHITE, this, 'R'), Ps[r][c]->set_vector_posi(v);
			else if (r == 7 && (c == 0 || c == 7))
				Ps[r][c] = new Rock(T, BLACK, this, 'r'), Ps[r][c]->set_vector_posi(v);
			else if (r == 0 && (c == 1 || c == 6))
				Ps[r][c] = new Knight(T, WHITE, this, 'N'), Ps[r][c]->set_vector_posi(v);
			else if (r == 7 && (c == 1 || c == 6))
				Ps[r][c] = new Knight(T, BLACK, this, 'n'), Ps[r][c]->set_vector_posi(v);
			else if (r == 0 && (c == 2 || c == 5))
				Ps[r][c] = new Bishop(T, WHITE, this, 'B'), Ps[r][c]->set_vector_posi(v);
			else if (r == 7 && (c == 2 || c == 5))
				Ps[r][c] = new Bishop(T, BLACK, this, 'b'), Ps[r][c]->set_vector_posi(v);
			else if (r == 0 && (c == 4))
				Ps[r][c] = new King(T, WHITE, this, 'K'), Ps[r][c]->set_vector_posi(v);
			else if (r == 7 && (c == 4))
				Ps[r][c] = new King(T, BLACK, this, 'k'), Ps[r][c]->set_vector_posi(v);
			else if (r == 0 && (c == 3))
				Ps[r][c] = new Queen(T, WHITE, this, 'Q'), Ps[r][c]->set_vector_posi(v);
			else if (r == 7 && (c == 3))
				Ps[r][c] = new Queen(T, BLACK, this, 'q'), Ps[r][c]->set_vector_posi(v);
			else
				Ps[r][c] = nullptr;
		}
	}
}


Peice*& Board::get_peice_at(Position P,int a=0)
{
	return Ps[P.r][P.c];
}
void Board::set_peice_at(Peice* p, Position P)
{
	Ps[P.r][P.c] = p;
}



void Board::for_permotion(const Position p, int a)
{
	Peice* o;
	if (a == -1)
	{
		o = new Pawn(p, Ps[p.r][p.c]->get_Clr(), this, ' ');
	}
	else if (a == 1)
		o = new Knight(p, Ps[p.r][p.c]->get_Clr(), this, '?');
	else if (a == 2)
		o = new Bishop(p, Ps[p.r][p.c]->get_Clr(), this, '?');
	else if (a == 3)
		o = new Queen(p, Ps[p.r][p.c]->get_Clr(), this, '?');
	else
		o = new Rock(p, Ps[p.r][p.c]->get_Clr(), this, '?');


	//delete[] *(Ps[p.r][p.c];
	Ps[p.r][p.c] = nullptr;
	Ps[p.r][p.c] = o;
}

void Board::postion_change(Position P1, Position P2)
{
	Ps[P1.r][P1.c]->Peice_move(P2);
	swap(Ps[P1.r][P1.c], Ps[P2.r][P2.c]);
	delete[] Ps[P1.r][P1.c];
	Ps[P1.r][P1.c] = nullptr;

}


Position Board::get_free_position(Position P1)
{
	Position PP{ -1,-1 };
	for (int i = Dimension; i < Dimension + 4; i++)
	{
		for (int k = 0; k < Dimension; k++)
		{
			if (Ps[i][k] == nullptr)
			{
				if (i < 10 && Ps[P1.r][P1.c]->get_Clr() == WHITE)
				{
					PP.r = i, PP.c = k;
					return PP;
				}
				else if (i >= 10 && Ps[P1.r][P1.c]->get_Clr() == BLACK)
				{
					PP.r = i, PP.c = k;
					return PP;
				}
			}
		}
	}
	return { 0,0 };
}
void Board::display_image_1(sf::RenderWindow& w, sf::Vector2f V, sf::Vector2f scale, string name)
{
	sf::Texture temp;

	if (!temp.loadFromFile(name))
	{
		throw("Unable to load img");
	}

	sf::Sprite s(temp);
	s.setScale(V.x, V.y);

	s.setPosition(scale.y, scale.x);
	w.draw(s);
}
void display_text(sf::RenderWindow& window, string txt, int row, int col)
{
	sf::Font font;
	if (!font.loadFromFile("impact.ttf"))
	{
		cout << "Ivalid text slected _____! Try again.....";
		return exit(-1);
	}
	sf::Text text(txt, font, 30);
	text.setFillColor(sf::Color::Black);
	text.setPosition(row * 100, col * 100+30);
	//text.setColor(sf::Color::Black);
	window.draw(text);
}
void Board::PrintLeft_right_arrow(sf::RenderWindow & window, sf::RectangleShape& r)
{
	box(window, r, 8, 2,3, 100, 100);
	display_text(window, "   UNDO   ", 2, 8);
	box(window, r, 8, 13,3, 100, 100);
	display_text(window, "   REDO ", 13, 8);
}
void Board::draw_board(sf::RenderWindow& w, sf::RectangleShape& r)
{
	//w.draw(S);
	for (int i = 0; i < Dimension; i++)
	{
		for (int k = 0; k < Dimension; k++)
		{
				box(w, r, i+1 , k+4, 0,100,100);
		}
	}


	PrintLeft_right_arrow(w,r);

}
void Board::Draw_box(sf::RenderWindow & w,Position p)
{
	if (((p.r + p.c) % 2) == 0)
	{
		sf::Vector2f v1{}, v2{};
		v1.x = 0.330; v1.y = 0.327; v2.x = (p.r) * 100; v2.y = (p.c) * 100;
		display_image_1(w, v1, v2, "blackbox.jpeg");
	}
	else if (((p.r + p.c) % 2) != 0)
	{
		sf::Vector2f v1{}, v2{};
		v1.x = 0.1099; v1.y = 0.1098; v2.x = (p.r) * 100; v2.y = (p.c) * 100;
		display_image_1(w, v1, v2, "Gray_Box.jpg");
	}
}

void Board::box(sf::RenderWindow& window, sf::RectangleShape& r,int ro,int c,int clr,int r_dim,int c_dim)
{
	if (clr == 0)
	{
		if ((ro + c) % 2 == 0)
		{
			r.setFillColor(sf::Color::Black);
			r.setPosition(c * c_dim, ro * r_dim);
			window.draw(r);
		}
		else if ((ro + c) % 2 != 0)
		{
			r.setFillColor(sf::Color::White);
			r.setPosition(c * c_dim, ro * r_dim);
			window.draw(r);
		}
	}
	if (clr == 1)
	{
		r.setFillColor(sf::Color::Blue);
		r.setPosition(c * c_dim, ro * r_dim);
		window.draw(r);
	}
	if (clr == 2)
	{
		r.setFillColor(sf::Color::Red);
		r.setPosition(c * c_dim, ro * r_dim);
		window.draw(r);
	}
	if (clr == 3)
	{
		r.setFillColor(sf::Color::Cyan);
		r.setPosition(c * c_dim, ro * r_dim);
		window.draw(r);
	}
	if (clr == 4)
	{
		r.setFillColor(sf::Color::Green);
		r.setPosition(c * c_dim, ro * r_dim);
		window.draw(r);
	}

}

void Board::move_1(Position Sou,Position Des)
{
	sf::Vector2f v;
	v.x = (Des.c + 4) * 100;
	v.y = (Des.r + 1) * 100;
	Ps[Sou.r][Sou.c]->set_vector_posi(v);
	Ps[Sou.r][Sou.c]->Peice_move(Des);
	delete[] Ps[Des.r][Des.c];
	Ps[Des.r][Des.c] = nullptr;
	swap(Ps[Sou.r][Sou.c], Ps[Des.r][Des.c]);
	
	Ps[Sou.r][Sou.c] = nullptr;
}



