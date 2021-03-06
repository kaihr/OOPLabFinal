#pragma once
#include "GameState.h"
#include "NullState.h"

class MovingState : public GameState {
protected:
	int _row, _col;

public:
	MovingState(int row, int col) : _row(row), _col(col) {};

	void entry(ChessGame& owner);
	void quit(ChessGame& owner);
	void update(ChessGame& owner);

	void acceptMove(ChessGame& owner);
	void rejectMove(ChessGame& owner);

	GameState* handleInput(const sf::Event& event, ChessGame& owner);
};
