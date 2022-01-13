#pragma once
#include "MovingState.h"

class MovingPawnState : public MovingState {
private:
	int _positiveDirection;
public:
	MovingPawnState(int row, int col, bool isWhite) : MovingState(row, col), _positiveDirection(-1) {
		if (!isWhite)
			_positiveDirection = 1;
	};

	GameState* handleInput(const sf::Event& event, ChessGame& owner);
};
