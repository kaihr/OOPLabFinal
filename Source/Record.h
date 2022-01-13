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
	std::vector <std::vector <std::vector <int>>> _piecesHistory;
	std::vector <std::pair <int, int>> _preChosenHistory;
public:
	static int encodePiece(Piece* piece) {
		if (!piece) return -1;
		return char((int)piece->type() * 10 + (piece->isWhite() << 2) + (piece->enPassant() << 1) + (piece->hasMoved() > 0));
	}
	static Piece* decodePiece(int piece, int row, int col) {
		if (piece == -1) return NULL;
		Piece::Type type = (Piece::Type)(piece / 10);
		bool isWhite = ((piece % 10) >> 2) & 1;
		bool enPassant = ((piece % 10) >> 1) & 1;
		bool hasMove = (piece % 10) & 1;
		Piece* cur = NULL;
		switch (type)
		{
		case Piece::Type::PAWN:
			cur = new Pawn(row, col, isWhite, enPassant, hasMove);
			break;
		case Piece::Type::ROOK:
			cur = new Rook(row, col, isWhite, enPassant, hasMove);
			break;
		case Piece::Type::BISHOP:
			cur = new Bishop(row, col, isWhite, enPassant, hasMove);
			break;
		case Piece::Type::KNIGHT:
			cur = new Knight(row, col, isWhite, enPassant, hasMove);
			break;
		case Piece::Type::QUEEN:
			cur = new Queen(row, col, isWhite, enPassant, hasMove);
			break;
		case Piece::Type::KING:
			cur = new King(row, col, isWhite, enPassant, hasMove);
			break;
		}
		if (cur == NULL) std::cout << "wtf\n";
		return cur;
	}

public:

	Record(){
		_piecesHistory.clear();
		_preChosenHistory.clear();
	}

	void addMove(Piece* _pieces[BOARD_SIZE][BOARD_SIZE], Piece* preChosen) {

		std::vector <std::vector <int>> table(BOARD_SIZE);
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++)
				table[i].push_back(encodePiece(_pieces[i][j]));
		}
		_piecesHistory.push_back(table);

		if (!preChosen)
			_preChosenHistory.push_back(std::make_pair(-1, -1));
		else
			_preChosenHistory.push_back(std::make_pair(preChosen->row(), preChosen->col()));
	}

	void reset(Piece* _pieces[BOARD_SIZE][BOARD_SIZE]) {
		std::cerr << "AAAAAAAAAAAAAAAAA" << '\n';
		_piecesHistory.clear();
		std::vector <std::vector <int>> table(BOARD_SIZE);
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				table[i].push_back(encodePiece(_pieces[i][j]));
		_piecesHistory.push_back(table);
		_preChosenHistory.push_back(std::make_pair(-1, -1));
	}

	Piece* preChosen(Piece* _pieces[BOARD_SIZE][BOARD_SIZE]) {
		std::pair <int, int> preChosenPos = _preChosenHistory.back();
		if (preChosenPos.first == -1)
			return NULL;
		return _pieces[preChosenPos.first][preChosenPos.second];
	}

	bool canUndo() {
		return !_piecesHistory.empty();
	}

	void undo() {
		_piecesHistory.pop_back();
		_preChosenHistory.pop_back();
	}

	char pieceAt(int row, int col){
		return _piecesHistory.back()[row][col];
	}
};
