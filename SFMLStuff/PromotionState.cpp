#include "PromotionState.h"
#include "NullState.h"

GameState* PromotionState::handleInput(const sf::Event& event, ChessGame& owner)
{
	GameState* ans = NULL;

	if (event.type == sf::Event::MouseButtonPressed) {
		if (_button[0]->isMouseOver()) {
			delete owner._pieces[_row][_col];
			owner._pieces[_row][_col] = new Queen(_row, _col, owner._isWhiteTurn);
			ans = new NullState();
		}

		if (_button[1]->isMouseOver()) {
			delete owner._pieces[_row][_col];
			owner._pieces[_row][_col] = new Knight(_row, _col, owner._isWhiteTurn);
			ans = new NullState();
		}

		if (_button[2]->isMouseOver()) {
			delete owner._pieces[_row][_col];
			owner._pieces[_row][_col] = new Rook(_row, _col, owner._isWhiteTurn);
			ans = new NullState();
		}

		if(_button[3]->isMouseOver()) {
			delete owner._pieces[_row][_col];
			owner._pieces[_row][_col] = new Bishop(_row, _col, owner._isWhiteTurn);
			ans = new NullState();
		}
	}

	return ans;
}

void PromotionState::draw(ChessGame& owner)
{
	GameState::draw(owner);

	owner._window.draw(*_text);

	for (int i = 0; i < 4; i++)
		owner._window.draw(*_button[i]);
}
