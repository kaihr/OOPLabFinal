#pragma once
#include "GameState.h"
#include "MovingState.h"

#include <iostream>

class NullState : public GameState {
public:
	GameState* handleInput(const sf::Event& event, ChessGame& owner);
};