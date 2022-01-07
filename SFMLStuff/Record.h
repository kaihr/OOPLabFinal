#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Piece.h"
#include "Pawn.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "ChessGame.h"

class Record{
private:
	std::vector <std::vector <std::string>> _piecesHistory;
public:
	static char pieceToChar(Piece* piece) {
		if (!piece) return ' ';
		if (piece->type() == Piece::Type::BISHOP)
			return 'b' - piece->isWhite() * 32;
		if (piece->type() == Piece::Type::PAWN)
			return 'p' - piece->isWhite() * 32;
		if (piece->type() == Piece::Type::ROOK)
			return 'r' - piece->isWhite() * 32;
		if (piece->type() == Piece::Type::KNIGHT)
			return 'n' - piece->isWhite() * 32;
		if (piece->type() == Piece::Type::QUEEN)
			return 'q' - piece->isWhite() * 32;
		if (piece->type() == Piece::Type::KING)
			return 'k' - piece->isWhite() * 32;
		return ' ';
	}

	static Piece* charToPiece(char piece, int i, int j) {
		if (piece == 'p') return new Pawn(i, j, false);
		else if (piece == 'P') return new Pawn(i, j);
		else if (piece == 'r') return new Rook(i, j, false);
		else if (piece == 'R') return new Rook(i, j);
		else if (piece == 'n') return new Knight(i, j, false);
		else if (piece == 'N') return new Knight(i, j);
		else if (piece == 'b') return new Bishop(i, j, false);
		else if (piece == 'B') return new Bishop(i, j);
		else if (piece == 'q') return new Queen(i, j, false);
		else if (piece == 'Q') return new Queen(i, j);
		else if (piece == 'k') return new King(i, j, false);
		else if (piece == 'K') return new King(i, j);
		return NULL;
	}

public:

	Record(){
		_piecesHistory.clear();
	}

	void addMove(Piece* piece, int fromRow, int fromCol, int toRow, int toCol) {

		std::vector <std::string> _pieces = _piecesHistory[_piecesHistory.size() - 1];
		_pieces[toRow][toCol] = pieceToChar(piece);
		_pieces[fromRow][fromCol] = ' ';
		_piecesHistory.push_back(_pieces);

		for (int i = 0; i < 8; i++) std::cout << _pieces[i] << '\n';
		std::cout << '\n';
	}

	void reset(Piece* _pieces[BOARD_SIZE][BOARD_SIZE]) {
		_piecesHistory.clear();
		std::vector <std::string> _str(BOARD_SIZE);
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				_str[i] += pieceToChar(_pieces[i][j]);
		_piecesHistory.push_back(_str);
	}

	bool undo() {
		if (_piecesHistory.size() < 2) return false;
		_piecesHistory.pop_back();
		return true;
	}

	char pieceAt(int row, int col){
		return _piecesHistory[_piecesHistory.size() - 1][row][col];
	}
};
