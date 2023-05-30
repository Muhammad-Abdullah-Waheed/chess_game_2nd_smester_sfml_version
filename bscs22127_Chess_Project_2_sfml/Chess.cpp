#include "Chess.h"
#include"Player.h"
#include"Header.h"
#include"Board.h"
#include<ctime>
#include"Peice.h"
#include"Pawn.h"
#include"mmsystem.h"
#include<windows.h>
#include <ctime>
#include<iomanip>
#include<vector>
using namespace std;

Chess::Chess(sf::RenderWindow& window,ifstream &rdr, sf::RectangleShape& r)
{
	string n1, n2;
	std::cout << "Enetr first player name:   ";
	rdr >> n1;
	Ps[0] = new Player(n1, BLACK);
	/*cout << Ps[0] << "\n\n";*/
	std::cout << "Enetr second player name:  ";
	rdr >> n2;
	Ps[1] = new Player(n2, WHITE);
	/*cout << Ps[0] << "\n\n";*/

	B = new Board(rdr);

	srand(time(0));

	//Turn = rand() % 2;
	Turn = 0;


	if (!t.loadFromFile("B_G_B.jpg"))
	{
		throw("Unable to load img");
	}
	this->s.setTexture(t);
	s.setScale(2.4, 2.2);
	s.setPosition(0, 0);
}
void Chess::turn_change()
{
	clock.restart();
	Is_hilight = false;
	
	turn_changing(this->Turn);
}
void Chess::Play(sf::RenderWindow& window,sf::RectangleShape& r)
{
	int count1{}, count2{};
	bool** K_b{};
	vector<Position>Rep;
	countdownTime = sf::seconds(180.10f);


	int i = 0; bool a=true;
	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == event.Closed)
				window.close();
			if (event.type == event.MouseButtonPressed)
				a = select_position(window, count1, count2, Rep, K_b,r);
		}

		display_back(window);
		B->draw_board(window,r);
		draw_peices(window);


		if (Is_hilight && !a)
		{
			Hilight(K_b,window,Sou,Turn);
			drawhigli(K_b, window, r);
		}
		if (dispaly_time(11, 0, window, countdownTime))
				turn_change();
		window.display();
	}
}

