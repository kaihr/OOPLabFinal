#include "TerminateState.h"

GameState* TerminateState::handleInput(const sf::Event& event, ChessGame& owner)
{
	return NULL;
}

void TerminateState::entry(ChessGame &owner)
{
	owner._time[owner._isWhiteTurn].stop();
	owner._gameRunning = false;

	Button* results = new Button(sf::Vector2f(120, 50), BG_COLOR, _str, 35, sf::Color::Black, 700, 220);
	Button* button = new Button(sf::Vector2f(120, 50), RECT_COLOR, "Exit", 35, sf::Color::Black, 700, 300);

	owner._gameRunning = true;

	while (owner._gameRunning) {
		sf::Event event;
		while (owner._window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				owner._gameRunning = false;
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			if (button->isMouseOver())
				owner._gameRunning = false;
		}

		button->update(sf::Mouse::getPosition(owner._window));

		owner._window.clear(BG_COLOR);

		owner._mouseState->draw(owner);

		owner._window.draw(*results);
		owner._window.draw(*button);

		owner._window.display();
	}

	delete button;
}
