#pragma once
#include "GameState.h"
#include <string>


class MenuState : public GameState {
private:
	sf::Font font;
public:
	void drawMenuOption(std::string s, float position, ChessGame& owner);
	MenuState(ChessGame& owner);
	void draw(ChessGame& owner);
	GameState* handleInput(const sf::Event &event, ChessGame &owner);
};
