#include "MenuState.h"
#include "NullState.h"
#include "Button.h"
#include "TextureManager.h"
#include "Constants.h"

#include <iostream>

MenuState::MenuState(sf::RenderWindow& window, int& configID) : _window(window), _configID(configID), _onConfig(false) {

	_configID = 3;
	_button[0] = new Button(RECT_SIZE, RECT_COLOR, "Start", 50, sf::Color::Black, 200, 150);
	_button[1] = new Button(RECT_SIZE, RECT_COLOR, "Load", 50, sf::Color::Black, 200, 250);
	_button[2] = new Button(RECT_SIZE, RECT_COLOR, "Config >", 50, sf::Color::Black, 200, 350);
	_button[3] = new Button(RECT_SIZE, RECT_COLOR, "Exit", 50, sf::Color::Black, 200, 450);
	_button[4] = new Button(sf::Vector2f(100, 50), RECT_COLOR, CONFIG_BUTTON_LABEL[_configID], 25, sf::Color::Black, 390, 350);
	for (int i = 0; i < 5; i++)
		_button[i]->setOnHoverColor(ACTIVE_RECT_COLOR, sf::Color::Black);

	for (int i = 0; i < N_CONFIG_BUTTON; i++) {
		_configButton[i] = new Button(sf::Vector2f(100, 50), CONFIG_BUTTON_COLOR, CONFIG_BUTTON_LABEL[i], 25, sf::Color::Black, 390 + (i % 3) * 120, 290 + 60 * (i / 3));
		_configButton[i]->setOnHoverColor(CONFIG_BUTTON_ACTIVE_COLOR, sf::Color::Black);
	}
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
	if (_onConfig) {
		for (int i = 0; i < N_CONFIG_BUTTON; i++) {
			_configButton[i]->update(mousePos);
			_window.draw(*_configButton[i]);
		}
	}
	else {
		_button[4]->update(mousePos);
		_window.draw(*_button[4]);
	}
	_window.display();
}

MenuState::OPTION MenuState::handleInput(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed){
		if (_onConfig) {
			for (int i = 0; i < N_CONFIG_BUTTON; i++)
				if (_configButton[i]->isMouseOver()) {
					_configID = i;
					delete _button[4];
					_button[4] = new Button(sf::Vector2f(100, 50), RECT_COLOR, CONFIG_BUTTON_LABEL[_configID], 25, sf::Color::Black, 390, 350);
					_button[4]->setOnHoverColor(ACTIVE_RECT_COLOR, sf::Color::Black);
				}
		}
		_onConfig = false;

		if(_button[0]->isMouseOver())
			return OPTION::START;
		if (_button[1]->isMouseOver())
			return OPTION::LOAD;
		if (_button[2]->isMouseOver())
			_onConfig ^= 1;
		if (_button[3]->isMouseOver())
			return OPTION::EXIT;
		if (_button[4]->isMouseOver())
			_onConfig ^= 1;
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

