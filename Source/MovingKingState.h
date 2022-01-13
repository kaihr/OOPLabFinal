#pragma once
#include "MovingState.h"

class MovingKingState : public MovingState {
public:
	MovingKingState(int row, int col) : MovingState(row, col) {};
	GameState* handleInput(const sf::Event& event, ChessGame& owner);
};
