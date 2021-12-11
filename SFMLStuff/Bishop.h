#pragma once
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Constants.h"

class Bishop : public Piece {
public:
	Bishop(int row = 0, int col = 0, bool isWhite = true) : Piece(row, col, isWhite, Piece::Type::BISHOP)
	{
		if (_isWhite)
			_sprite.setTexture(TextureManager::getTexture(PIECES::WHITE_BISHOP));
		else
			_sprite.setTexture(TextureManager::getTexture(PIECES::BLACK_BISHOP));

		_sprite.setPosition(_col * CELL_LENGTH, _row * CELL_LENGTH);
	}

	virtual bool validCell(int nextRow, int nextCol, Piece *pieces[BOARD_SIZE][BOARD_SIZE]) {
		if (abs(nextRow - _row) != abs(nextCol - _col))
			return false;

		if (nextRow > _row)
		{
			if (nextCol > _col)
			{
				int j = _col + 1;
				for (int i = _row + 1; i < nextRow; i++)
				{
					if (pieces[i][j])
						return false;
					j++;
				}
			}
			else
			{
				int j = _col - 1;
				for (int i = _row + 1; i < nextRow; i++)
				{
					if (pieces[i][j])
						return false;
					j--;
				}
			}
		}
		else
		{
			if (nextCol == _col)
			{
				int j = _col;
				for (int i = _row - 1; i > nextRow; i--)
				{
					if (pieces[i][j])
						return false;
				}
			}
			else if (nextCol > _col)
			{
				int j = _col + 1;
				for (int i = _row - 1; i > nextRow; i--)
				{
					if (pieces[i][j])
						return false;
					j++;
				}
			}
			else
			{
				int j = _col - 1;
				for (int i = _row - 1; i > nextRow; i--)
				{
					if (pieces[i][j])
						return false;
					j--;
				}
			}
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
public:
	int enPassant()
	{
		return 0;
	}
};

