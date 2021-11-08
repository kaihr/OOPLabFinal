#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "ChessBoard.h"
#include "Pawn.h"

class ChessGame {
private:
	ChessBoard board;
	Piece* pieces[BOARD_SIZE][BOARD_SIZE];
	Piece* currentChosen;
	sf::RenderWindow window;

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