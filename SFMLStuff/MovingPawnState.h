#pragma once
#include "MovingState.h"

class MovingPawnState : public MovingState {
public:
	MovingPawnState(int row, int col) : MovingState(row, col) {};
	GameState* handleInput(const sf::Event& event, ChessGame& owner);
};
