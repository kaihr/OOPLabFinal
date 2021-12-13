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
			else
			{
				if (owner._currentChosen->isWhite())
				{
					if (_row == 3 && _row - 1 == cell.x && (cell.y == _col-1 || cell.y == _col+1))
					{
						delete owner._pieces[_row][cell.y];
						owner._pieces[_row][cell.y] = NULL;
					}
				}
				else
				{
					if (_row == 4 && _row + 1 == cell.x && (cell.y == _col - 1 || cell.y == _col + 1))
					{
						delete owner._pieces[_row][cell.y];
						owner._pieces[_row][cell.y] = NULL;
					}
				}
			}
			
			owner._pieces[_row][_col] = NULL;
			owner._pieces[cell.x][cell.y] = owner._currentChosen;
			owner._currentChosen->setPos(cell.x, cell.y);
			
			acceptMove(owner);
			return new NullState();
		}

		rejectMove(owner);
		return new NullState();
	}

	if (event.type == sf::Event::KeyPressed) {
		rejectMove(owner);
		return new NullState();
	}

	return NULL;
}

void MovingState::entry(ChessGame& owner)
{
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

/*
Stop clock
Swith turn
Start clock
Mark current piece as moved
Update en passant state of previous piece
Update privious piece
 */
void MovingState::acceptMove(ChessGame& owner)
{
	owner._time[owner._isWhiteTurn].stop();
	owner._isWhiteTurn ^= 1;
	owner._time[owner._isWhiteTurn].start();

	owner._currentChosen->markAsMoved();

	if (owner._preChosen && owner._preChosen->type() == Piece::Type::PAWN && owner._preChosen->enPassant())
		owner._preChosen->switchEnPassant();

	owner._preChosen = owner._currentChosen;
}

/*
Invalid move
Clean up and reset piece position
*/
void MovingState::rejectMove(ChessGame &owner)
{
	owner._currentChosen->setPos(_row, _col);
}
