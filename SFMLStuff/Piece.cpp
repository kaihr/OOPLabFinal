#include <iostream>
#include <sstream>

#include "Piece.h"

bool Piece::putKingInDanger(int fromRow, int fromCol, int toRow, int toCol, Piece* pieces[BOARD_SIZE][BOARD_SIZE])
{
	bool curColor = pieces[fromRow][fromCol]->isWhite();

	Piece* preTo = pieces[toRow][toCol];

	if ((fromRow != toRow) || (fromCol != toCol)) {
		pieces[toRow][toCol] = pieces[fromRow][fromCol];
		pieces[fromRow][fromCol] = NULL;
	}

	int kingRow = -1;
	int kingCol = -1;

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (pieces[i][j]
				&& pieces[i][j]->type() == Piece::Type::KING
				&& pieces[i][j]->isWhite() == curColor) {
				kingRow = i;
				kingCol = j;
			}

	bool ans = false;

	for(int i = 0; i < BOARD_SIZE; i++)
		for(int j = 0; j < BOARD_SIZE; j++)
			if (pieces[i][j]
				&& pieces[i][j]->isWhite() != curColor
				&& pieces[i][j]->validCell(kingRow, kingCol, pieces)) {
				ans = true;
			}

	if ((fromRow != toRow) || (fromCol != toCol)) {
		pieces[fromRow][fromCol] = pieces[toRow][toCol];
		pieces[toRow][toCol] = preTo;
	}

	return ans;
}

bool Piece::validAndNotInCheck(int nextRow, int nextCol, Piece* pieces[BOARD_SIZE][BOARD_SIZE])
{
	return validCell(nextRow, nextCol, pieces) && !putKingInDanger(_row, _col, nextRow, nextCol, pieces);
}

std::string Piece::toString() const
{
	std::stringstream ss;
	ss << _row << " " << _col << " " << _isWhite << " " << _enPassant << " " << _hasMoved << " " << (int)_type;

	return ss.str();
}
