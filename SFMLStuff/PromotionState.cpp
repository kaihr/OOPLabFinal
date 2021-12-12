#include "PromotionState.h"
#include "NullState.h"

GameState* PromotionState::handleInput(const sf::Event& event, ChessGame& owner)
{
	GameState* ans = NULL;

	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code)
		{
		case sf::Keyboard::A:
			delete owner._pieces[_row][_col];
			owner._pieces[_row][_col] = new Queen(_row, _col, owner._isWhiteTurn);
			ans = new NullState();
			break;
		case sf::Keyboard::S:
			delete owner._pieces[_row][_col];
			owner._pieces[_row][_col] = new Knight(_row, _col, owner._isWhiteTurn);
			ans = new NullState();
			break;
		case sf::Keyboard::D:
			delete owner._pieces[_row][_col];
			owner._pieces[_row][_col] = new Rook(_row, _col, owner._isWhiteTurn);
			ans = new NullState();
			break;
		case sf::Keyboard::F:
			delete owner._pieces[_row][_col];
			owner._pieces[_row][_col] = new Bishop(_row, _col, owner._isWhiteTurn);
			ans = new NullState();
			break;
		default:
			break;
		}
	}

	return ans;
}
