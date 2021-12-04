#include "ChessGame.h"
#include "Timer.h"

#include <iostream>

ChessGame::ChessGame() : _currentChosen(NULL), _window(sf::VideoMode(800, 600), "Chess")
{
	_isWhiteTurn = true;

	_time[0].setTimer(FullTime(0, 5, 0));
	_time[1].setTimer(FullTime(0, 5, 0));
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
}

void ChessGame::handleInput()
{
	sf::Event event;

	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window.close();

		if (_currentChosen) {
			_currentChosen = _currentChosen->handleInput(event, _pieces);
			if (!_currentChosen){
				_time[_isWhiteTurn].stop();
				_isWhiteTurn ^= 1;
				_time[_isWhiteTurn].start();
			}

		}
		else if (!_currentChosen) {
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i cell = Utility::getCell(sf::Mouse::getPosition(_window));
				if (_pieces[cell.x][cell.y] && _pieces[cell.x][cell.y]->isWhite() == _isWhiteTurn)
					_currentChosen = _pieces[cell.x][cell.y];
			}
		}
	}
}

void ChessGame::draw()
{
	_window.clear();

	_window.draw(_board);

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (_pieces[i][j] && (_currentChosen != _pieces[i][j]))
				_window.draw(*_pieces[i][j]);

	if (_currentChosen) {
		_currentChosen->moveWithMouse(_window);
		_window.draw(*_currentChosen);
	}

	_window.display();
}

void ChessGame::run()
{
	std::cout << _window.isOpen() << std::endl;
	while (_window.isOpen())
	{
		_time[_isWhiteTurn].update();
		FullTime t = _time[_isWhiteTurn].getRemainingTime();
		std::cout << t._hours << ':' << t._minutes << ':' << t._seconds << ':' << t._miliseconds << "    \r";
		handleInput();
		draw();
	}
}
