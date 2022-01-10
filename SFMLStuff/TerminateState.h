#pragma once
#include "GameState.h"

class TerminateState : public GameState {
private:
	std::string _str;

public:
	TerminateState(const std::string str) : _str(str) {};

	GameState* handleInput(const sf::Event& event, ChessGame& owner);
	void entry(ChessGame &game);
};
