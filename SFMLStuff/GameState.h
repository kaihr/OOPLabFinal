#pragma once
#include "ChessGame.h"

class GameState {
public:
	virtual void entry(ChessGame& game) {};
	virtual void quit(ChessGame& game) {};
	virtual void update(ChessGame& game) {};
	virtual void draw(ChessGame& game);
	virtual GameState *handleInput(const sf::Event& e, ChessGame& game) = 0;
};
