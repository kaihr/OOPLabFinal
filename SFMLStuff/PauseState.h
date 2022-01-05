#pragma once
#include "GameState.h"

class PauseState : public GameState
{
public:
	GameState* handleInput(const sf::Event& e, ChessGame& owner);
	void entry(ChessGame& owner);
	void quit(ChessGame& owner);
	void draw(ChessGame& owner);
};
