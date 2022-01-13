#pragma once
#include "MovingState.h"
#include "Button.h"
#include "Constants.h"

class PromotionState : public MovingState {
private:
	Button* _text;
	Button* _button[4];
	int _preRow, _preCol;

public:
	PromotionState(int preRow, int preCol, int row, int col) : MovingState(row, col) {
		_preRow = preRow;
		_preCol = preCol;

		int top = 100;
		_text = new Button(sf::Vector2f(420, MENU_OPTION_HEIGHT), RECT_COLOR, "PROMOTION", 60, sf::Color::Blue, 300, top);

		_button[0] = new Button(RECT_SIZE, RECT_COLOR, "Queen", 50, sf::Color::Black, 300, top + 100);
		_button[1] = new Button(RECT_SIZE, RECT_COLOR, "Knight", 50, sf::Color::Black, 300, top + 2*100);
		_button[2] = new Button(RECT_SIZE, RECT_COLOR, "Rook", 50, sf::Color::Black, 300, top + 3*100);
		_button[3] = new Button(RECT_SIZE, RECT_COLOR, "Bishop", 50, sf::Color::Black, 300, top + 4*100);
	};

	GameState* handleInput(const sf::Event& event, ChessGame& owner);
	void entry(ChessGame& owner) {};

	void update(ChessGame& owner) {
		for (int i = 0; i < 4; i++)
			_button[i]->update(sf::Mouse::getPosition(owner._window));
	};

	void draw(ChessGame& owner);

	void quit(ChessGame& owner) { acceptMove(owner); };

	~PromotionState() {
		for (int i = 0; i < 4; i++) {
			delete _button[i];
			_button[i] = NULL;
		}

		delete _text;
		_text = NULL;
	}
};
