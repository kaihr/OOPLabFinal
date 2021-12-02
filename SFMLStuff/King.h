#pragma once
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Constants.h"

class King : public Piece {
private:
	sf::Texture _texture;
public:
	King(int row = 0, int col = 0, bool isWhite = true) : Piece(row, col, isWhite)
	{
		if (_isWhite)
			_sprite.setTexture(TextureManager::getTexture(WHITE_KING));
		else
			_sprite.setTexture(TextureManager::getTexture(BLACK_KING));

		_sprite.setPosition(_col * CELL_LENGTH, _row * CELL_LENGTH);
	}

	virtual bool validCell(int nextRow, int nextCol, Piece *pieces[BOARD_SIZE][BOARD_SIZE]) {
		return abs(nextRow - _row) <= 1 && abs(nextCol - _col) <= 1;
	}
};
