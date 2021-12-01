#pragma once
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Constants.h"

class Queen : public Piece {
private:
	sf::Texture _texture;
public:
	Queen(int row = 0, int col = 0, bool isWhite = true) : Piece(row, col, isWhite)
	{
		if (_isWhite)
			_texture = TextureManager::getTexture(WHITE_QUEEN);
		else
			_texture = TextureManager::getTexture(BLACK_QUEEN);

		_sprite.setTexture(_texture);
		_sprite.setPosition(_col * CELL_LENGTH, _row * CELL_LENGTH);
	}

	virtual bool validCell(int nextRow, int nextCol, Piece *pieces[BOARD_SIZE][BOARD_SIZE]) {
		return (nextRow == _row || nextCol == _col) || (abs(nextRow - _row) == abs(nextCol - _col));
	}
};

