#include "TerminateState.h"

GameState* TerminateState::handleInput(const sf::Event& event, ChessGame& owner)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Q)
			owner._gameRunning = false;
	}

	return NULL;
}

void TerminateState::entry(ChessGame &owner)
{
	owner._time[owner._isWhiteTurn].stop();
}
