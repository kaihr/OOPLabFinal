#include "King.h"

bool King::validCell(int nextRow, int nextCol, Piece* pieces[BOARD_SIZE][BOARD_SIZE])
{
	// Castling queen side
	if (!_hasMoved && _row == nextRow && nextCol == _col - 2) {
		if ((pieces[_row][0]
			&& !pieces[_row][0]->hasMoved())
			&& !pieces[_row][_col - 1]
			&& !pieces[_row][_col - 2]
			&& !pieces[_row][_col - 3]) {
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

	return true;
}

bool King::validAndNotInCheck(int nextRow, int nextCol, Piece* pieces[BOARD_SIZE][BOARD_SIZE])
{
	if (nextRow == _row && abs(nextCol - _col) == 2 
		&& pieces[_row][_col]->validCell(nextRow, nextCol, pieces)) {

		bool ans = true;

		int delta = -1;
		if (_col < nextCol)
			delta = 1;

		int pathCol = _col;

		while (true) {
			std::swap(pieces[_row][_col], pieces[nextRow][pathCol]);
			if (putKingInDanger(nextRow, pathCol, nextRow, pathCol, pieces))
				ans = false;
			std::swap(pieces[_row][_col], pieces[nextRow][pathCol]);
			if (pathCol == nextCol)
				break;
			pathCol += delta;
		}

		return ans;
	}

	return Piece::validAndNotInCheck(nextRow, nextCol, pieces);
}