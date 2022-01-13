#pragma once
#include "GameState.h"

class NullState : public GameState {
public:
	GameState* handleInput(const sf::Event& event, ChessGame& owner);
};
