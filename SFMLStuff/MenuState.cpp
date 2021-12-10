#include "MenuState.h"
#include "NullState.h"

void MenuState::draw(ChessGame& owner)
{
	owner._window.clear();

	sf::Font font;
	font.loadFromFile("Assets\\arial.ttf");
	
	sf::Text text;
	text.setFont(font);
	text.setString("Press 'S' to start");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Red);

	owner._window.draw(text);

	owner._window.display();
}

GameState* MenuState::handleInput(const sf::Event& event, ChessGame& owner)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::S)
			return new NullState();

		return NULL;
	}

	return NULL;
}
