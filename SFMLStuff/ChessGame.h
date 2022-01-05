#pragma once

#include <SFML/Graphics.hpp>

#include <assert.h>

#include "Timer.h"
#include "Record.h"
#include "Constants.h"
#include "ChessBoard.h"
#include "Pawn.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"

class GameState;

class ChessGame {
private:
	ChessBoard _board;
	Piece* _pieces[BOARD_SIZE][BOARD_SIZE];
	Piece* _currentChosen;
	Piece* _preChosen;
	sf::RenderWindow &_window;
	bool _isWhiteTurn;
	Timer _time[2];
	int _score[2];
	GameState* _mouseState;
	Record _record;
	bool _gameRunning;

public:
	enum class TERMINATE_CODE {
		EXISTS_VALID_MOVE,
		CHECK_MATE,
		STALE_MATE,
	};

public:
	friend class GameState;
	friend class NullState;
	friend class MovingState;
	friend class MovingKingState;
	friend class MovingPawnState;
	friend class MenuState;
	friend class MenuOption;
	friend class TerminateState;
	friend class PromotionState;
	friend class PauseState;

	ChessGame(sf::RenderWindow &window);
	ChessGame(sf::RenderWindow& window, int saveSlot);

	~ChessGame()
	{
		assert(_currentChosen == NULL);

		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++) {
				if (_pieces[i][j] == _preChosen)
					_preChosen = NULL;

				delete _pieces[i][j];
				_pieces[i][j] = NULL;
			}

		delete _preChosen;
		delete _mouseState;
	}

	void handleInput();
	void update();
	void draw();
	void switchState(GameState *newState);
	void run();

	TERMINATE_CODE outOfMove();

	void save(int id);
};
