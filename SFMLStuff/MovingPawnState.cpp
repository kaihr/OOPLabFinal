#include "MovingPawnState.h"

GameState* MovingPawnState::handleInput(const sf::Event& event, ChessGame& owner)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i cell = Utility::getCell(sf::Mouse::getPosition(owner._window));
	
		if (Utility::inBoard(cell.x, cell.y)) {
			if (!owner._pieces[cell.x][cell.y]
				&& (cell.x == _row + _positiveDirection)
				&& (cell.y == _col + 1 || cell.y == _col - 1)) {
				
				// Another pawn of different color
				if (owner._pieces[_row][cell.y]
					&& owner._pieces[_row][cell.y]->isWhite() != owner._currentChosen->isWhite()
					&& owner._pieces[_row][cell.y]->type() == Piece::Type::PAWN
					&& owner._preChosen == owner._pieces[_row][cell.y]) {
					
					delete owner._pieces[_row][cell.y];
					owner._pieces[_row][cell.y] = NULL;

					owner._pieces[_row][_col] = NULL;
					owner._pieces[cell.x][cell.y] = owner._currentChosen;
					owner._currentChosen->setPos(cell.x, cell.y);

					owner._time[owner._isWhiteTurn].stop();
					owner._isWhiteTurn ^= 1;
					owner._time[owner._isWhiteTurn].start();

					owner._currentChosen->markAsMoved();
					
					owner._preChosen = owner._currentChosen;

					return new NullState();
				}

				owner._currentChosen->setPos();
				return new NullState();
			}
		}
	}

	return MovingState::handleInput(event, owner);
}
