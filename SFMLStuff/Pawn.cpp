#include "Pawn.h"

#include <iostream>

bool Pawn::validCell(int nextRow, int nextCol, Piece* pieces[BOARD_SIZE][BOARD_SIZE]) {
	if (nextRow == _row + this->_positiveDirection)
	{
		if ((nextCol == _col + 1 ) || (nextCol == _col - 1))
		{
			if (pieces[nextRow][nextCol]->isWhite() != this->_isWhite)
			{
				this->_hasMoved = 1;
				return true;
			}
		}
		else
		{
			if (nextCol == _col)
				if (!pieces[nextRow][nextCol])
				{
					this->_hasMoved = 1;
					return true;
				}
		}
	}	
	if (nextRow == _row + 2 * this->_positiveDirection)
		if (this->_hasMoved == 0)
			return true;
	return false;
}

Piece* Pawn::handleInput(const sf::Event& event, Piece* pieces[BOARD_SIZE][BOARD_SIZE])
{
	// TO-DO: En Passant

	return Piece::handleInput(event, pieces);
}
