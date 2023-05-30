#pragma once
#include"Header.h"
class Board;
class Peice;
class Player;

class Chess
{
protected:
	Position Sou;
	Position Des;
	int Turn;
	Player* Ps[2];
	Board* B;
	bool is_right_source{};
	bool is_right_des{};
	bool is_cake_mate{};
	bool is_self_ckeck{};
	bool is_stale_chek{};
	bool is_check{};
	sf::Sprite s;
	sf::Texture t;
	sf::Time countdownTime;
	sf::Clock clock;
	bool Is_hilight{};
public:
	bool Self_check_imp(Board* B, int dim, int turn, Position Sc, Position Dc, Player** Ps, sf::RenderWindow& w);
	bool dispaly_time(int row, int col, sf::RenderWindow&, sf::Time);
	void display_back(sf::RenderWindow& window);
	void display_image(sf::RenderWindow& w, sf::Vector2f scale, sf::Vector2f V, string name);
	void get_position(Position& a, sf::RenderWindow& window);
	bool IsCastling(Position F);
	void Reply2(Board* B, vector<Position> C, int count, int dimesion, int turn, string finames, sf::RectangleShape& r);

	Position findking(Board* B, int dim, Player* Ps, sf::RenderWindow& w);
	bool ckeckmakkkk(Board* B, int dim, int turn, Position Sc, Position Dc, Player** p, sf::RenderWindow& w);
	void display_text(sf::RenderWindow& window, string txt, int row, int col);
	void Print_peices(sf::RenderWindow& window, char sym, Position P);
	bool Ste_Make(Board* B, Player** P, int turn, Position Sc, Position Dc, int dim, sf::RenderWindow& w);
	bool Isvaildpath(Board* B, Position So, Position De, Player* Ps, sf::RenderWindow& w, int turn);
	bool selfchexk(Board* B, Player** P, int turn, Position Sc, Position Dc, int dim, sf::RenderWindow& w);
	void Hilight(bool**& F, sf::RenderWindow& w, Position Sc, int turn);
	void drawhigli(bool** F, sf::RenderWindow& window, sf::RectangleShape& r);
	void delete_bool(bool**& F);
	bool checkpoint(Board* B, int dim, Player** Ps, Position Sc, Position Dc, int turn, sf::RenderWindow& w);
	void Turn_mess(Player* Ap, sf::RenderWindow& w);
	void turn_change();
	void turn_changing(int& a);
	void Select_for_premoted_pawn(Position So, Position De, sf::RenderWindow& w);
	bool IsExit(Position F, sf::RenderWindow& w);


	void static getRowColbyLeftClick_1(int& rpos, int& cpos, sf::RenderWindow& window);
	Chess()=default;
	void Play();



	Position getsourcepoint() { return Sou; }
	

	
	bool Valid_Source(Player* Ap, Position P);
	bool Valid_Destination(Player* Ap, Position P);
	void IsExit(Position F);
	void replaystart(int**& C, Player** P, int count, int& scount);

	void Removedrawhigli(Board B, bool**& F, int dim, Position Sc, int col1, int col2);
	void ReplayArray(vector<Position>& B, int& count);
	void replay(vector<Position> &C, int count, int scount, Position& Sc, Position& Dc);
	void replaystart(vector<Position> C, Player** P, int count, int& scount);
	bool undo(vector<Position>& C, sf::RenderWindow& window, int count,int &, sf::RectangleShape& r);
	bool redo(vector<Position>& C, sf::RenderWindow& window, int count, int& count2, sf::RectangleShape& r);
	bool Redomess(Position Sc);
	
	
	bool IfCapture(Board* Bo, Position Sr, Position De);
	
	void  hilghiking(Board* B, int dim, Player** P, int turn, sf::RenderWindow& window, sf::RectangleShape& r);

	void initReplayArray(int**& B, int count);
	bool Replaymess(Position Sc);
	
	void Writingonfile(Board* B, int dimension, Player** Ps, string filname);
	void resume(Board* b, int dim, Player** P, string filename);
	bool Isreplay2(Position F);


	bool is_castling(Position r, int scount, int& count ,vector<Position>& Rep, Position r2, sf::RenderWindow& w);
	bool resumechk(Position Sc);
	void Play(sf::RenderWindow& window, sf::RectangleShape& r);
	void dispaly_time(int start);

	void static getRowColbyLeftClick(int& rpos, int& cpos, sf::RenderWindow& window);
	bool select_position(sf::RenderWindow& window, int& count1, int& count2, vector<Position>& Rep, bool** King_bool, sf::RectangleShape& r);
	void move();


	void draw_peices(sf::RenderWindow &w);
	Chess(sf::RenderWindow& window, ifstream& rdr, sf::RectangleShape& r);
	bool Valid_move_remain(int turn, sf::RenderWindow&);
	bool is_check_remain(Position p1, Position P2, int turn, sf::RenderWindow& w);

	
};
