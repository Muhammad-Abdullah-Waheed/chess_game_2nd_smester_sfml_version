#include<iostream>
#include<SFML/Graphics.hpp>
#include"Chess.h"
#include<fstream>



using namespace std;
void draw(sf::RenderWindow& window,sf::RectangleShape&r)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((i + j) % 2 == 0)
			{
				r.setFillColor(sf::Color::Black);
				r.setPosition(j * 100, i * 100);
				window.draw(r);
			}
			else
			{
				r.setFillColor(sf::Color::Yellow);
				r.setPosition(j * 100, i * 100);
				window.draw(r);
			}
		}
	}
}
int main()
{
	//sf::Vector2f v;
	//v.x = 100;
	//v.y = 100;
	//sf::RenderWindow win(sf::VideoMode(800, 800), "rectangle");
	//sf::RectangleShape r;
	////r.setFillColor(sf::Color::White);
	//r.setSize(v);
	//r.setPosition(0, 0);
	//while (win.isOpen())
	//{
	//	sf::Event e;
	//	while (win.pollEvent(e))
	//	{
	//		if (e.type == e.Closed)
	//		{
	//			win.close();
	//		}
	//	}
	//	win.clear();
	//	draw(win, r);
	//	win.display();
	//}
	


	//r.setScale(1000, 1000);
	/*while (win.isOpen())
	{
		sf::Event e;
		while (win.pollEvent(e))
		{
			if (e.type == e.Closed)
			{
				win.close();
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (r.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(win))))
			{
				break;
			}
		}
		win.clear();
		win.draw(r);
		win.display();

	}
	while (win.isOpen())
	{
		sf::Event e;
		while (win.pollEvent(e))
		{
			if (e.type == e.Closed)
			{
				win.close();
			}
		}
		win.clear();
		draw(win, r);
		win.display();

	}*/



	{
		string name{};

		{
			Chess E;
			sf::RenderWindow win(sf::VideoMode(1900, 1000), "Load Game !!");
			sf::Sprite s;
			sf::Texture t;
			if (!t.loadFromFile("B_2.jpeg"))
			{
				cout << "Unable to load ___!";
			}
			Position P{};

			s.setTexture(t);
			s.setScale(1, 1);
			s.setPosition(0, 0);

			while (win.isOpen())
			{
				sf::Event e;
				while (win.pollEvent(e))
				{
					if (e.type == e.Closed)
					{
						win.close();
					}


					win.draw(s);
					E.display_text(win, "CHESS GAME BY  _______  MUHAMMAD ABDULLAH WAHEED ", 4, 1);
					E.display_text(win, "[ 1 ]   Start new game. ", 4, 2);
					E.display_text(win, "[ 2 ]   Laod game. ", 4, 3);
					E.display_text(win, "[ 3 ]   Exit. ", 4, 4);
					win.display();

					if (e.type == e.MouseButtonPressed)
					{
						E.getRowColbyLeftClick(P.c, P.r, win);
						P.c /= 100, P.r /= 100;
						if (P.r == 4 && P.c == 2)
							name = "Text1.txt", win.close();
						else if (P.r == 4 && P.c == 3)
							name = "Resume.txt", win.close();
						else if (P.r == 4 && P.c == 4)
							exit(-1);
					}

				}


			}
		}
		ifstream rdr(name);


		sf::RectangleShape r;
		sf::Vector2f v;
		v.x = 100;
		v.y = 100;
		r.setSize(v);
		sf::RenderWindow window(sf::VideoMode(1900, 1000), "Chess Game By MUHAMMAD ABDULLAH WAHEED");
		Chess C(window, rdr, r);
		C.Play(window, r);

	}
	return 0;
}


