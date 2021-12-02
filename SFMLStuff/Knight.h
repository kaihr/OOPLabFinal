#pragma once
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Constants.h"

class Knight : public Piece {
public:
	Knight(int row = 0, int col = 0, bool isWhite = true) : Piece(row, col, isWhite)
	{
		if (_isWhite)
			_sprite.setTexture(TextureManager::getTexture(WHITE_KNIGHT));
		else
			_sprite.setTexture(TextureManager::getTexture(BLACK_KNIGHT));

		_sprite.setPosition(_col * CELL_LENGTH, _row * CELL_LENGTH);
	}

	virtual bool validCell(int nextRow, int nextCol, Piece* pieces[BOARD_SIZE][BOARD_SIZE]) {
		return nextRow != _row && nextCol != _col && (abs(nextRow - _row) + abs(nextCol - _col) == 3);
	}
};
