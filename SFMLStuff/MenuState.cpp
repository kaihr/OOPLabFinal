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

void MenuState::drawMenuOption(std::string s, float position, ChessGame& owner){
	sf::Vector2i mousePos = sf::Mouse::getPosition(owner._window);
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
	owner._window.draw(rect);

	text.setFont(font);
	text.setString(s);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Black);
	text.setPosition(MENU_OPTION_PADDING_LEFT, position);

	owner._window.draw(text);
}

MenuState::MenuState(ChessGame& owner){
	font.loadFromFile("Assets\\arial.ttf");
}

void MenuState::draw(ChessGame& owner)
{
	owner._window.clear();
	sf::Texture texture;
	texture.loadFromFile("Assets\\menu_background.jpg");
	sf::Sprite bg(texture);
	owner._window.draw(bg);

	/*
	for (int i = 1; i <= 4; i++){
		rect.setSize(sf::Vector2f(200, 70));
		rect.setFillColor(rectColor1);
		rect.setPosition(sf::Vector2f(75, i * 100));
		owner._window.draw(rect);
	}
	*/

	drawMenuOption("Start", 100, owner);
	drawMenuOption("Load", 200, owner);
	drawMenuOption("Config", 300, owner);
	drawMenuOption("Exit", 400, owner);

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
		if (isMouseOnRect(100, mousePos))
			return new NullState();   // Start
		if (isMouseOnRect(200, mousePos))
			return NULL;   // Option 2
		if (isMouseOnRect(300, mousePos))
			return NULL;   // Option 3
		if (isMouseOnRect(400, mousePos))
			return NULL;   // Option 4
		return NULL;
	}

	return NULL;
}