bool Chess::dispaly_time(int row,int col,sf::RenderWindow & w,sf::Time  T )
{
	sf::Time elapsed;
	elapsed = countdownTime - clock.getElapsedTime();
	int minutes = elapsed.asSeconds() / 60;
	int seconds = elapsed.asSeconds();
	seconds %= 60;
	int milliseconds = elapsed.asMilliseconds() % 1000;
	if (elapsed <= sf::Time::Zero) {
		minutes = 0;
		seconds = 0;
		milliseconds = 0;
	}
	std::string time_str = ((minutes < 10) ? "0" : "")+std::to_string(minutes) + ":" + ((seconds<10)? "0" : "") + std::to_string(seconds);
	display_text(w, time_str, row, col);

	if (minutes == 0 && seconds == 0)
	{
		return true;
	}
	return false;
}
void Chess::display_back(sf::RenderWindow & window)
{
	window.draw(s);
}
void Chess::getRowColbyLeftClick(int& rpos, int& cpos, sf::RenderWindow& window)
{
		sf::Vector2i p = sf::Mouse::getPosition(window);
		cpos = p.x;
		rpos = p.y;
}
bool Chess::select_position(sf::RenderWindow& window,int& count1,int& count2, vector<Position> &Rep,bool** King_bool, sf::RectangleShape& r)
{

		Position P{};
		Position S = Sou;
		Position D = Des;

		get_position(P,window);
	
		if (Replaymess(P))
		{
			if (undo(Rep, window, count1, count2, r))
				turn_change();
		}
		if (Redomess(P))
		{
			if (redo(Rep, window, count1, count2, r))
				turn_change();
		}
		if (resumechk(P))
		{
			resume(B, B->get_Dimension(), Ps, "Resume.txt");
		}
		if (IsExit(P,window)) 
		{ window.close(); }
		if (Isreplay2(P))
		{
			Reply2(B, Rep, count1, B->get_Dimension(), Turn, "Text1.txt",r);
		}

		P.r -= 1;
		P.c -= 4;
		if (!is_right_source)
			Sou = P;
		Des = P;
		if (Valid_Source(Ps[Turn], P) && !is_right_source)
		{
			is_right_source = true;
			S = P;

			Is_hilight = true;

			return false;
		}
		else if ((is_right_source) && Valid_Destination(Ps[Turn], P))
		{
			D = P;
			is_right_des = true;
			Is_hilight = false;
		}
		else 
		{
			is_right_des = false;
			is_right_source = false;

			return true;
		}
		Sou = S;
		Des = D;


		if (is_right_des && is_right_source && Isvaildpath(B,Sou,Des,Ps[Turn], window,Turn) && (!Self_check_imp(B,8,Turn,Sou,Des,Ps,window)))
		{
			char ch = B->get_peice_at(Sou)->get_sym();
			if (((ch == 'p') && (Des.r < 2)) || ((ch == 'P' && Des.r > 5)))
			{
				Select_for_premoted_pawn(Sou, Des,window);
			}
			if (IfCapture(B, Sou, Des))
			{
				Position t = B->get_free_position(Sou),a=Sou,b=Des;
				Sou = Des;
				Des = t;
				move();
				ReplayArray(Rep, count1);
				Sou = a;
				Des = b;
			}
			is_castling(Sou, count2, count1, Rep, Des, window);

			Des = D;
			Sou = S;
			move();
			ReplayArray(Rep, count1);
			is_right_des = false;
			is_right_source = false;

			ckeckmakkkk(B, B->get_Dimension(), Turn, Sou, Des, Ps, window);
			Ste_Make(B, Ps, Turn, Sou, Des, B->get_Dimension(), window);
			turn_change();

			checkpoint(B, 8, Ps, Sou, Des, Turn, window);
			if (count2 < 2)
				count2 = 0;


			return true;
		}
}
void  Chess::hilghiking(Board* B, int dim, Player** P, int turn, sf::RenderWindow& window, sf::RectangleShape& r)
{
	Position R{};
	turn_changing(turn);
	R = findking(B,dim,Ps[turn],window );
	B->box(window, r, R.r, R.c,2, 100, 100);

	
}

void Chess::getRowColbyLeftClick_1(int& rpos, int& cpos, sf::RenderWindow& window)
{
	while (true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i p = sf::Mouse::getPosition(window);

			cpos = p.x;
			rpos = p.y;
			break;
		}
	}
}



