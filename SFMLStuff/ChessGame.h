#pragma once

#include <SFML/Graphics.hpp>

#include "Timer.h"
#include "Constants.h"
#include "ChessBoard.h"
#include "Pawn.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"

class ChessGame {
private:
	ChessBoard board;
	Piece* pieces[BOARD_SIZE][BOARD_SIZE];
	Piece* currentChosen;
	sf::RenderWindow window;
	bool _isWhiteTurn;
	Timer _time[2];
	int _score[2];

public:
	ChessGame();
	~ChessGame()
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				delete pieces[i][j];
	}

	void handleInput();
	void draw();
	void run();
};
