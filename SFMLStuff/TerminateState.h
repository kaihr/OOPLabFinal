#pragma once
#include "GameState.h"

class TerminateState : public GameState {
	GameState* handleInput(const sf::Event& event, ChessGame& owner);
};
