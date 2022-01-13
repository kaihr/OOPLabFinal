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
	Button* _button[5];
	Button* _configButton[N_CONFIG_BUTTON];
	bool _onConfig;

	sf::RenderWindow& _window;
	int& _configID;

public:
	MenuState(sf::RenderWindow &window, int& configID);
	void draw();
	OPTION handleInput(const sf::Event &event);
	~MenuState();
};
