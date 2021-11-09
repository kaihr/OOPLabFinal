#pragma once
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Constants.h"

class Knight : public Piece {
private:
	sf::Texture _texture;
public:
	Knight(int row = 0, int col = 0, bool isWhite = true)
	{
		_row = row;
		_col = col;
		_isWhite = isWhite;

		if (_isWhite)
			_texture.loadFromFile("Assets\\white_knight.png");
		else
			_texture.loadFromFile("Assets\\black_knight.png");


		_sprite.setTexture(_texture);

		_sprite.setPosition(_col * CELL_LENGTH, _row * CELL_LENGTH);
	}

	virtual bool validCell(int nextRow, int nextCol, Piece* pieces[BOARD_SIZE][BOARD_SIZE]) {
		if (nextRow >= BOARD_SIZE || nextCol >= BOARD_SIZE || nextRow < 0 || nextCol < 0)
			return 0;
		return nextRow != _row && nextCol != _col && abs(nextRow - _row) + abs(nextCol - _col) == 3;
	}
};
