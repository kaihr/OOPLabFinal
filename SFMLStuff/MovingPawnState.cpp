#include "MovingPawnState.h"

GameState* MovingPawnState::handleInput(const sf::Event& event, ChessGame& owner)
{
	return MovingState::handleInput(event, owner);
}
