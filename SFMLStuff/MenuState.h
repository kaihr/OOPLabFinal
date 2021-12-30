#pragma once
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
	sf::RenderWindow& _window;
	sf::Font font;
public:
	void drawMenuOption(std::string s, float position);
	MenuState(sf::RenderWindow &window);
	void draw();
	OPTION handleInput(const sf::Event &event);
};
