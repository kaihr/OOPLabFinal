#pragma once
#include "GameState.h"
#include "Button.h"
#include <string>
#include <SFML/Graphics.hpp>

class MenuState {
public:
	enum class OPTION {
		MENU,
		START,
		LOAD,
		CONFIG,
		EXIT
	};

private:
	Button* _button[4];
	sf::RenderWindow& _window;

public:
	MenuState(sf::RenderWindow &window);
	void draw();
	OPTION handleInput(const sf::Event &event);
	~MenuState();
};
