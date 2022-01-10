#include "NullState.h"
#include "MovingState.h"
#include "MovingKingState.h"
#include "MovingPawnState.h"
#include "MenuState.h"
#include "PauseState.h"

GameState* NullState::handleInput(const sf::Event& event, ChessGame& owner)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i cell = Utility::getCell(sf::Mouse::getPosition(owner._window));

		sf::Vector2i mousePos = sf::Mouse::getPosition(owner._window);

		for (int i = 0; i < 3; i++)
			if (owner._button[i]->isMouseOver(mousePos))
				owner.handleButton(i);

		if (!Utility::inBoard(cell.x, cell.y))
			return NULL;

		if (owner._pieces[cell.x][cell.y] && owner._pieces[cell.x][cell.y]->isWhite() == owner._isWhiteTurn) {
			owner._currentChosen = owner._pieces[cell.x][cell.y];

			if (owner._currentChosen->type() == Piece::Type::KING)
				return new MovingKingState(cell.x, cell.y);

			if (owner._currentChosen->type() == Piece::Type::PAWN)
				return new MovingPawnState(cell.x, cell.y, owner._isWhiteTurn);

			return new MovingState(cell.x, cell.y);
		}

	}

	return NULL;
}
