#pragma once
#include "Piece.h"

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
	bool validCell(int nextRow, int nextCol, Piece* pieces[BOARD_SIZE][BOARD_SIZE]) {
		if (nextRow >= BOARD_SIZE || nextCol >= BOARD_SIZE || nextRow < 0 || nextCol < 0)
			return false;
		if (nextRow == _row + 1 || nextRow == _row - 1)
		{
			if (nextCol == _col + 2 || nextCol == _col - 2)
				return 1;
		}
		if (nextRow == _row + 2 || nextRow == _row - 2)
		{
			if (nextCol == _col + 1 || nextCol == _col - 1)
				return 1;
		}
		return 0;
	}
};