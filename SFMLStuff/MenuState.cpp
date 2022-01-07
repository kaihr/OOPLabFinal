#include "MenuState.h"
#include "NullState.h"
#include "Button.h"
#include "TextureManager.h"
#include "Constants.h"

#include <iostream>

MenuState::MenuState(sf::RenderWindow& window) : _window(window) {
	_button[0] = new Button(RECT_SIZE, RECT_COLOR, "Start", 50, sf::Color::Black, 200, 150);
	_button[1] = new Button(RECT_SIZE, RECT_COLOR, "Load", 50, sf::Color::Black, 200, 250);
	_button[2] = new Button(RECT_SIZE, RECT_COLOR, "Config", 50, sf::Color::Black, 200, 350);
	_button[3] = new Button(RECT_SIZE, RECT_COLOR, "Exit", 50, sf::Color::Black, 200, 450);
	for (int i = 0; i < 4; i++)
		_button[i]->setOnHoverColor(ACTIVE_RECT_COLOR, sf::Color::Black);
}

void MenuState::draw()
{
	_window.clear();
	sf::Sprite bg(TextureManager::getTexture(PIECES::BACKGROUND));
	_window.draw(bg);

	sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
	for (int i = 0; i < 4; i++){
		_button[i]->update(mousePos);
		_window.draw(*_button[i]);
	}

	_window.display();
}

MenuState::OPTION MenuState::handleInput(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed){
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
		
		if(_button[0]->isMouseOver())
			return OPTION::START;
		if (_button[1]->isMouseOver())
			return OPTION::LOAD;
		if (_button[2]->isMouseOver())
			return OPTION::MENU;
		if (_button[3]->isMouseOver())
			return OPTION::EXIT;
	}

	return OPTION::MENU;
}

MenuState::~MenuState()
{
	for (int i = 0; i < 4; i++) {
		delete _button[i];
		_button[i] = NULL;
	}
}

