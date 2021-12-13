#include "Pawn.h"

#include <iostream>

bool Pawn::validCell(int nextRow, int nextCol, Piece* pieces[BOARD_SIZE][BOARD_SIZE]) 
{
	if (_col == nextCol && _row + _positiveDirection == nextRow) {
		if (!pieces[nextRow][nextCol])
			return true;
		return false;
	}

	if (_col == nextCol && _row + 2 * _positiveDirection == nextRow) {
		if (!pieces[nextRow - _positiveDirection][nextCol] && !pieces[nextRow][nextCol] && !_hasMoved)
			return true;
		return false;
	}

	if (_row + _positiveDirection == nextRow && (_col - 1 == nextCol || _col + 1 == nextCol)) {
		if (pieces[nextRow][nextCol])
			return true;
		if (_isWhite && _row == 3)
		{
			if (pieces[3][nextCol] && pieces[3][nextCol]->type() == Type::PAWN && pieces[3][nextCol]->isWhite() != _isWhite && pieces[3][nextCol]->hasMoved() == 1)
			{
				return true;
			}
		}
		if (!_isWhite && _row == 4)
		{
			if (pieces[4][nextCol] && pieces[4][nextCol]->type() == Type::PAWN && pieces[4][nextCol]->isWhite() != _isWhite && pieces[4][nextCol]->hasMoved() == 1)
			{
				return true;
			}
		}
	}
	return false;
}

/*
Piece* Pawn::handleInput(const sf::Event& event, Piece* pieces[BOARD_SIZE][BOARD_SIZE])
{
	// TO-DO: En Passant

	return Piece::handleInput(event, pieces);
}
*/
