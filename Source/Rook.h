#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Constants.h"

class Rook : public Piece {
public:
	Rook(int row = 0, int col = 0, bool isWhite = true, bool enPassant = false, int hasMoved = 0) : 
		Piece(row, col, isWhite, Piece::Type::ROOK, enPassant, hasMoved)
	{
		if (_isWhite)
			_sprite.setTexture(TextureManager::getTexture(PIECES::WHITE_ROOK));
		else
			_sprite.setTexture(TextureManager::getTexture(PIECES::BLACK_ROOK));

		_sprite.setPosition(_col * CELL_LENGTH, _row * CELL_LENGTH);
	}

	virtual bool validCell(int nextRow, int nextCol, Piece *pieces[BOARD_SIZE][BOARD_SIZE]) {
		if (!(nextRow == _row || nextCol == _col))
			return false;
		
		int diff = 1;
		if (_col > nextCol)
			diff = -1;

		for (int i = _col; i != nextCol; i += diff) {
			if (i == _col)
				continue;

			if (pieces[_row][i])
				return false;
		}

		diff = 1;
		if (_row > nextRow)
			diff = -1;

		for (int i = _row; i != nextRow; i += diff) {
			if (i == _row)
				continue;

			if (pieces[i][_col])
				return false;
		}
		if (pieces[nextRow][nextCol])
		{
			if (pieces[nextRow][nextCol]->isWhite() == this->_isWhite)
			{
				return false;
			}
		}
		return true;
	}
};
