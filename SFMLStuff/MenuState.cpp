#include "MenuState.h"
#include "NullState.h"
#include "Button.h"
#include <iostream>

const float MENU_OPTION_WIDTH = 250;
const float MENU_OPTION_HEIGHT = 80;
const sf::Color RECT_COLOR(206, 216, 229);
const sf::Color ACTIVE_RECT_COLOR(236, 246, 255);
const sf::Vector2f RECT_SIZE(MENU_OPTION_WIDTH, MENU_OPTION_HEIGHT);

MenuState::MenuState(ChessGame& owner) {
	_button[0] = new Button(RECT_SIZE, RECT_COLOR, "Start", 50, sf::Color::Black, 200, 150);
	_button[1] = new Button(RECT_SIZE, RECT_COLOR, "Load", 50, sf::Color::Black, 200, 250);
	_button[2] = new Button(RECT_SIZE, RECT_COLOR, "Config", 50, sf::Color::Black, 200, 350);
	_button[3] = new Button(RECT_SIZE, RECT_COLOR, "Exit", 50, sf::Color::Black, 200, 450);
	for (int i = 0; i < 4; i++)
		_button[i]->setOnHoverColor(ACTIVE_RECT_COLOR, sf::Color::Black);

}

MenuState::MenuState(sf::RenderWindow& window) : _window(window)
{
	font.loadFromFile("Assets\\arial.ttf");
}

void MenuState::draw()
{
	_window.clear();
	sf::Texture texture;
	texture.loadFromFile("Assets\\menu_background.jpg");
	sf::Sprite bg(texture);
	_window.draw(bg);

	sf::Vector2i mousePos = sf::Mouse::getPosition(owner._window);
	for (int i = 0; i < 4; i++){
		_button[i]->update(mousePos);
		owner._window.draw(*_button[i]);
	}
	*/

	drawMenuOption("Start", 100);
	drawMenuOption("Load", 200);
	drawMenuOption("Config", 300);
	drawMenuOption("Exit", 400);

	_window.display();
}

MenuState::OPTION MenuState::handleInput(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed){
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		
		if (isMouseOnRect(100, mousePos))
			return OPTION::START;
		if (isMouseOnRect(200, mousePos))
			return OPTION::MENU;
		if (isMouseOnRect(300, mousePos))
			return OPTION::MENU;
		if (isMouseOnRect(400, mousePos))
			return OPTION::EXIT;
	}

	return OPTION::MENU;
}

