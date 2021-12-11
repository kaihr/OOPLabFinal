#pragma once
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Constants.h"

class King : public Piece {
private:
	sf::Texture _texture;
public:
	King(int row = 0, int col = 0, bool isWhite = true) : Piece(row, col, isWhite, Piece::Type::KING)
	{
		if (_isWhite)
			_sprite.setTexture(TextureManager::getTexture(PIECES::WHITE_KING));
		else
			_sprite.setTexture(TextureManager::getTexture(PIECES::BLACK_KING));

		_sprite.setPosition(_col * CELL_LENGTH, _row * CELL_LENGTH);
	}

	virtual bool validCell(int nextRow, int nextCol, Piece *pieces[BOARD_SIZE][BOARD_SIZE]) {
		// Castling queen side
		if (!_hasMoved && _row == nextRow && nextCol == _col - 2) {
			if ((pieces[_row][0]
				&& !pieces[_row][0]->hasMoved())
				&& !pieces[_row][_col - 1] && !pieces[_row][_col - 2]) {
				return true;
			}
		}

		// Castling king side
		if (!_hasMoved && _row == nextRow && nextCol == _col + 2) {
			if ((pieces[_row][7]
				&& !pieces[_row][7]->hasMoved())
				&& !pieces[_row][_col + 1]
				&& !pieces[_row][_col + 2]) {
				return true;
			}
		}

		if (!(abs(nextRow - _row) <= 1 && abs(nextCol - _col) <= 1))
			return false;

		for (int i = 0; i < BOARD_SIZE; ++i)
			for (int j = 0; j < BOARD_SIZE; ++j) {
				if (i == nextRow && j == nextCol)
					continue;

				if (!pieces[i][j])
					continue;

				if (pieces[i][j]->isWhite() == _isWhite)
					continue;

				if (pieces[i][j]->type() != Piece::Type::KING) {
					if(pieces[i][j]->validCell(nextRow, nextCol, pieces))
						return false;
				}
				else if (abs(i - nextRow) <= 1 && abs(j - nextCol) <= 1) {
						return false;
				}
			}

		return true;
	}
public:
	int enPassant()
	{
		return 0;
	}
};
