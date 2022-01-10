#include "MovingKingState.h"

GameState* MovingKingState::handleInput(const sf::Event& event, ChessGame& owner)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i cell = Utility::getCell(sf::Mouse::getPosition(owner._window));

		if ((cell.y == _col - 2 || cell.y == _col + 2)
			&& owner._currentChosen->validAndNotInCheck(cell.x, cell.y, owner._pieces)) {
			owner._record.addMove(owner._pieces, owner._preChosen);

			owner._pieces[cell.x][cell.y] = owner._currentChosen;
			owner._pieces[_row][_col] = NULL;
			owner._currentChosen->setPos(cell.x, cell.y);

			if (cell.y == _col + 2) {
				if (!owner._currentChosen->validAndNotInCheck(cell.x, _col + 1, owner._pieces))
					return MovingState::handleInput(event, owner);

				owner._pieces[cell.x][_col + 1] = owner._pieces[cell.x][7];
				owner._pieces[cell.x][7]->setPos(cell.x, _col + 1);
				owner._pieces[cell.x][7] = NULL;
			}

			if (cell.y == _col - 2) {
				if (!owner._currentChosen->validAndNotInCheck(cell.x, _col - 1, owner._pieces))
					return MovingState::handleInput(event, owner);

				owner._pieces[cell.x][_col - 1] = owner._pieces[cell.x][0];
				owner._pieces[cell.x][0]->setPos(cell.x, _col - 1);
				owner._pieces[cell.x][0] = NULL;
			}

			acceptMove(owner);
			return new NullState();
		}
	}

	return MovingState::handleInput(event, owner);
}
