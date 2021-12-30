#include <SFML/Graphics.hpp>

#include "ChessGame.h"
#include "TextureManager.h"
#include "MenuState.h"

#include <iostream>

TextureManager *TextureManager::instance = NULL;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Chess");
	MenuState menu(window);

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
			ChessGame game(window);
			game.run();
		}

		if (mode == MenuState::OPTION::EXIT) {
			window.close();
		}
	}

	return 0;
}