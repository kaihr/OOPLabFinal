#include "Piece.h"

Piece* Piece::handleInput(const sf::Event& event, Piece* pieces[8][8])
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i curCell = Utility::getCell(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			int nextRow = curCell.x;
			int nextCol = curCell.y;

			if (validCell(nextRow, nextCol, pieces)) {
				if (pieces[nextRow][nextCol]) {
					delete pieces[nextRow][nextCol];
					pieces[nextRow][nextCol] = NULL;
				}

				pieces[nextRow][nextCol] = pieces[_row][_col];
				pieces[_row][_col] = NULL;

				_row = nextRow;
				_col = nextCol;
				_sprite.setPosition(_col * CELL_LENGTH, _row * CELL_LENGTH);

				return NULL;
			}
		}
	}

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			_sprite.setPosition(_col * CELL_LENGTH, _row * CELL_LENGTH);

		return NULL;
	}

	return this;
}