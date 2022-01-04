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

	_button[0] = new Button(sf::Vector2f(120, 50), RECT_COLOR, "Undo", 35, sf::Color::Black, 700, 220);
	_button[1] = new Button(sf::Vector2f(120, 50), RECT_COLOR, "Menu", 35, sf::Color::Black, 700, 300);
	_button[2] = new Button(sf::Vector2f(120, 50), RECT_COLOR, "Exit", 35, sf::Color::Black, 700, 380);

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
	if (code == TERMINATE_CODE::CHECK_MATE) {
		switchState(new TerminateState());
	}

	if (code == TERMINATE_CODE::STALE_MATE) {
		switchState(new TerminateState());
	}

	if (!_time[_isWhiteTurn].update()) {
		switchState(new TerminateState());
	}

	sf::Event event;

	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			switchState(new TerminateState());
			_gameRunning = false;
		}

		GameState *tmp = _mouseState->handleInput(event, *this);
		if (tmp)
			switchState(tmp);
	}
}

void ChessGame::draw()
{
	_window.clear(BG_COLOR);

	_mouseState->draw(*this);

	for (int i = 0; i < 3; i++)
		_window.draw(*_button[i]);

	_window.display();
}

void ChessGame::switchState(GameState* newState)
{
	_mouseState->quit(*this);
	delete _mouseState;

	_mouseState = newState;
	_mouseState->entry(*this);
}

void ChessGame::handleButton(int btnId)
{
	if (btnId == 0) {
		_isWhiteTurn ^= 1;
		_record.undo();
		for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++){
			delete _pieces[i][j];
			_pieces[i][j] = NULL;
			char piece = _record.pieceAt(i, j);

			if (piece == 'p') _pieces[i][j] = new Pawn(i, j, false);
			else if (piece == 'P') _pieces[i][j] = new Pawn(i, j);
			else if (piece == 'r') _pieces[i][j] = new Rook(i, j, false);
			else if (piece == 'R') _pieces[i][j] = new Rook(i, j);
			else if (piece == 'n') _pieces[i][j] = new Knight(i, j, false);
			else if (piece == 'N') _pieces[i][j] = new Knight(i, j);
			else if (piece == 'b') _pieces[i][j] = new Bishop(i, j, false);
			else if (piece == 'B') _pieces[i][j] = new Bishop(i, j);
			else if (piece == 'q') _pieces[i][j] = new Queen(i, j, false);
			else if (piece == 'Q') _pieces[i][j] = new Queen(i, j);
			else if (piece == 'k') _pieces[i][j] = new King(i, j, false);
			else if (piece == 'K') _pieces[i][j] = new King(i, j);
		}
	}
}

void ChessGame::update() {
	_mouseState->update(*this);
	_time[_isWhiteTurn].update();
	sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
	for (int i = 0; i < 3; i++)
		_button[i]->update(mousePos);
}

void ChessGame::run()
{
	while (_gameRunning) {
		handleInput();
		update();
		draw();
	}

	Button* button = new Button(sf::Vector2f(400, MENU_OPTION_HEIGHT), RECT_COLOR, "Back to menu", 50, sf::Color::Black, 300, 300);

	_gameRunning = true;

	while (_gameRunning) {
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_gameRunning = false;
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			if (button->isMouseOver())
				_gameRunning = false;
		}

		button->update(sf::Mouse::getPosition(_window));

		_window.clear(BG_COLOR);

		_mouseState->draw(*this);

		_window.draw(*button);

		_window.display();
	}

	delete button;
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
