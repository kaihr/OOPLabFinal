#include "ChessGame.h"
#include "Timer.h"
#include "NullState.h"
#include "MovingState.h"
#include "MenuState.h"
#include "TerminateState.h"

#include <iostream>
#include <string>
#include <fstream>

ChessGame::ChessGame(sf::RenderWindow &window, Timer::FullTime configTime) : _currentChosen(NULL), _preChosen(NULL), _window(window)
{

	_isWhiteTurn = true;
	_gameRunning = true;

	_time[0].setTimer(configTime);
	_time[0].setPosition(600, 0);
	_time[1].setTimer(configTime);
	_time[1].setPosition(600, 600 - TIMER_HEIGHT);
	_time[0].start();
	_time[0].stop();
	_time[1].start();

	_button[0] = new Button(sf::Vector2f(120, 50), RECT_COLOR, "Undo", 35, sf::Color::Black, 700, 220);
	_button[1] = new Button(sf::Vector2f(120, 50), RECT_COLOR, "Save", 35, sf::Color::Black, 700, 300);
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
	//_record.reset(_pieces);

	_mouseState = new NullState();
}

ChessGame::ChessGame(sf::RenderWindow& window, int saveSlot) : _window(window)
{
	_gameRunning = false;
	_isWhiteTurn = false;
	_mouseState = NULL;
	_currentChosen = NULL;
	_preChosen = NULL;
	_score[0] = _score[1] = 0;

	_button[0] = new Button(sf::Vector2f(120, 50), RECT_COLOR, "Undo", 35, sf::Color::Black, 700, 220);
	_button[1] = new Button(sf::Vector2f(120, 50), RECT_COLOR, "Save", 35, sf::Color::Black, 700, 300);
	_button[2] = new Button(sf::Vector2f(120, 50), RECT_COLOR, "Exit", 35, sf::Color::Black, 700, 380);

	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			_pieces[i][j] = NULL;

	std::ifstream fin(std::to_string(saveSlot) + ".dat");

	if (!fin.good())
		return;

	std::string buf;

	std::getline(fin, buf);
	_isWhiteTurn = std::stoi(buf);

	std::getline(fin, buf);
	int currentID = std::stoi(buf);

	std::getline(fin, buf);
	int preID = std::stoi(buf);

	std::getline(fin, buf);
	int n = std::stoi(buf);

	for (int i = 0; i < n; ++i) {
		std::getline(fin, buf);
		std::stringstream ss(buf);
		int row, col;
		bool isWhite, enPassant;
		int hasMove, foo;

		Piece::Type type;

		ss >> row >> col >> isWhite >> enPassant >> hasMove >> foo;
		type = (Piece::Type)foo;

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
		default:
			break;
		}

		_pieces[row][col] = cur;

		if (currentID == i)
			_currentChosen = cur;

		if (preID == i)
			_preChosen = cur;
	}

	_time[0].setPosition(600, 0);
	_time[1].setPosition(600, 600 - TIMER_HEIGHT);

	for (int i = 0; i < 2; ++i) {
		std::getline(fin, buf);
		std::stringstream ss(buf);

		int remainingTime;
		ss >> remainingTime;

		int temp = remainingTime;
		int miliseconds = temp % 1000;
		temp /= 1000;
		int seconds = temp % 60;
		temp /= 60;
		int minutes = temp % 60;
		temp /= 60;
		int hours = temp % 1000;

		_time[i].setTimer(Timer::FullTime(hours, minutes, seconds, miliseconds));
	}

	_time[0].start();
	_time[0].stop();

	_time[1].start();
	_time[1].stop();

	_time[_isWhiteTurn].start();

	// _record.reset(_pieces);

	std::getline(fin, buf);
	_gameRunning = std::stoi(buf);

	_mouseState = new NullState();

	fin.close();
}

void ChessGame::handleInput()
{
	TERMINATE_CODE code = outOfMove();
	if (code == TERMINATE_CODE::CHECK_MATE) {
		switchState(new TerminateState(_isWhiteTurn ? "Black win" : "White win"));
	}

	if (code == TERMINATE_CODE::STALE_MATE) {
		switchState(new TerminateState("Stale mate"));
	}

	if (!_time[_isWhiteTurn].update()) {
		switchState(new TerminateState(_isWhiteTurn ? "Black win" : "White win"));
	}

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
	_window.clear(BG_COLOR);

	_mouseState->draw(*this);

	for (int i = 0; i < 3; i++)
		_window.draw(*_button[i]);

	_window.display();
}

void ChessGame::switchState(GameState* newState)
{
	if (_mouseState) {
		_mouseState->quit(*this);
		delete _mouseState;
	}

	_mouseState = newState;
	_mouseState->entry(*this);
}

void ChessGame::handleButton(int btnId)
{
	if (btnId == 0 && _record.canUndo()) {
		_time[_isWhiteTurn].stop();
		_isWhiteTurn ^= 1;
		_time[_isWhiteTurn].start();
		for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++){
			delete _pieces[i][j];
			_pieces[i][j] = Record::decodePiece(_record.pieceAt(i, j), i, j);
		}
		_preChosen = _record.preChosen(_pieces);

		_record.undo();
	}

	if (btnId == 1)
		save(1);

	if (btnId == 2)
		_gameRunning = false;
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

void ChessGame::save(int id)
{
	std::ofstream fout(std::to_string(id) + ".dat");

	if (!fout.good())
		return;

	std::vector<Piece*> buff;
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			if (_pieces[i][j])
				buff.push_back(_pieces[i][j]);

	int currentID = -1;
	int preID = -1;

	for (int i = 0; i < (int)buff.size(); ++i) {
		if (_preChosen == buff[i])
			preID = i;

		if (_currentChosen == buff[i])
			preID = i;
	}

	fout << _isWhiteTurn << '\n';
	fout << currentID << '\n';
	fout << preID << '\n';

	fout << (int)buff.size() << '\n';
	for (auto piece : buff)
		fout << piece->toString() << '\n';

	fout << _time[0].toString() << '\n';
	fout << _time[1].toString() << '\n';

	fout << _gameRunning << '\n';

	fout.close();
}
