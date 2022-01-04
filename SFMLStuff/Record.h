#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Piece.h"

class Record{
private:
	int _nTurns;
	std::vector <std::string> history;
	std::vector <std::vector <std::string>> _piecesHistory;
public:

	Record(){
		_nTurns = 0;
		history.clear();
		std::vector <std::string> _pieces(8);
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				_pieces[i] += ' ';
		for (int i = 0; i < 8; i++) {
			_pieces[1][i] = 'p';
			_pieces[6][i] = 'P';
		}

		_pieces[0][0] = 'r';
		_pieces[0][7] = 'r';
		_pieces[7][0] = 'R';
		_pieces[7][7] = 'R';

		_pieces[0][1] = 'n';
		_pieces[0][6] = 'n';
		_pieces[7][1] = 'N';
		_pieces[7][6] = 'N';

		_pieces[0][2] = 'b';
		_pieces[0][5] = 'b';
		_pieces[7][2] = 'B';
		_pieces[7][5] = 'B';

		_pieces[0][3] = 'q';
		_pieces[7][3] = 'Q';

		_pieces[0][4] = 'k';
		_pieces[7][4] = 'K';

		_piecesHistory.push_back(_pieces);
	}

	Record(std::string filePath){
		loadFromFile(filePath);
	}

	void addMove(std::string str) {
		history.push_back(str);
		int fromRow = str[1] - 48;
		int fromCol = str[2] - 48;
		int toRow = str[3] - 48;
		int toCol = str[4] - 48;

		std::vector <std::string> _pieces = _piecesHistory[_piecesHistory.size() - 1];
		_pieces[toRow][toCol] = _pieces[fromRow][fromCol];
		_pieces[fromRow][fromCol] = ' ';
		_piecesHistory.push_back(_pieces);

		for (int i = 0; i < 8; i++) std::cout << _pieces[i] << '\n';
		std::cout << '\n';
	}

	void undo(){
		if (history.size() == 0) return;
		history.pop_back();
		_piecesHistory.pop_back();

	}

	char pieceAt(int row, int col){
		return _piecesHistory[_piecesHistory.size() - 1][row][col];
	}

	void saveToFile(std::string filePath){
		std::ofstream f(filePath);
		f << _nTurns << '\n';
		for (int i = 0; i < _nTurns; i++)
			f << history[i] << '\n';
		f.close();
	}

	void loadFromFile(std::string filePath){
		history.clear();
		std::ifstream f(filePath);
		f >> _nTurns;
		history.resize(_nTurns);
		for (int i = 0; i < _nTurns; i++)
			f >> history[i];
		f.close();
	}

};
