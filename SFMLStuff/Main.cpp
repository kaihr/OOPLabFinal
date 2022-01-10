#include <SFML/Graphics.hpp>

#include "ChessGame.h"
#include "TextureManager.h"
#include "MenuState.h"

#include <iostream>

TextureManager *TextureManager::instance = NULL;
const Timer::FullTime CONFIG_TIME[N_CONFIG_BUTTON] = {
	Timer::FullTime(2, 0, 0),
	Timer::FullTime(1, 0, 0),
	Timer::FullTime(0, 30, 0),
	Timer::FullTime(0, 15, 0),
	Timer::FullTime(0, 10, 0),
	Timer::FullTime(0, 5, 0),
	Timer::FullTime(0, 3, 0),
	Timer::FullTime(0, 2, 0),
	Timer::FullTime(0, 1, 0),
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Chess", sf::Style::Titlebar | sf::Style::Close);
	int configID;
	MenuState menu(window, configID);

	while (window.isOpen()) {
		sf::Event event;
		MenuState::OPTION mode = MenuState::OPTION::MENU;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			mode = menu.handleInput(event);
		}

		if(mode == MenuState::OPTION::MENU)
			menu.draw();

		if (mode == MenuState::OPTION::START) {
			ChessGame game(window, CONFIG_TIME[configID]);
			game.run();
		}

		if (mode == MenuState::OPTION::LOAD) {
			ChessGame game(window, 1);
			game.run();
		}

		if (mode == MenuState::OPTION::EXIT) {
			window.close();
		}
	}

	return 0;
}
