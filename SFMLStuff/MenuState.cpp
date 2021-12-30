#include "MenuState.h"
#include "NullState.h"
#include <iostream>

const float MENU_OPTION_WIDTH = 200;
const float MENU_OPTION_HEIGHT = 70;
const sf::Color RECT_COLOR(206, 216, 229);
const sf::Color ACTIVE_RECT_COLOR(148, 164, 188);
const sf::Vector2f RECT_SIZE(MENU_OPTION_WIDTH, MENU_OPTION_HEIGHT);
const sf::Vector2f ACTIVE_RECT_SIZE(250, 70);
const float MENU_OPTION_PADDING_LEFT = 100;

bool isMouseOnRect(float position, sf::Vector2i mousePos){
	return mousePos.y >= position &&
			mousePos.y <= position + MENU_OPTION_HEIGHT &&
			mousePos.x >= MENU_OPTION_PADDING_LEFT &&
			mousePos.x <= MENU_OPTION_PADDING_LEFT + MENU_OPTION_WIDTH;
}

void MenuState::drawMenuOption(std::string s, float position){
	sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
	bool onHover = isMouseOnRect(position, mousePos);
	sf::Text text;
	sf::RectangleShape rect;
	if (!onHover){
		rect.setSize(RECT_SIZE);
		rect.setFillColor(RECT_COLOR);
	}else{
		rect.setSize(ACTIVE_RECT_SIZE);
		rect.setFillColor(ACTIVE_RECT_COLOR);
	}
	rect.setPosition(sf::Vector2f(MENU_OPTION_PADDING_LEFT - 25, position));
	_window.draw(rect);

	text.setFont(font);
	text.setString(s);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Black);
	text.setPosition(MENU_OPTION_PADDING_LEFT, position);

	_window.draw(text);
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

	/*
	for (int i = 1; i <= 4; i++){
		rect.setSize(sf::Vector2f(200, 70));
		rect.setFillColor(rectColor1);
		rect.setPosition(sf::Vector2f(75, i * 100));
		owner._window.draw(rect);
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

