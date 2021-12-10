#pragma once
#include "GameState.h"

class MenuState : public GameState {
	void draw(ChessGame& owner);
	GameState* handleInput(const sf::Event &event, ChessGame &owner);
};
