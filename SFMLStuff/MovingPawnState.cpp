#include "MovingPawnState.h"
#include "NullState.h"

#include <assert.h>

#include <iostream>

GameState* MovingPawnState::handleInput(const sf::Event& event, ChessGame& owner)
{
	return MovingState::handleInput(event, owner);
}
