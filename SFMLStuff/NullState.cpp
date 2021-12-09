#include "NullState.h"
#include "MovingState.h"

GameState* NullState::handleInput(const sf::Event& event, ChessGame& owner)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i cell = Utility::getCell(sf::Mouse::getPosition(owner._window));

		if (!Utility::inBoard(cell.x, cell.y)) //Might be clicking other button, will change later
			return NULL;

		if (owner._pieces[cell.x][cell.y] && owner._pieces[cell.x][cell.y]->isWhite() == owner._isWhiteTurn) {
			owner._currentChosen = owner._pieces[cell.x][cell.y];
			return new MovingState(cell.x, cell.y);
		}
	}

	return NULL;
}
