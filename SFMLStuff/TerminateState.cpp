#include "TerminateState.h"

GameState* TerminateState::handleInput(const sf::Event& event, ChessGame& owner)
{
	return NULL;
}

void TerminateState::entry(ChessGame &owner)
{
	owner._time[owner._isWhiteTurn].stop();
}
