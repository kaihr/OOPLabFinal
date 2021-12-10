#include "MovingState.h"
#include "NullState.h"

#include <assert.h>

#include <iostream>

GameState* MovingState::handleInput(const sf::Event& event, ChessGame& owner) {
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i cell = Utility::getCell(sf::Mouse::getPosition(owner._window));

		if (!Utility::inBoard(cell.x, cell.y)
			|| (owner._pieces[cell.x][cell.y] == owner._currentChosen)
			|| (owner._pieces[cell.x][cell.y] && owner._pieces[cell.x][cell.y]->isWhite() == owner._currentChosen->isWhite())) 
		{
			owner._currentChosen->setPos();
			return new NullState();
		}

		if (owner._currentChosen->validCell(cell.x, cell.y, owner._pieces)) {
			if (owner._pieces[cell.x][cell.y])
				delete owner._pieces[cell.x][cell.y];

			owner._pieces[_row][_col] = NULL;
			owner._pieces[cell.x][cell.y] = owner._currentChosen;

			owner._currentChosen->setPos(cell.x, cell.y);
			
			owner._time[owner._isWhiteTurn].stop();
			owner._isWhiteTurn ^= 1;
			owner._time[owner._isWhiteTurn].start();

			return new NullState();
		}

		owner._currentChosen->setPos();
		return new NullState();
	}

	if (event.type == sf::Event::KeyPressed) {
		owner._currentChosen->setPos();
		return new NullState();
	}

	return NULL;
}

void MovingState::entry(ChessGame& owner)
{
	//std::cout << "FUCKFUCKFUCK" << std::endl;
	owner._board.highlightCell(owner._currentChosen, true, owner._pieces);
}

void MovingState::quit(ChessGame& owner)
{
	owner._board.highlightCell(owner._currentChosen, false, owner._pieces);
	owner._currentChosen = NULL;
}

void MovingState::update(ChessGame& owner)
{
	assert(owner._currentChosen);
	owner._currentChosen->moveWithMouse(owner._window);
}
