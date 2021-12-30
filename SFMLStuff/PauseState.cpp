#include "PauseState.h"
#include "NullState.h"

GameState* PauseState::handleInput(const sf::Event& e, ChessGame& owner)
{
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Q)
			owner._gameRunning = false;
		if (e.key.code == sf::Keyboard::Escape)
			return new NullState();
	}

	return NULL;
}

void PauseState::entry(ChessGame& owner)
{
	owner._time[owner._isWhiteTurn].stop();
}

void PauseState::quit(ChessGame& owner)
{
	owner._time[owner._isWhiteTurn].start();
}

void PauseState::draw(ChessGame& owner)
{
	sf::Font font;
	font.loadFromFile("Assets\\arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setString("P A U S E");
	sf::FloatRect bound = text.getLocalBounds();

	text.setOrigin(bound.width / 2, bound.height / 2);
	text.setPosition(400, 300 - 80);

	owner._window.draw(text);
}
