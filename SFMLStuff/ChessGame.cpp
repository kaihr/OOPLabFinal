#include "ChessGame.h"
#include "Timer.h"
#include "NullState.h"
#include "MovingState.h"
#include "MenuState.h"
#include "TerminateState.h"

#include <iostream>

ChessGame::ChessGame(sf::RenderWindow &window) : _currentChosen(NULL), _preChosen(NULL), _window(window)
{
	_isWhiteTurn = true;
	_gameRunning = true;

	_time[0].setTimer(FullTime(0, 1, 0));
	_time[0].setPosition(600, 0);
	_time[1].setTimer(FullTime(0, 1, 0));
	_time[1].setPosition(600, 600 - TIMER_HEIGHT);
	_time[0].start();
	_time[0].stop();
	_time[1].start();

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			_pieces[i][j] = NULL;

	for (int i = 0; i < 8; i++) {
		_pieces[1][i] = new Pawn(1, i, false);
		_pieces[6][i] = new Pawn(6, i);
	}

	_pieces[0][0] = new Rook(0, 0, false);
	_pieces[0][7] = new Rook(0, 7, false);
	_pieces[7][0] = new Rook(7, 0);
	_pieces[7][7] = new Rook(7, 7);

	_pieces[0][1] = new Knight(0, 1, false);
	_pieces[0][6] = new Knight(0, 6, false);
	_pieces[7][1] = new Knight(7, 1);
	_pieces[7][6] = new Knight(7, 6);

	_pieces[0][2] = new Bishop(0, 2, false);
	_pieces[0][5] = new Bishop(0, 5, false);
	_pieces[7][2] = new Bishop(7, 2);
	_pieces[7][5] = new Bishop(7, 5);

	_pieces[0][3] = new Queen(0, 3, false);
	_pieces[7][3] = new Queen(7, 3);

	_pieces[0][4] = new King(0, 4, false);
	_pieces[7][4] = new King(7, 4);

	_score[0] = _score[1] = 0;

	_mouseState = new NullState();
}

void ChessGame::handleInput()
{
	TERMINATE_CODE code = outOfMove();
	if (code == TERMINATE_CODE::CHECK_MATE)
		switchState(new TerminateState());

	if (code == TERMINATE_CODE::STALE_MATE)
		switchState(new TerminateState());

	sf::Event event;

	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_gameRunning = false;

		GameState *tmp = _mouseState->handleInput(event, *this);
		if (tmp)
			switchState(tmp);
	}
}

void ChessGame::draw()
{
	_mouseState->draw(*this);
}

void ChessGame::switchState(GameState* newState)
{
	_mouseState->quit(*this);
	delete _mouseState;

	_mouseState = newState;
	_mouseState->entry(*this);
}

void ChessGame::update() {
	_mouseState->update(*this);
	_time[_isWhiteTurn].update();
}

void ChessGame::run()
{
	while (_gameRunning)
	{
		handleInput();
		update();
		draw();
	}
}

ChessGame::TERMINATE_CODE ChessGame::outOfMove()
{
	bool noValidMove = true;

	int kingRow = -1;
	int kingCol = -1;

	for(int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (!_pieces[i][j])
				continue;

			if (_pieces[i][j]->isWhite() != _isWhiteTurn)
				continue;

			if (_pieces[i][j]->type() == Piece::Type::KING) {
				kingRow = i;
				kingCol = j;
			}

			for (int k = 0; k < BOARD_SIZE; k++)
				for (int l = 0; l < BOARD_SIZE; l++) {
					if (_pieces[k][l] && _pieces[k][l]->isWhite() == _isWhiteTurn)
						continue;

					if (_pieces[i][j]->validAndNotInCheck(k, l, _pieces))
						return TERMINATE_CODE::EXISTS_VALID_MOVE;
				}
		}

	for(int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_pieces[i][j]
				&& _pieces[i][j]->isWhite() != _isWhiteTurn
				&& _pieces[i][j]->validAndNotInCheck(kingRow, kingCol, _pieces)) {

				return TERMINATE_CODE::CHECK_MATE;
			}
		}


	return TERMINATE_CODE::STALE_MATE;
}