bool Chess::Replaymess(Position Sc)
{
	char c = ' ';
	if (Sc.r >= 8 && Sc.c == 2)
	{
		return true;
	}
	return false;
}
bool Chess::Redomess(Position Sc)
{
	char c = ' ';
	if (Sc.r >= 8 && Sc.c == 13)
	{
		return true;
	}
	return false;
}
void Chess::replay(vector<Position>& C, int count, int scount, Position& Sc, Position& Dc)
{
	int d = count - scount;
	Sc = C[d - 1];
	Dc = C[d - 2];
}
bool Chess::undo(vector<Position>& C, sf::RenderWindow& window, int count, int& count2, sf::RectangleShape& r)
{
	if (count - (count2) > 1)
	{
		Sou = C[count-count2 - 1 ];
		Des = C[count-count2 - 2];
		move();
		count2 += 2;
		return true;
	}
	return false;

}
void Chess::move()
{
	sf::Vector2f v;
	v.x = (Des.c+4)*100;
	v.y = (Des.r+1)*100;
	B->get_peice_at(Sou)->set_vector_posi(v);
	B->get_peice_at(Sou)->Peice_move(Des);
	B->postion_change(Sou, Des);
}
void Chess::draw_peices(sf::RenderWindow& w)
{
	for (int i = 0; i < Dimen2 +2; i++)
	{
		for (int j = 0; j < Dimen2 - 2; j++)
		{
			if (B->get_peice_at({ i,j }) != nullptr)
			{
				if (i < 8)
				{
					B->get_peice_at({ i,j })->print(w, 0, 0);
				}
				else if (i<10)
				{
					Print_peices(w, B->get_peice_at({ i,j })->get_sym1(), { i+6,j+1 });
				}
				else
				{
					Print_peices(w, B->get_peice_at({ i,j })->get_sym1(), { i-10,j+1 });
				}
			}
		}
	}
	display_text(w, Ps[1]->get_name(), 1, 0);
	display_text(w, Ps[0]->get_name() , 15, 0);

	display_text(w, "<<<  Exit  >>> ", 16, 8);
	display_text(w, "<<< REPLY >>> ", 16, 7);
	display_text(w, "<<< RESUME >>> ", 16, 6);
	display_text(w, Ps[Turn]->get_name() + " Now Its yours turn__!! ", 5, 0);
	if (is_cake_mate)
		display_text(w, Ps[Turn]->get_name() + " You are now in Check MATe ____!", 6, 9);
	if(is_check)
		display_text(w, Ps[Turn]->get_name() + " You are now in Check ____!", 6, 9);
	else if (is_self_ckeck )
		display_text(w, Ps[Turn]->get_name() + " You are now in self Check ____!", 6, 9);
	else if(is_stale_chek )
		display_text(w, Ps[Turn]->get_name() + " You are now in Stale MATe____!", 6, 9);




		


}
bool Chess::IsExit(Position F,sf::RenderWindow & w)
{
	if (F.r == 8 && F.c == 17)
	{
		display_text(w,"GAME OVER Sir ALLAH HAFIZ", 10, 3);
		return true;
	}
	return false;

}
bool Chess::Isreplay2(Position F)
{
	if (F.r == 7 && F.c == 17)
	{
		return true;
	}return false;
}
bool Chess::IsCastling(Position F)
{
	if (F.r == 8 && F.c == 17)
	{
		return true;
	}return false;
}
bool Chess::resumechk(Position Sc)
{
	char c = ' ';
	if (Sc.r == 6 && Sc.c == 17)
	{
		return true;
	}
	return false;
}
void Chess::display_text(sf::RenderWindow & window,string txt, int row, int col)
{
	sf::Font font;
	if (!font.loadFromFile("impact.ttf"))
	{
		cout << "Ivalid text slected _____! Try again.....";
		return exit(-1);
	}
	sf::Text text(txt, font, 40);
	text.setFillColor(sf::Color::Green);
	text.setPosition(row*100,col*100);
	window.draw(text);
}
void Chess::Print_peices(sf::RenderWindow & window ,char sym, Position P)
{
	string n{};
	switch (sym)
	{
	case 'P':
		n = "Pawn_1.png";
		break;
	case 'p':
		n = "Pawn_2.png";
		break;
	case 'R':
		n = "Rook_1.png";
		break;
	case 'r':
		n = "Rook_2.png";
		break;
	case 'Q':
		n = "Queen_1.png";
		break;
	case 'q':
		n = "Queen_2.png";
		break;
	case 'K':
		n = "King_1.png";
		break;
	case 'k':
		n = "King_2.png";
		break;
	case 'N':
		n = "Knight_1.png";
		break;
	case 'n':
		n = "Kinght_2.png";
		break;
	case 'B':
		n = "Bishop_1.png";
		break;
	case 'b':
		n = "Bishop_2.png";
		break;
	}
	sf::Vector2f v1{}, v2{};
	v1.x = 1; v1.y = 1;
	v2.x = (P.c) * 100 + 10;
	v2.y = (P.r) * 100 + 25;
	display_image(window, {0.07,0.07},v2 , n);
}
void Chess::Select_for_premoted_pawn(Position So, Position De,sf::RenderWindow & w)
{
	sf::RenderWindow win(sf::VideoMode(1000, 500), "Menu for Pawn Permotion__!");
	sf::Texture texture;
		sf::RectangleShape r;
		sf::Vector2f v;
		v.x = 100;
		v.y = 100;
		r.setSize(v);
		if (!texture.loadFromFile("B_1.jpg"))
		{
			cout << "Wrong input file selecte in permotion funtion__1";
		}
		sf::Sprite sprite(texture);
		sprite.setScale(0.6, 0.42);
		sprite.setPosition(0, 0);
		win.draw(sprite);
	


	int  k = 3;
	for (int i = 9; i < 13; i++)
	{
		sf::Vector2f v1{}, v2{};
		v2.x = k * 100 +  10;
		v2.y = (i-6) * 100 + 15;
		v1.x = 0.07; v1.y = 0.07; 
		B->box(win,r,k,i-6,0,100,100);


		string name{};

		display_text(win, Ps[Turn]->get_name() + " Please select any peice for permotion_!", 1, 1);
		if (i ==9 )
		{
			if (Turn == 0)
				name = "Knight_2.png";
			else if (Turn == 1)
				name = "Knight_1.png";
		}
		else if (i == 11 )
		{
			if (Turn == 0)
				name = "Bishop_2.png";
			else if (Turn == 1)
				name = "Bishop_1.png";
		}
		else if (i == 12 )
		{
			if (Turn == 0)
				name = "Queen_2.png";
			else if (Turn == 1)
				name = "Queen_1.png";
		}
		else if (i == 10 )
		{
			if (Turn == 0)
				name = "Rook_2.png";
			else if(Turn == 1)
				name = "Rook_1.png";
		}
		display_image(win, v1, v2, name);
	}
	win.display();
	Position p{};
	do
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			get_position(p,win);
			if (p.r == 3 && (p.c == 3 || p.c == 4 || p.c == 5 || p.c == 6));
				break;
		}
		
	} while (true);
	win.close();
	if (p.r == 3)
	{
		if (p.c == 3)
		{
			B->for_permotion(So, 1);
		}
		if (p.c == 4)
		{
			B->for_permotion(So, 4);
		}
		if (p.c == 5)
		{
			B->for_permotion(So, 2);
		}
		if (p.c == 6)
		{
			B->for_permotion(So, 3);
		}
	}
}
void Chess::display_image(sf::RenderWindow& w, sf::Vector2f V, sf::Vector2f scale, string name)
{
	sf::Texture temp;

	if (!temp.loadFromFile(name))
	{
		throw("Unable to load img");
	}

	sf::Sprite s(temp);
	s.setScale(V.x,V.y);

	s.setPosition(scale.y, scale.x); 
	w.draw(s);	
}
bool Chess::Valid_Source(Player* Ap, Position P)
{
	int dim = B->get_Dimension();
	if (P.r < 0 || P.r >= dim || P.c < 0 || P.c >= dim)
		return false;
	Peice* p = B->get_peice_at(P);
	return (p != nullptr && (p->get_Clr() == Ap->get_Color()));
}
bool Chess::Valid_Destination(Player* Ap, Position P)
{
	int dim = B->get_Dimension();
	if (P.r < 0 || P.r > dim || P.c < 0 || P.c > dim)
		return false;
	Position i = getsourcepoint();
	if (P.r == i.r && P.c == i.c)
		return false;
	Peice* p = B->get_peice_at(P);
	return (p == nullptr || p->get_Clr() != Ap->get_Color());
}
void Chess::Hilight(bool**& F,sf::RenderWindow & w,Position Sc,int turn)
{
	int dim = B->get_Dimension();
	F = new bool* [dim] {};
	for (int i = 0; i < dim; i++)
	{
		F[i] = new bool[dim] {};
	}
	for (int i = 0; i < dim; i++)
	{
		for (int k = 0; k < dim; k++)
		{
			if (((B->get_peice_at(Sc)->Peice_legal(*B, Sc, {i,k}) && (Valid_Destination(Ps[turn], {i,k})))&& (!Self_check_imp(B, 8, turn, Sc, { i,k }, Ps, w))) )
				F[i][k] = true;
			else
				F[i][k] = false;
		}
	}
}
void Chess::drawhigli( bool** F, sf::RenderWindow& window, sf::RectangleShape& r)
{
	int a = 100;
	int dim = B->get_Dimension();

	int ro = 0, c = 0;
	for (int i = 0; i < dim; i++)
	{
		for (int k = 0; k < dim; k++)
		{
			ro = i + 1;
			c = k + 4;
			if (F[i][k] == true )
			{
				if (i == Sou.r && k == Sou.c)
				{
					sf::RectangleShape border(sf::Vector2f(a, a));
					border.setFillColor(sf::Color::Transparent);
					border.setOutlineColor(sf::Color::Yellow);
					border.setOutlineThickness(5);
					border.setPosition(sf::Vector2f(c * a, ro * a));
					window.draw(border);
					B->get_peice_at({ i,k })->print(window, ro, c);
				}
				else if (B->get_peice_at({ i,k }) != nullptr)
				{
					sf::RectangleShape border(sf::Vector2f(a,a));
					border.setFillColor(sf::Color::Transparent);
					border.setOutlineColor(sf::Color::Green);
					border.setOutlineThickness(5);
					border.setPosition(sf::Vector2f(c*a, ro*a));
					B->box(window, r, ro , c , 2, a, a);
					window.draw(border);
					B->get_peice_at({ i,k })->print(window, ro, c);

				}
				else
				{
					sf::RectangleShape border(sf::Vector2f(a,a));
					border.setFillColor(sf::Color::Transparent);
					border.setOutlineColor(sf::Color::Green);
					border.setOutlineThickness(5);
					border.setPosition(sf::Vector2f(c * a, ro * a));
					B->box(window, r, ro , c , 1, a, a);
					window.draw(border);
				}
			}
		}
	}
}
void Chess::delete_bool(bool**&F)
{
	for (int i = 0; i < B->get_Dimension(); i++)
	{
		delete[] F[i];
	}
	delete[]F;
}
void Chess::ReplayArray(vector<Position>& B, int& count)
{
	B.push_back(Sou);
	B.push_back(Des);
	count += 2;
}
bool Chess::redo(vector<Position>& C, sf::RenderWindow& window, int count, int& count2,sf::RectangleShape& r)
{
	if (((count2)) <= C.size() && count2>1)
	{
		Sou = C[(count-count2)  ];
		Des = C[(count-count2) + 1 ];
		move();
		count2 -= 2;
		return true;
	}
	return false;
}
void Chess::get_position(Position& a, sf::RenderWindow& window)
{
	getRowColbyLeftClick(a.r, a.c, window);
	a.r /= 100;
	a.c /= 100;
}
Position Chess::findking(Board* B, int dim, Player* Ps, sf::RenderWindow& w)
{
	int dimi = 8;
	char ch = ' ';
	if (Ps->get_Color() == WHITE)
		ch = 'K';
	else if (Ps->get_Color() == BLACK)
		ch = 'k';
	for (int i = 0; i < dimi; i++)
	{
		for (int j = 0; j < dimi; j++)
		{
			if (B->get_peice_at({ i,j }) != nullptr)
			{
				char d = B->get_peice_at({ i,j })->get_sym();
				if (d == ch)
				{
					Position R{};
					R.r = i, R.c = j;
					return R;
				}
			}
		}
	}
}
bool Chess::IfCapture(Board* Bo, Position Sr, Position De)
{
	if (Bo->get_peice_at(De) == nullptr)
	{
		return false;
	}
	if (Bo->get_peice_at(Sr)->get_Clr() != Bo->get_peice_at(De)->get_Clr())
		return true;

	return false;
}
bool Chess::Isvaildpath(Board* B, Position So, Position De, Player* Ps, sf::RenderWindow& w,int turn)
{
	if (B->get_peice_at(So) == nullptr)
		return false;
	return Valid_Source(Ps, So) && B->get_peice_at(So)->Peice_legal((*B), So, De);
}
bool Chess::checkpoint(Board* B, int dim, Player** Ps, Position Sc, Position Dc, int turn, sf::RenderWindow& w)
{
	Position R{}, S{};
	turn_changing(turn);
	R = findking(B, dim, Ps[turn], w);
	if (R.r == Sc.r && R.c == Sc.c)
	{
		R = Dc;
	}
	turn_changing(turn);
	for (int i = 0; i < dim; i++)
	{
		for (int k = 0; k < dim; k++)
		{
			if (Isvaildpath(B, { i,k }, R, Ps[turn], w,turn))
			{
				is_check = true;
				return true;
			}
		}
	}
	is_check = false;
	return false;
}
bool Chess::selfchexk(Board* B, Player** P, int turn, Position Sc, Position Dc, int dim, sf::RenderWindow& w)
{
	turn_changing(turn);
	return (checkpoint(B, dim, P, Sc, Dc, turn, w));
}
bool Chess::Ste_Make(Board* B, Player** P, int turn, Position Sc, Position Dc, int dim, sf::RenderWindow& w)
{
	if (!Valid_move_remain(turn, w))
	{
		is_stale_chek = true;
		return true;
	}
	is_stale_chek = false;
	return false;
}
bool Chess::Self_check_imp(Board* B, int dim, int turn, Position Sc, Position Dc, Player** Ps, sf::RenderWindow& w)
{
	Board* J{};
	J = new Board(1);


	for (int l = 0; l < dim; l++)
	{
		for (int f = 0; f < dim; f++)
		{
			if (B->get_peice_at({ l, f }) != nullptr)
				J->set_peice_at(B->get_peice_at({ l,f }), { l,f });
			else
				J->set_peice_at(nullptr, { l,f });
		}
	}


	J->set_peice_at(J->get_peice_at({ Sc.r,Sc.c }), { Dc.r,Dc.c });
	J->set_peice_at(nullptr, { Sc.r,Sc.c });
	if (selfchexk(J, Ps, turn, Sc, Dc, dim, w))
	{
		is_self_ckeck = true;
		return true;
	}
	is_self_ckeck = false;
	return false;
}
bool Chess::Valid_move_remain(int turn,sf::RenderWindow & w)
{
	bool **F{};
	bool valid_sou{}, valid_des{};
	Position s{}, D{}, p{};
	int dim = B->get_Dimension();
	for (int h = 0; h < dim; h++)
	{
		for (int f = 0; f < dim; f++)
		{
			if (Valid_Source(Ps[turn], { h,f }))
			{
				s = { h,f };
				Hilight(F, w,s,turn);
				for (int d = 0; d < dim; d++)
				{
					for (int r = 0; r < dim; r++)
					{
						if (F[d][r] != false)
							return true;
					}
				}
			}
			else
				continue;
				
		}
	}
	return false;
}
bool Chess::is_check_remain(Position p1,Position p2,int turn, sf::RenderWindow& w)
{
	if (Self_check_imp(B, 8, turn, p1, p2, Ps, w))
	{
		return true;
	}
	return false;
}
bool Chess::ckeckmakkkk(Board* B, int dim, int turn, Position Sc, Position Dc, Player** p, sf::RenderWindow& w)
{
	if (checkpoint(B, 8, Ps, {}, {}, turn, w))
	{
		turn_changing(turn);
		if (!Valid_move_remain(turn,w))
		{
			is_cake_mate = true;
			return false;
		}
		is_cake_mate = false;
		return true;
	}
	is_cake_mate = false;
	return false;
}
void Chess::turn_changing(int& a)
{
	if (a == 1)
		a = 0;
	else if (a == 0)
		a = 1;
}
void Chess::Turn_mess(Player* Ap,sf::RenderWindow & w)
{
	display_text(w,Ap->get_name()+ " Now Its your Turn__!", 10, 3);
}
void Chess::Reply2(Board* B, vector<Position> C, int count, int dimesion, int turn, string finames,  sf::RectangleShape& r)
{
	sf::RenderWindow win(sf::VideoMode(1900, 1000), "Reply Game");
	std::ifstream rdr("Text1.txt");
	Chess C1(win,rdr,r);
	for (int i = 0; i + 1 < count; i += 2)
	{
		C1.Sou = C[i];
		C1.Des = C[i + 1];

		C1.move();
		C1.B->draw_board(win,r);
		C1.draw_peices(win);
		win.display();

	}
	C1.display_text(win, "Now for continue Enter any key:", 10, 3);
}
void Chess::resume(Board* b, int dim, Player** P, string filename)
{
	Writingonfile(b, dim, P, filename);
	system("cls");
	exit(-1);
}
void Chess::Writingonfile(Board* B, int dimension, Player** Ps, string filname)
{

	std::ofstream wr(filname);
	for (int t = 0; t < 2; t++)
	{
		wr << Ps[t]->get_name() << "\n";
	}wr << "\n\n";
	wr << dimension << "\n"; wr << "\n\n";
	for (int i = 0; i < dimension + 4; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			if (B->get_peice_at({ i,j }) != nullptr)
				wr << B->get_peice_at({ i,j })->get_sym1() << "  ";
			else
				wr << "-" << "  ";
		}
		if (i == dimension - 1)
			wr << "\n\n";
		wr << "\n";
	}
	wr << "\n\n";

}
bool Chess::is_castling(Position R,int scount,int &count,vector<Position> &Rep,Position kd,sf::RenderWindow& w)
{
	int dim = B->get_Dimension();
	int turn = Turn;
	Pawn p;
	Position K = findking(B,dim,Ps[turn],w );
	if (kd.r == R.r)
	{
		turn_changing(turn);
		if (!checkpoint(B, dim, Ps, R, kd, turn, w))
		{
			turn_changing(turn);
			Position P = { kd.r,kd.c - 2 }, p1 = { kd.r,kd.c - 2 };
			char ch = B->get_peice_at(R)->get_sym1();
			bool posible = p.Ishorizontalpathclear(*B, K, R);
			if (R.c - kd.c == 2 && (ch == 'r' || ch == 'R') && (posible))
			{
				if (!selfchexk(B, Ps, turn, K, {K.r,K.c+2}, B->get_Dimension(), w))
				{
					Sou = K, Des = { K.r,K.c + 2 };
					ReplayArray(Rep, count);
					move();
					Sou = R, Des = kd;
					return true;
				}
				
			}
			else if ((R.c - kd.c == -2) && (ch == 'r' || ch == 'R') && (posible))
			{
				if (!selfchexk(B, Ps, turn, K, { K.r,K.c - 3 },dim, w))
				{
					Sou = K, Des = { K.r,K.c - 3 };
					ReplayArray(Rep, count);
					move();
					Sou = R, Des = kd;
					return true;
				}
			}

		}
	}

	return false;
	/*if (((kd.r == K.r) && (kd.c - K.c == 2 && B->get_peice_at({kd.r+1,kd.c})->get_sym1()=='r' || k.c - K.c == -1)) && (p.Isverticalpathclear(*B, k, K)))
	{
		if (!checkpoint(B, B->get_Dimension(),Ps,k,K,turn,w))
		{
			turn_changing(turn);
			if (k.c - K.c == 4)
			{
				if (!selfchexk(B, Ps, turn, k, { k.r,k.c - 2 }, B->get_Dimension(), w))
				{
					ReplayArray(Rep, count);
					scount += 2;
					B->postion_change(k, { k.r,k.c - 2 });
				    kd = { K.r,K.c - 3 };
					return true;
				}
			}
			else
			{
				if (!selfchexk(B, Ps, turn, k, { k.r,k.c + 2 }, B->get_Dimension(),w))
				{
					ReplayArray(Rep,count);
					scount += 2;
					B->postion_change(k, { k.r,k.c + 2 });
					kd = { K.r,K.c + 3 };
					return true;
				}
			}
		}
	}*/
}



// 235, 122, 8*8
