#pragma once
#include "MovingState.h"

class PromotionState : public MovingState {
public:
	PromotionState(int row, int col) : MovingState(row, col) {};
	GameState* handleInput(const sf::Event& event, ChessGame& owner);
	void entry(ChessGame& owner) {};
	void update(ChessGame& owner) {};
	void quit(ChessGame& owner) {
		acceptMove(owner);
	}
};
