#pragma once
#include <SFML/Graphics.hpp>

#include "Utility.h"

class Piece : public sf::Drawable, public sf::Transformable 
{
protected:
	int _row, _col;
	bool _selected;
	bool _isWhite;
	bool _isAlive;
	sf::Sprite _sprite;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(_sprite, states);
	}

public:
	Piece(int row = 0, int col = 0) : _row(row), _col(col), _selected(false), _isWhite(false), _isAlive(true) {}

	virtual bool validCell(int nextRow, int nextCol, Piece *pieces[BOARD_SIZE][BOARD_SIZE]) {	return true;	}

	Piece* handleInput(const sf::Event& event, Piece* pieces[BOARD_SIZE][BOARD_SIZE]);

	void moveWithMouse(const sf::Window &window)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		mousePos.x -= CELL_LENGTH / 2;
		mousePos.y -= CELL_LENGTH / 2;

		_sprite.setPosition(sf::Vector2f(mousePos));
	}
};