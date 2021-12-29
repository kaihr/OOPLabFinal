#include "MenuState.h"
#include "NullState.h"
#include "Button.h"
#include <iostream>

const float MENU_OPTION_WIDTH = 250;
const float MENU_OPTION_HEIGHT = 80;
const sf::Color RECT_COLOR(206, 216, 229);
const sf::Color ACTIVE_RECT_COLOR(148, 164, 188);
const sf::Vector2f RECT_SIZE(MENU_OPTION_WIDTH, MENU_OPTION_HEIGHT);

MenuState::MenuState(ChessGame& owner) {
	_button[0] = new Button(RECT_SIZE, RECT_COLOR, "Start", 50, sf::Color::Black, 250, 150);
	_button[1] = new Button(RECT_SIZE, RECT_COLOR, "Load", 50, sf::Color::Black, 250, 250);
	_button[2] = new Button(RECT_SIZE, RECT_COLOR, "Config", 50, sf::Color::Black, 250, 350);
	_button[3] = new Button(RECT_SIZE, RECT_COLOR, "Exit", 50, sf::Color::Black, 250, 450);
	for (int i = 0; i < 4; i++)
		_button[i]->setOnHoverColor(ACTIVE_RECT_COLOR, sf::Color::Black);

}

void MenuState::draw(ChessGame& owner)
{
	owner._window.clear();
	sf::Texture texture;
	texture.loadFromFile("Assets\\menu_background.jpg");
	sf::Sprite bg(texture);
	owner._window.draw(bg);

	sf::Vector2i mousePos = sf::Mouse::getPosition(owner._window);
	for (int i = 0; i < 4; i++){
		_button[i]->update(mousePos);
		owner._window.draw(*_button[i]);
	}
	//drawMenuOption("Load", 200, owner);
	//drawMenuOption("Config", 300, owner);
	//drawMenuOption("Exit", 400, owner);

	owner._window.display();
}

GameState* MenuState::handleInput(const sf::Event& event, ChessGame& owner)
{

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::S)
			return new NullState();

		return NULL;
	}
	if (event.type == sf::Event::MouseButtonPressed){
		sf::Vector2i mousePos = sf::Mouse::getPosition(owner._window);
		if (_button[0]->isMouseOver())
			return new NullState();   // Start
		if (_button[1]->isMouseOver())
			return NULL;   // Option 2
		if (_button[2]->isMouseOver())
			return NULL;   // Option 3
		if (_button[3]->isMouseOver())
			return NULL;   // Option 4
		return NULL;
	}

	return NULL;
}

