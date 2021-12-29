#pragma once
#include "GameState.h"
#include "Button.h"
#include <string>


class MenuState : public GameState {
private:
	Button* _button[4];
public:
	void drawMenuOption(std::string s, float position, ChessGame& owner);
	MenuState(ChessGame& owner);
	void draw(ChessGame& owner);
	GameState* handleInput(const sf::Event &event, ChessGame &owner);
};
