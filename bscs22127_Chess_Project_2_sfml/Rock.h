#pragma once
class Peice;

class Rock : public Peice
{
public:
	void set_vector_posi(sf::Vector2f& v)override
	{
		set_posi(v);
	}
	Rock() = default;
	Rock(Position P_p, Color clr, Board* B, char sym = char(-37));
	bool Peice_legal(Board B, Position Sc, Position Dc)override;
	void print(sf::RenderWindow& window, int column, int row)override;
};
